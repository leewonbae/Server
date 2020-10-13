#pragma once
#include "Resource.h"
#include "cUser.h"
#include "cLog.h"
#include "cCriticalSection.h"
class cUserManager
{
public:
	cUserManager();
	~cUserManager();

	void InputUser(cUser* _user);
	void DeleteUser(int _index);
 
	
private:
	cUser* mUserArray[MAX_SESSION_ARRAY] = {NULL,};
	cCriticalSection mCS_UserManager;
	int UserCount;
};

