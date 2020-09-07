#pragma once
#include "Resource.h"
#include "cUser.h"
#include "cDataBase.h"
#include "Packet.h"
#include "cCriticalSection.h"
class cUserManager
{
public:
	cUserManager();
	~cUserManager();

	void InputUser(cUser* _user);
	void DeleteUser(int _key);
	void SetDataBase(cDataBase* _DBptr);
	void ShowUserCount();
	void UserParsing(int _key, PACKET_HEAD* _recvpacket);



private:
	cUser* mUserArray[50] = { NULL, };
	cDataBase* mDBPtr;
	int mUsercount;

};


