#pragma once
#include "resource.h"

struct UserDB_NODE {
	PACKET_NEWUSER mNODE_pnew;
	UserDB_NODE* mNextnode;
};
class cUserDB
{
	 
public:
	cUserDB();
	~cUserDB();
	void InputUserDB(PACKET_NEWUSER _pnewuser);
	bool ChecktUserDB(PACKET_LOGIN _checkDB);
private:
	UserDB_NODE* mHead;
	UserDB_NODE* mTail;
	int mUserDBcount;
};

