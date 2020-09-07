#include "cUserDB.h"
cUserDB::cUserDB()
{
	mUserDBcount = 0;
	mHead = NULL;
	mTail = NULL;
}
cUserDB::~cUserDB()
{

}

void cUserDB::InputUserDB(PACKET_NEWUSER _pnewuser)
{
	UserDB_NODE* newnode = new UserDB_NODE;
	memcpy(&newnode->mNODE_pnew, &_pnewuser, sizeof(PACKET_NEWUSER));
	newnode->mNextnode = NULL;

	if (mHead == NULL)
	{
		mHead = newnode;
	}
	else
	{
		mTail->mNextnode = newnode;
	}
	mTail = newnode;
	mUserDBcount += 1;
}
bool cUserDB::ChecktUserDB(PACKET_LOGIN _checkDB)
{
	UserDB_NODE* cur = mHead;
	while (cur != NULL)
	{
		if (strcmp(cur->mNODE_pnew.mNEW_ID, _checkDB.mLOGIN_ID) == 0  && cur->mNODE_pnew.mNEW_Password == _checkDB.mLOGIN_Password)
		{
			return true;
		}
		cur = cur->mNextnode;
	}
	
	return false;
}