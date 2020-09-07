#include "cUserManager.h"
cUserManager::cUserManager()
{
	mUsercount = 0;
	mHead = NULL;
	mTail = NULL;
}
cUserManager::~cUserManager()
{

}
void cUserManager::InputUser(cUser* _user)
{
	USER_NODE* newuser = new USER_NODE;
	_user->SetKey(mUsercount + 1);
	newuser->mlogin = _user;
	newuser->mNextNODE = NULL;

	if (mHead == NULL)
	{
		mHead = newuser;
	}
	else
	{
		mTail->mNextNODE = newuser;
	}
	mTail = newuser;
	mUsercount++;

}
 
void cUserManager::BroadMSG()
{

}