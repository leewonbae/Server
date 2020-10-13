#include "cUserManager.h"
cUserManager::cUserManager()
{
	UserCount = 0;

}
cUserManager::~cUserManager()
{

}

void cUserManager::InputUser(cUser* _user)
{
	mCS_UserManager.LockCs();
	int index = _user->getkey();
	mUserArray[index] = _user;
	_user->SetUserMode(true);
	UserCount++;
	mCS_UserManager.UnLock();
	cLog::Print_UserCount(UserCount);
}
void cUserManager::DeleteUser(int _index)
{
	mCS_UserManager.LockCs();
	mUserArray[_index] = NULL;
	UserCount--;
	mCS_UserManager.UnLock();
	cLog::Print_UserCount(UserCount);
}
 