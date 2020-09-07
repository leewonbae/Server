#pragma once
#include "Resource.h"
#include "cUser.h"
#include "Packet.h"


class cUserManager
{
	 
public:
	cUserManager();
	~cUserManager();

	void InputUser(cUser* _user);
	void DelteUser(int _key);
	void ShowCount();
	void UserParsing(int _key,PACKET_HEAD* _recvpacket);
private:
	cUser* mUserArray[20] = { NULL, };
	int mUserCount;
	 

};

