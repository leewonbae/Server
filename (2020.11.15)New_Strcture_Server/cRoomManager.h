#pragma once
#include "Resource.h"
#include "Protocol.h"
#include "cUser.h"
#include "cRoom.h"
#include "cCriticalSection.h"

class cRoomManager
{
public:
	cRoomManager();
	~cRoomManager();
	// recv ฐüทร 
	void RoomManagerParsing(PACKET_HEAD* _phead, cUser* _user);

	void MakeRoomReq(PACKET_HEAD* _phead, cUser* _user);
	
	void RoomListReq(PACKET_HEAD* _phead, cUser* _user);

	void InOutRoomReq(PACKET_HEAD* _phead, cUser* _user);
 
	void ReadyReq(PACKET_HEAD* _phead, cUser* _user);
 
	void AttackReq(PACKET_HEAD* _phead, cUser* _user);
 
	void SendMsgCheck(PACKET_HEAD* _phead, cUser* _user);
private:
	cCriticalSection mCS_RoomManager;
	cRoom* mRoomArray[MAX_ROOM_SIZE] = { NULL, };
	int mDeleteCheckArray[MAX_ROOM_SIZE] = { 0, };
	int mRoomCount = 0;
};

