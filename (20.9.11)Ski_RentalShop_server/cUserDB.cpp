#include "cUserDB.h"
cUserDB::cUserDB()
{
	mDBcount = 0;
	mHead = NULL;
	mTail = NULL;
}
cUserDB::~cUserDB()
{

}
void cUserDB::DBparsing(PACKET_HEAD* _recvpacket, cUser* _user)
{
	switch (_recvpacket->mCmd)
	{
	case PTC_LOGIN_REQ:
		CheckLogin(_recvpacket, _user);
		break;
	case PTC_NEWUSER_REQ:
		InputDB(_recvpacket);
		break;
	default:
		cout << "DB 패킷확인 불가능" << endl;
		break;
	}
}
void cUserDB::InputDB(PACKET_HEAD* _recvpacket)
{
	mCS.Lock();
	PACKET_NEWUSER* pnew = (PACKET_NEWUSER*)_recvpacket;
	NODE* newnode = new NODE;
	strcpy(newnode->mUserInfo.mID, pnew->mName);
	newnode->mUserInfo.mPassword = pnew->mPassword;
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

	cout << "입력 된 id = " << newnode->mUserInfo.mID << endl;
	cout << "입력 된 password = " << newnode->mUserInfo.mPassword << endl;
	_recvpacket->mPacket_MSG = MSG_NEWUSER_OK;
	mDBcount++;
	ShowDBcount();

	mCS.Unlock();
}
void cUserDB::CheckLogin(PACKET_HEAD* _recvpacket, cUser* _user)
{
	mCS.Lock();
	PACKET_LOGIN* plog = (PACKET_LOGIN*)_recvpacket;
	NODE* cur = mHead;

	while (cur != NULL)
	{
		if (strcmp(cur->mUserInfo.mID, plog->mName) == 0 &&
			cur->mUserInfo.mPassword == plog->mPassword &&
			cur->mActiveCheck ==false)
		{
			_user->SetUserinfo(cur->mUserInfo);
			_user->SetReservation(cur->mReserv);
			memcpy(&plog->mReserv, &cur->mReserv, sizeof(RESERVATION));
			_recvpacket->mPacket_MSG = MSG_LOGIN_OK;
			cur->mActiveCheck = true;
			break;
		}
		 
		cur = cur->mNextNode;
	}
	mCS.Unlock();
}
void cUserDB::ModifiedRservation(cUser* _user)
{
	mCS.Lock();
	NODE* cur = mHead;
	USERINFO userinfo;
	RESERVATION reserv;
	memcpy(&userinfo, &_user->getUserinfo(), sizeof(USERINFO));
	memcpy(&reserv, &_user->getReserv(), sizeof(RESERVATION));
	cout << "이름 = " << userinfo.mID << endl;
	cout << " 수량 스키= " << reserv.mSki_count << endl;
	cout << " 수량 보드= " << reserv.mBoard_count << endl;
	cout << " 수량 의류=" << reserv.mClothing_count << endl;

	while (cur != NULL)
	{
		if (strcmp(cur->mUserInfo.mID, userinfo.mID) == 0 &&
			cur->mUserInfo.mPassword == userinfo.mPassword)
		{
			cur->mActiveCheck = false;
			memcpy(&cur->mReserv, &reserv,sizeof(RESERVATION));

			break;
		}
		 
		cur = cur->mNextNode;
	}
	mCS.Unlock();
}
void cUserDB::ShowDBcount()
{
	cout << "현재 저장된 DB 수 = " << mDBcount << endl;
}