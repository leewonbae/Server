#include "cUserDB.h"
cUserDB::cUserDB()
{
	mDatacount = 0;
	mHead = NULL;

}
cUserDB::~cUserDB()
{

}
void cUserDB::InputUserinfo(char* _name, int _password)
{
	mDatacount++;
	NODE* newnode = new NODE;
	strcpy(newnode->mName, _name);
	newnode->mPassword = _password;
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
}
bool cUserDB::CheckDB(char* _name, int _password)
{
	NODE* cur = mHead;
	while (cur != NULL)
	{
		if (strcmp(cur->mName, _name) == 0 && cur->mPassword == _password)
		{
			return true;
		}
		cur = cur->mNextnode;
	}
	return false;
}