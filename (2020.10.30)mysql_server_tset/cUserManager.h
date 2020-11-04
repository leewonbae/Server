#pragma once
#include "Resource.h"
#include "cUser.h"
#include "Packet.h"
#include "cCriticalSection.h"
#include "cItemDBA.h"
class cUserManager
{
public:
	cUserManager();
	~cUserManager();

	void UserManager_Parsing(cUser* _user, PACKET_HEAD* _phead);
	void InputUser(cUser* _session);
	void ShowUserCount();
	void OutUser();
 
private:
	int mUserCount;
	cItemDBA mItemDBA;
	cCriticalSection mUser_CS;
};

