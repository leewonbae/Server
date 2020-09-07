#include "cUser.h"
cUser::cUser()
{
	mFmap.insert(map<int, fp>::value_type(MSG_NEWUSER_REQ, &cUser::MSG_NEWUSER));
	mFmap.insert(map<int, fp>::value_type(MSG_USERMOVE_REQ, &cUser::MSG_USERMOVE));
	
	mUsercount = 0;
}

cUser::~cUser()
{

}
 
void cUser::SetUserarray(cSession** _userarray)
{
	mUserarray = _userarray;
}
void cUser::SetUsercount(int* _usercount)
{
	mUsercount = _usercount;
}
void cUser::SetEvent(HANDLE* _handle)
{
	mEventhandle = _handle;
}
void cUser::Parsing(OVERDATA* _over)
{
	PACKET_HEAD phead;
	memset(&phead, 0, sizeof(PACKET_HEAD));
	memcpy(&phead, _over->mDatabuf, sizeof(PACKET_HEAD));
	

	fp	Temp;
	mMapIteratior = mFmap.find(phead.sPacketCmd);


	Temp = mMapIteratior->second;
	(this->*Temp)(_over);



}

void cUser::MSG_NEWUSER(OVERDATA* over)
{
	cout << "new user" << endl;
	cSession* user = (cSession*)over;
	 
	PACKET_NEW pnew;
	memset(&pnew, 0, sizeof(PACKET_NEW));
	pnew.sUserKey = user->getkey();
	memcpy(mSendbuf + sizeof(PACKET_HEAD), &pnew, sizeof(PACKET_NEW));
	user->Onsend(MSG_NEWUSER_REQ, mSendbuf);
	PACKET_NEW ordernew;
	if (*mUsercount > 1)
	{
		for (int i = 0;i < *mUsercount;i++)
		{
			if (mUserarray[i] != user)
			{
				mUserarray[i]->Onsend(MSG_ORDERUSER_REQ, mSendbuf);
				ordernew.sUserKey = mUserarray[i]->getkey();
				memcpy(mSendbuf + sizeof(PACKET_HEAD), &ordernew, sizeof(PACKET_NEW));
				user->Onsend(MSG_ORDERUSER_REQ, mSendbuf);

			}

			Sleep(500);
		}
	}
	 
}

void cUser::MSG_USERMOVE(OVERDATA* over)
{

	cSession* user = (cSession*)over;
	PAKCET_MOVE pmove;
	memset(&pmove, 0, sizeof(PAKCET_MOVE));
	memcpy(&pmove, over->mDatabuf + sizeof(PACKET_HEAD), sizeof(PAKCET_MOVE));
	memcpy(mSendbuf + sizeof(PACKET_HEAD), &pmove, sizeof(PAKCET_MOVE));
	if (*mUsercount > 1)
	{
		for (int i = 0;i < *mUsercount;i++)
		{
			if (mUserarray[i] != user)
			{
				mUserarray[i]->Onsend(MSG_USERMOVE_REQ, mSendbuf);

			}

			Sleep(500);
		}
	}
}

