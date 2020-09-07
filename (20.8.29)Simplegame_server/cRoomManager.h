#pragma once
#include "Resource.h"
#include "cRoom.h"
#include "Packet.h"
#include "cUser.h"



class cRoomManager
{
public:
	cRoomManager();
	~cRoomManager();

	void RoomParsing(cUser* _user, PACKET_HEAD* _recvpacket);

	void MakeRoom(cUser* _user, PACKET_HEAD* _recvpacket);
	void InRoom(cUser* _user, PACKET_HEAD* _recvpacket);
	void ReayReq(cUser* _user, PACKET_HEAD* _recvpacket);
	void setRoomLIST(cUser* _user, PACKET_HEAD* _recvpacket);
	void GameResult(cUser* _user, PACKET_HEAD* _recvpacket);
	void DelteRoom(int _roomnum);

private:
	cRoom* mRoomArray[20] = { NULL, };
	int mRoomcount;
};

