#pragma once
#include "Resource.h"
#include "cUser.h"
#include "cCriticalSection.h"
#include "Protocol.h"
#include "cMysql.h"
#include "cRoomManager.h"

class cUserManager
{
public:
	cUserManager();
	~cUserManager();

	void OutUser(cUser* _user);
	
	// recv ok
	void UserManagerParsing(PACKET_HEAD* _phead, cUser* _user);

	// send ok
	void SendCheck(OVERDATA* _overdata,cUser* _user);


	void ShowUserCount();
private:
	cCriticalSection mCS_USERMANAGER;
	
	int mUserCount;// 병목 체크 
	cMysql mMysql;
};

