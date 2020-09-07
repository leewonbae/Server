#pragma once
#include "Resource.h"
#include "Packet.h"
#include "cUser.h"
struct LIST_NODE {
	char mID[10];
	int mPassword;
	int mScore;

	LIST_NODE* mNextNode = NULL;

};
class cDatabase
{
public:
	cDatabase();
	~cDatabase();
	void DBparsing(PACKET_HEAD* _recvpacket);
	void InputData(PACKET_HEAD* _recvpacket);
	void CheckUserdata(PACKET_HEAD* _recvpacket);
	
private:
	LIST_NODE* mHead;
	LIST_NODE* mTail;
	int DBcount;
};

