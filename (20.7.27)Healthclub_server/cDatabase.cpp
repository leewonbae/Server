#include "cDatabase.h"
cDatabase::cDatabase()
{
	mUsercount = 0;
	mNoticecount = 0;
	mDatacount = 0;
	mNodeHead = NULL;
	mNoticeHead = NULL;
	mDataHead = NULL;

}
cDatabase ::~cDatabase()
{

}
void cDatabase::InputNewUser(PACKET_USERDATA* _puser)
{
	NODE* newnode = new NODE;
	memcpy(&newnode->mUserdata, _puser, sizeof(PACKET_USERDATA));
	newnode->mNextnode = NULL;
	mUsercount++;
	if (mNodeHead == NULL)
	{
		mNodeHead = newnode;
		
	}
	else
	{
		mNodeTail->mNextnode = newnode;
	}
	mNodeTail = newnode;
}
bool cDatabase::CompareUser(PACKET_USERDATA* _puser)
{
	NODE* cur = mNodeHead;
	while (cur != NULL)
	{
		if (strcmp(cur->mUserdata.mName, _puser->mName) == 0)
		{
			if (cur->mUserdata.mPassword == _puser->mPassword)
			{
				return true;
			}
		}
		
		cur = cur->mNextnode;
	}
	return false;
	 
}
void cDatabase::InputNotice(PAKCET_NOTICE* _pnotice)
{
	NOTICE_NODE* newnode = new NOTICE_NODE;
	memcpy(&newnode->mNoticedata, _pnotice, sizeof(PAKCET_NOTICE));
	newnode->mNextnode = NULL;
	mNoticecount++;
	if (mNoticeHead == NULL)
	{
		mNoticeHead = newnode;

	}
	else
	{
		mNoticeTail->mNextnode = newnode;
	}
	mNoticeTail = newnode;
}
void cDatabase::InputData(PAKCET_NOTICE* _pnotice)
{
	NOTICE_NODE* newnode = new NOTICE_NODE;
	memcpy(&newnode->mNoticedata, _pnotice, sizeof(PAKCET_NOTICE));
	newnode->mNextnode = NULL;
	mDatacount++;
	if (mDataHead == NULL)
	{
		mDataHead = newnode;

	}
	else
	{
		mDataTail->mNextnode = newnode;
	}
	mDataTail = newnode;
}
void cDatabase::ShowUserData()
{
	NODE* cur = mNodeHead;
	int usercount = 1;
	while (cur != NULL)
	{
		 
		cout << usercount<<" . ¹ø È¸¿ø = " <<cur->mUserdata.mName << endl;
		usercount++;
		cur = cur->mNextnode;
	}
}
int cDatabase::getNoticeCount()
{
	return mNoticecount;
}
int cDatabase::getDataCount()
{
	return mDatacount;
}
int cDatabase::getUserCount()
{
	return mUsercount;
}
NOTICE_NODE* cDatabase::getNotice()
{
	return mNoticeHead;
}
NOTICE_NODE* cDatabase::getData()
{
	return mDataHead;
}