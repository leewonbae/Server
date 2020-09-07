#pragma once
#include "cSession.h"
#include "Packet.h"
class cUser :public cSession
{
public:
	cUser();
	~cUser();
	void SetRoomNum(int _roomnum);
	int getRoomNUM();

	typedef void (cUser::* fp)(PACKET_HEAD* _recvpacket);
	void Parsing(PACKET_HEAD* _phead);



private:
	void PTC_LOGIN(PACKET_HEAD* _recvpacket);
	void PTC_NEW_USER(PACKET_HEAD* _recvpacket);

	map<int, fp> mMap;
	map<int, fp>::iterator mIter;
	int RoomNum;
};

