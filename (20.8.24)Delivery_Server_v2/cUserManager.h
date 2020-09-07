#pragma once
#include "Resource.h"
#include "cUser.h"
#include "Packet.h"
#include "Log.h"
class cUserManager
{
public:
	cUserManager();
	~cUserManager();
	void InputUser(cUser* _user,int _key);
	void DeleteUser(int _key);
	void ShowUser();
	void UserParsing(int _key, PACKET_HEAD* _recvpacket);
private:
	cUser* mUserArray[50] = {NULL,};
	int mUsercount;
};

