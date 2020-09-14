#include "cEquipmentStore.h"
cEquipmentStore::cEquipmentStore()
{
	mHave_ski_count = 10;
	mHave_board_count = 10;
	mHave_clothing_count = 10;
}
cEquipmentStore::~cEquipmentStore()
{

}

void cEquipmentStore::EquipmentParsing(PACKET_HEAD* _recvpacket )
{
	switch (_recvpacket->mCmd)
	{
	case PTC_EQUIPMENT_LIST_REQ:
		MakeListReq(_recvpacket);
		break;
	case PTC_RETAL_REQ:
		RentalREQ(_recvpacket );
		break;
	case PTC_RETURN_REQ:
		ReturnREQ(_recvpacket );
		break;
	default:
		cout << "STORE 패킷 확인 불가능" << endl;
		break;
	}
}
void cEquipmentStore::MakeListReq(PACKET_HEAD* _recvpacket)
{
	PACKET_LIST* plist = (PACKET_LIST*)_recvpacket;
	plist->mSKIcount = mHave_ski_count;
	plist->mBOARDcount = mHave_board_count;
	plist->mCLOTHINGcount = mHave_clothing_count;


	_recvpacket->mPacket_MSG = MSG_LIST_OK;

}
void cEquipmentStore::RentalREQ(PACKET_HEAD* _recvpacket )
{
	mCS.Lock();
	PACKET_RENTAL* prental = (PACKET_RENTAL*)_recvpacket;
	int ski_check = mHave_ski_count - prental->mSKIcount;
	int board_check = mHave_board_count - prental->mBOARDcount;
	int clothing_check = mHave_clothing_count - prental->mCLOTHINGcount;

	if (ski_check >= 0 && board_check >= 0 && clothing_check >= 0)
	{
		mHave_ski_count -= prental->mSKIcount;
		mHave_board_count -= prental->mBOARDcount;
		mHave_clothing_count -= prental->mCLOTHINGcount;

		_recvpacket->mPacket_MSG = MSG_RENTAIL_OK;
		ShowCount();
	}
	
	mCS.Unlock();
}

void cEquipmentStore::ReturnREQ(PACKET_HEAD* _recvpacket )
{
	mCS.Lock();
	PACKET_RETURN* preturn = (PACKET_RETURN*)_recvpacket;
	mHave_ski_count += preturn->mSKIcount;
	mHave_board_count += preturn->mBOARDcount;
	mHave_clothing_count += preturn->mCLOTHINGcount;

	_recvpacket->mPacket_MSG = MSG_RETURN_OK;
	ShowCount();
	mCS.Unlock();
}

void cEquipmentStore::ShowCount()
{
	cout << "현재 보유 ski      = " << mHave_ski_count << endl;
	cout << "현재 보유 board    = " << mHave_board_count << endl;
	cout << "현재 보유 clothing = " << mHave_clothing_count << endl;
}