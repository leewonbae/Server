#pragma once
#include "resource.h"
#include "cUser.h"
struct USER_NODE {
	cUser* mlogin;
	USER_NODE* mNextNODE;
};
class cUserManager
{
public:
	cUserManager();
	~cUserManager();
	void InputUser(cUser* _user);
	 
	void BroadMSG();
private:
	int mUsercount;
	USER_NODE* mHead;
	USER_NODE* mTail;
};

