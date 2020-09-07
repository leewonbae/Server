#include "cUSER.h"
cUSER:: cUSER() 
{
	
	 
	mRoomNumber = 0;
	mPlayRoomNumber = 0;
	mFmap.insert(map<int, fp>::value_type(MSG_LOGIN_REQ, &cUSER::MSG_LOGIN));
	mFmap.insert(map<int, fp>::value_type(MSG_NEWUSER_REQ, &cUSER::MSG_NEWUSER));
	mFmap.insert(map<int, fp>::value_type(MSG_ROOMLIST_REQ, &cUSER::MSG_ROOMLIST));
	mFmap.insert(map<int, fp>::value_type(MSG_MAKEROOM_REQ, &cUSER::MSG_MAKEROOM));
	mFmap.insert(map<int, fp>::value_type(MSG_ENTERROOM_REQ, &cUSER::MSG_ENTERROOM));
	mFmap.insert(map<int, fp>::value_type(MSG_OUTROOM_REQ, &cUSER::MSG_OUTROOM));
	mFmap.insert(map<int, fp>::value_type(MSG_PLAER_READY_REQ, &cUSER::MSG_PLAER_READY));
	mFmap.insert(map<int, fp>::value_type(MSG_HIT_REQ, &cUSER::MSG_HIT));
	mFmap.insert(map<int, fp>::value_type(MSG_STAND_REQ, &cUSER::MSG_STAND));
	mFmap.insert(map<int, fp>::value_type(MSG_RESULT_REQ, &cUSER::MSG_RESULT));
	mFmap.insert(map<int, fp>::value_type(MSG_REGAME_REQ, &cUSER::MSG_REGAME));
}
cUSER::~cUSER()
{
	 
}

void cUSER::Parsing(int _packetCmd, OVERDATA* _over)
{

	
	cout << "head  = " << _packetCmd << endl;
	fp	Temp;
	iter = mFmap.find(_packetCmd);
	memset(mSendBuf, 0, sizeof(BUFFER_SIZE));
	memcpy(&phead, _over->mDatabuf, sizeof(PACKET_HEAD));
	cSession* se = (cSession*)_over;
	Temp = iter->second;
	(this->*Temp)(_over);
	if (_packetCmd != MSG_PLAER_READY_REQ && _packetCmd != MSG_STAND_REQ && _packetCmd!= MSG_RESULT_REQ && _packetCmd != MSG_REGAME_REQ)
	{
		memcpy(mSendBuf, &phead, sizeof(PACKET_HEAD));
		se->OnSend(mSendBuf);
	}
}
void cUSER::MSG_LOGIN(OVERDATA* _over)
{
	cout << "로그인" << endl;
	int usernum;
	PACKET_USERDATA puser;
	cSession* se = (cSession*)_over;
	USERDATA udata;
	memcpy(&puser, _over->mDatabuf + sizeof(PACKET_HEAD), sizeof(PACKET_USERDATA));
	cout << "puser" << puser.mName << endl;
	cout << "puser" << puser.mPassword << endl;
	usernum = mCdatabase.FindData(&puser);
	
	if (usernum != USER_PASSWORD_ERROR && usernum != USER_NO_DATA_ERROR)
	{
		se->SetUser( mCdatabase.getUSER(usernum));
		memcpy(&udata, mCdatabase.getUSER(usernum),sizeof(USERDATA));
		memcpy(mSendBuf + sizeof(PACKET_HEAD), &udata, sizeof(USERDATA));

	}
	else
	{
		phead.mPacketSize = 2;
		
	}
}

void cUSER::MSG_NEWUSER(OVERDATA* _over)
{
	cout << "회원가입" << endl;
	PACKET_USERDATA puser;

	memcpy(&puser, _over->mDatabuf + sizeof(PACKET_HEAD), sizeof(PACKET_USERDATA));
	USERDATA* newdata = new USERDATA;
	memcpy(newdata->mName, puser.mName, sizeof(puser.mName));
	newdata->mPassword = puser.mPassword;
	newdata->mMoney = 0;
	newdata->mNextData = NULL;
	mCdatabase.InputData(newdata);
	
}

