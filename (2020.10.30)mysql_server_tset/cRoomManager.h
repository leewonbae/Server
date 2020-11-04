#pragma once
#include "Resource.h"
#include "cRoom.h"
#include "cUser.h"
#include "cMySQL.h"
#include "Packet.h"



class cRoomManager
{
public:
	cRoomManager();
	~cRoomManager();

	void InitRoom();
	void RoomManager_Parsing(PACKET_HEAD* _packet, cUser* _user);
	void InOutRoom(PACKET_HEAD* _packet,cUser* _user);
	void MakeRoomReq(PACKET_HEAD* _packet,cUser* _user);
	void RoomReadyCheck(PACKET_HEAD* _packet,cUser* _user);

	void RoomListReq(PACKET_HEAD* _packet);


private:
	cRoom* mRoomArray[MAX_ROOM_COUNT] = { NULL, };
	int mRoomCount;
	cCriticalSection mCS_RoomManager;
};

