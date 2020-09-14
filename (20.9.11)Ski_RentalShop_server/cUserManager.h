#pragma once
#include "Resource.h"
#include "cUser.h"
#include "cEquipmentStore.h"
#include "Packet.h"
#include "cCriticalSection.h"
class cUserManager
{
public:
	cUserManager();
	~cUserManager();

	void InputUser(cUser* _user);
	void DeleteUser(int _key);
	 
	void ShowUserCount();
	void UserParsing(int _key, PACKET_HEAD* _recvpacket);



private:
	cCriticalSection mCS;
	cEquipmentStore mEquipment;
	cUser* mUserArray[50] = { NULL, };
	int mUsercount;

};