void cUSER::MSG_ROOMLIST(OVERDATA* _over)
{
	
	cout << "방 리스트 요청" << endl;
	PACKET_ROOMINFO proom;
	proom.mRoomcount = mRoomNumber;
	if (mRoomNumber == 0)
	{
		cout << "방 없습니다." << endl;
	}
	else
	{
		for (int i = 0;i < mRoomNumber;i++)
		{
			proom.mStartFleg[i] = mRoomArray[i]->getStartfleg();
			proom.mRoominfo[i] = mRoomArray[i]->getUserCount();
		}
		
	}
	memcpy(mSendBuf + sizeof(PACKET_HEAD), &proom, sizeof(PACKET_ROOMINFO));
	
}
void cUSER::MSG_MAKEROOM(OVERDATA* _over)
{
	cSession* se = (cSession*)_over;
	cRoom* newroom = new cRoom;
	mRoomArray[mRoomNumber] = newroom;
	newroom->EnterUser(se);
	se->SetRoomNum(mRoomNumber);
	mRoomNumber += 1;
	 
}
void cUSER::MSG_ENTERROOM(OVERDATA* _over)
{
	PACKET_ENTERROOM penter;
	cSession* se = (cSession*)_over;
	memset(&penter, 0, sizeof(PACKET_ENTERROOM));
	memcpy(&penter, _over->mDatabuf + sizeof(PACKET_HEAD), sizeof(PACKET_ENTERROOM));
	if (mRoomStartFleg[penter.mEnterRoomNum] == false)
	{
		se->SetRoomNum(penter.mEnterRoomNum);
		mRoomArray[penter.mEnterRoomNum]->EnterUser(se);
	}
}
void cUSER::MSG_OUTROOM(OVERDATA* _over)
{
	cSession* se = (cSession*)_over;
	PACKET_ENTERROOM penter;
	int roomnumber;
	roomnumber = se->getRoomNumber();
	if (!mRoomArray[roomnumber]->outUser(se))
	{
		delete mRoomArray[roomnumber];
		mRoomNumber--;
	}
}


void cUSER::MSG_PLAER_READY(OVERDATA* _over)
{
	int temp;
	int usercount;
	cSession* se = (cSession*)_over;
	PACKET_READY pready;
	memset(&pready, 0, sizeof(PACKET_READY));
	memcpy(&pready, _over->mDatabuf + sizeof(PACKET_HEAD), sizeof(PACKET_READY));
	temp = se->getRoomNumber();
	usercount = mRoomArray[temp]->getUserCount();
	if (mRoomArray[temp]->ReadyInput(se) && usercount>= 2)
	{
		
		mUserArray = mRoomArray[temp]->getUserArry();
		mRoomArray[temp]->setStartFleg(true);
		mRoomStartFleg[temp] = true;

		PLAYROOM* newplayroom = new PLAYROOM;
		newplayroom->mUserArray = mRoomArray[temp]->getUserArry();
		newplayroom->mUserCount = usercount;
		memcpy(&newplayroom->mServerCard, &newplayroom->mCardDumy.PopCard(2), sizeof(PACKET_CARD));
		memcpy(mSendBuf + sizeof(PACKET_HEAD), &newplayroom->mServerCard, sizeof(PACKET_CARD));
		
		
		
		PACKET_CARD pcard;
		phead.mPacketSize = 1;
		memcpy(mSendBuf, &phead, sizeof(PACKET_HEAD));
		
		
		for (int i = 0;i < usercount;i++)
		{
			
			memcpy(&pcard, &newplayroom->mCardDumy.PopCard(2), sizeof(PACKET_CARD));
			memcpy(mSendBuf + sizeof(PACKET_HEAD) + sizeof(PACKET_CARD), &pcard, sizeof(PACKET_CARD));
			mUserArray[i]->SetmStartRoomNumber(mPlayRoomNumber);
			
			mUserArray[i]->OnSend(mSendBuf);
		}
		
		mPlayRoomLIst[mPlayRoomNumber] = newplayroom;
		mPlayRoomNumber++;
	}
}
 
