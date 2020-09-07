#include "cDataBase.h"
cDataBase::cDataBase()
{
	mHead = NULL;
	mTail = NULL;
	mDBcount = 0;
}
cDataBase::~cDataBase()
{

}
void cDataBase::ShowDataCount()
{
	cout << "현재 저장된 DB 수 = " << mDBcount << endl;
}
void cDataBase::PasingDB(cUser* _user,PACKET_HEAD* _recvpacket)
{
	cout << "디비 파싱" << endl;
	cout << _recvpacket->mCmd << endl;
	switch (_recvpacket->mCmd)
	{
	case PTC_NEWUSER_REQ:
		InputData(_recvpacket);
		break;

	case PTC_LOGIN_REQ:
		CheckData(_user,_recvpacket);
		break;
	}
}
void cDataBase::InputData(PACKET_HEAD* _recvpacket)
{
	cCriticalSection cs;
	cs.Lock();


	cout << "db 의 회원가입" << endl;
	PACKET_NEWUSER* pnew = (PACKET_NEWUSER*)_recvpacket;
	
	
	NODE* newnode = new NODE;
	strcpy(newnode->mUserInfo.mName, pnew->mName);
	newnode->mUserInfo.mPassword = pnew->mPassword;
	newnode->mUserInfo.mTransferNum = pnew->mTransferNum;
	newnode->mUserInfo.mMoney = 0;
	newnode->mNextNode = NULL;

	if (mHead == NULL)
	{
		mHead = newnode;
	}
	else
	{
		mTail->mNextNode = newnode;
	}
	mTail = newnode;

	_recvpacket->mPacket_MSG = MSG_NEWUSER_OK;
	mDBcount++;
	ShowDataCount();


	cs.Unlock();
}
void cDataBase::CheckData(cUser* _user, PACKET_HEAD* _recvpacket)
{
	cCriticalSection cs;
	cs.Lock();
	cout << "DB의  로그인 체크" << endl;
	PACKET_LOGIN* plogin = (PACKET_LOGIN*)_recvpacket;
	NODE* cur = mHead;
	 
	while (cur != NULL)
	{
		if (strcmp(cur->mUserInfo.mName, plogin->mName) == 0 &&
			cur->mUserInfo.mPassword == plogin->mPassword &&
			cur->mUserInfo.mActiveCheck==false)

		{
			_recvpacket->mPacket_MSG = MSG_LOGIN_OK;
			_user->SetUserCheck(true);
			_user->SetUserINFO(&cur->mUserInfo);
			cur->mUserInfo.mActiveCheck = true;
			break;
		}
		cur = cur->mNextNode;
		if (cur == NULL)
		{
			_recvpacket->mPacket_MSG = MSG_LOGIN_FAIL;
		}
	}
	cs.Unlock();
}
void cDataBase::TransferMoney(PACKET_HEAD* _recvpacket)
{
	cCriticalSection cs;
	cs.Lock();
	cout << "DB 의 계좌이체" << endl;

	PACKET_TRANSFER* ptrans = (PACKET_TRANSFER*)_recvpacket;
	NODE* cur = mHead;

	while (cur != NULL)
	{
		if (cur->mUserInfo.mTransferNum == ptrans->mTo_TransferNum)
		{
			cur->mUserInfo.mMoney += ptrans->mSendMoney;
			_recvpacket->mPacket_MSG = MSG_TRANSFER_OK;
			cout << cur->mUserInfo.mName << endl;
			cout << cur->mUserInfo.mMoney << endl;
			break;
		}
		cur = cur->mNextNode;
		if (cur == NULL)
		{
			_recvpacket->mPacket_MSG = MSG_TRANSFER_FAIL;
		}
	}
	cs.Unlock();
}
 