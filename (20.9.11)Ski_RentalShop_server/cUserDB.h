#pragma once
#include "Resource.h"
#include "Packet.h"
#include "cUser.h"
#include "cCriticalSection.h"
struct NODE {
	USERINFO mUserInfo;
	RESERVATION mReserv;
	bool mActiveCheck = false;
	NODE* mNextNode;

};
class cUserDB
{
public:
	cUserDB();
	~cUserDB();
	void DBparsing(PACKET_HEAD* _recvpacket,cUser* _user);
	void InputDB(PACKET_HEAD* _recvpacket);
	void CheckLogin(PACKET_HEAD* _recvpacket, cUser* _user);
	void ModifiedRservation(cUser* _user);
	void ShowDBcount();
private:

	cCriticalSection mCS;
	NODE* mHead;
	NODE* mTail;
	int mDBcount;
};

