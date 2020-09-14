#pragma once
#include "Resource.h"
#include "Packet.h"
#include "cUser.h"
#include "cCriticalSection.h"
class cEquipmentStore
{
public:
	cEquipmentStore();
	~cEquipmentStore();

	void EquipmentParsing(PACKET_HEAD* _recvpacket );
	void MakeListReq(PACKET_HEAD* _recvpacket);
	void RentalREQ(PACKET_HEAD* _recvpacket );
	void ReturnREQ(PACKET_HEAD* _recvpacket );
	void ShowCount();
private:

	cCriticalSection mCS;
	int mHave_ski_count;
	int mHave_board_count;
	int mHave_clothing_count;
};

