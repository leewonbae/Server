#include "cUser.h"
cUser::cUser()
{
	DBuserNum = 0;
	mMap.insert(make_pair(PTC_LOGIN,&cUser::Packet_Login));
	mMap.insert(make_pair(PTC_ITEM_UPLOAD, &cUser::packet_Item));

}
cUser::~cUser()
{

}
void cUser::SetDB_Num(int _num)
{
	DBuserNum = _num;
}

int cUser::getUserNum()
{
	return DBuserNum;
}

void cUser::SetRoomIndex(int _roomindex)
{
	mRoomIndex = _roomindex;
}

int cUser::getRoomIndex()
{
	return mRoomIndex;
}

void cUser::SetRoomNum(int _roomnum)
{
	mRoomNum = _roomnum;
}

int cUser::getRoomNum()
{
	return mRoomNum;
}


void cUser::Parsing(PACKET_HEAD* _phead)
{
	fp	Temp;

	mIter = mMap.find(_phead->mCmd);

	if (mIter != mMap.end())
	{
		Temp = mIter->second;
		(this->*Temp)(_phead);
	}
}
void cUser::Packet_Login(PACKET_HEAD* _phead)
{
	cout << "login" << endl;

	PACKET_LOGIN plog;
	memcpy(&plog, _phead, plog.mPacket_size);
	
	Onsend((void*)&plog, plog.mPacket_size);
}

void cUser::packet_Item(PACKET_HEAD* _phead)
{
	cout << "item" << endl;

	PACKET_ITEM_UPLOAD pItem;
	memcpy(&pItem, _phead, pItem.mPacket_size);
	
	Onsend((void*)&pItem, pItem.mPacket_size);
}