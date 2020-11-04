#pragma once
#include "Resource.h"
#include "cSession.h"
class cUser : public cSession
{
public:
	cUser();
	~cUser();

	void SetDB_Num(int _num);
	int getUserNum();

	void SetRoomNum(int _roomnum);
	void SetRoomIndex(int _roomindex);

	int getRoomNum();
	int getRoomIndex();

	typedef void (cUser::* fp)(PACKET_HEAD* _phead);
	void Parsing(PACKET_HEAD* _phead);
private:
	void Packet_Login(PACKET_HEAD* _phead);
	void packet_Item(PACKET_HEAD* _phead);
	int DBuserNum;
	int mRoomNum ;
	int mRoomIndex;

	map<int, fp> mMap;
	map<int, fp> ::iterator mIter;

};

