#include "cDatabase.h"
cDatabase::cDatabase()
{
	mHead = NULL;
	mTail = NULL;
	DBcount = 0;
}
cDatabase::~cDatabase()
{

}
void cDatabase::DBparsing(PACKET_HEAD* _recvpacket)
{
	switch (_recvpacket->mCmd)
	{
	case PTC_NEW_USER_REQ:
		InputData(_recvpacket);
		break;
	case PTC_LOGIN_REQ:
		CheckUserdata(_recvpacket);
		break;
	
	}
}
void cDatabase::InputData(PACKET_HEAD* _recvpacket)
{
	_recvpacket->mMsg = MSG_NEWUSER_OK;
	PACKET_NEWUSER* Pnewuser = (PACKET_NEWUSER*)_recvpacket;
	LIST_NODE* newnode = new LIST_NODE;
	strcpy(newnode->mID, Pnewuser->mID);
	newnode->mPassword = Pnewuser->mPassword;
	newnode->mScore = 0;

	if (mHead == NULL)
	{
		mHead = newnode;
	}
	else
	{
		mTail->mNextNode = newnode;
	}
	mTail = newnode;
	DBcount++;

}
void cDatabase::CheckUserdata(PACKET_HEAD* _recvpacket)
{
	LIST_NODE* cur = mHead;
	PACKET_LOGIN* plogin = (PACKET_LOGIN*)_recvpacket;
	while (cur != NULL)
	{
		if (strcmp(cur->mID, plogin->mID) == 0 && cur->mPassword == plogin->mPassword)
		{
			_recvpacket->mMsg = MSG_LOGIN_OK;
		}

		cur = cur->mNextNode;
	}

	if (_recvpacket->mMsg != MSG_LOGIN_OK)
	{
		_recvpacket->mMsg = MSG_LOGIN_FAIL;
	}

}