void cUSER::MSG_HIT(OVERDATA* _over)
{
	int temp;
	cSession* se = (cSession*)_over;
	temp=se->getStartRoomNumber();
	PACKET_CARD pcard;
	memcpy(&pcard, &mPlayRoomLIst[temp]->mCardDumy.PopCard(1), sizeof(PACKET_CARD));
	memcpy(mSendBuf + sizeof(PACKET_HEAD), &pcard, sizeof(PACKET_CARD));
}
void cUSER::MSG_STAND(OVERDATA* _over)
{
	int temp;
	cSession* se = (cSession*)_over;
	PACKET_RESULT presult;
	temp = se->getStartRoomNumber();
	mPlayRoomLIst[temp]->mStandCount++;
	phead.mCmd = MSG_STAND_REQ;
	memcpy(mSendBuf, &phead, sizeof(PACKET_HEAD));
	memcpy(&presult, _over->mDatabuf + sizeof(PACKET_HEAD), sizeof(PACKET_RESULT));
	if (presult.mResult == true)
	{
		
		se->InputMoney(presult.mBattingMoney * 3);
	}
	else
	{
		se->OutputMoney(presult.mBattingMoney);
	}
	cout << "stand user count " << mPlayRoomLIst[temp]->mUserCount<<endl;
	if (mPlayRoomLIst[temp]->mUserCount == mPlayRoomLIst[temp]->mStandCount)
	{
		for (int i = 0;i < mPlayRoomLIst[temp]->mUserCount;i++)
		{
			mPlayRoomLIst[temp]->mUserArray[i]->OnSend(mSendBuf);
		}
		mPlayRoomLIst[temp]->mStandCount = 0;
		
	}
}
void cUSER::MSG_RESULT(OVERDATA* _over)
{
	int temp;
	PACKET_STAND pstand;
	memcpy(&pstand, _over->mDatabuf + sizeof(PACKET_HEAD), sizeof(PACKET_STAND));
	
	cSession* se = (cSession*)_over;
	phead.mCmd = MSG_RESULT_REQ;
	temp = se->getStartRoomNumber();
	mPlayRoomLIst[temp]->mStandCount++;
	if (pstand.mStandRsult == true)
	{
		cout << "regame" << endl;
		
	}
	else if (pstand.mStandRsult == false)
	{
		cout << "noregame" << endl;
		mPlayRoomLIst[temp]->mNoRestartCount++;
	}

	if (mPlayRoomLIst[temp]->mUserCount == mPlayRoomLIst[temp]->mStandCount )
	{
		if (mPlayRoomLIst[temp]->mNoRestartCount == 0)
		{
			pstand.mStandRsult = true;
			mPlayRoomLIst[temp]->mStandCount = 0;
		}
		else
		{
			pstand.mStandRsult = false;
			
		}
		memcpy(mSendBuf, &phead, sizeof(PACKET_HEAD));
		memcpy(mSendBuf + sizeof(PACKET_HEAD), &pstand, sizeof(PACKET_STAND));
		for (int i = 0;i < mPlayRoomLIst[temp]->mUserCount;i++)
		{
			mPlayRoomLIst[temp]->mUserArray[i]->OnSend(mSendBuf);

		}
		if (pstand.mStandRsult == false)
		{
			delete mPlayRoomLIst[temp];
			delete mRoomArray[temp];
			mPlayRoomNumber--;
			mRoomNumber--;
		}
	}

}

void cUSER::MSG_REGAME(OVERDATA* _over)
{
	int startroom;
	int usercount;
	cSession* se = (cSession*)_over;
	PACKET_CARD pcard;
	phead.mCmd = MSG_REGAME_REQ;
	memcpy(mSendBuf, &phead, sizeof(PACKET_HEAD));
	startroom = se->getStartRoomNumber();
	usercount = mPlayRoomLIst[startroom]->mUserCount;
	mPlayRoomLIst[startroom]->mStandCount++;

	if (mPlayRoomLIst[startroom]->mStandCount == usercount)
	{
		memcpy(&mPlayRoomLIst[startroom]->mServerCard, &mPlayRoomLIst[startroom]->mCardDumy.PopCard(2), sizeof(PACKET_CARD));
		memcpy(mSendBuf + sizeof(PACKET_HEAD), & mPlayRoomLIst[startroom]->mServerCard, sizeof(PACKET_CARD));
		for (int i = 0;i < mPlayRoomLIst[startroom]->mUserCount;i++)
		{
			memcpy(&pcard, &mPlayRoomLIst[startroom]->mCardDumy.PopCard(2), sizeof(PACKET_CARD));
			memcpy(mSendBuf + sizeof(PACKET_HEAD) + sizeof(PACKET_CARD), &pcard, sizeof(PACKET_CARD));
			mPlayRoomLIst[startroom]->mUserArray[i]->OnSend(mSendBuf);
		}
		mPlayRoomLIst[startroom]->mStandCount = 0;
	}
}