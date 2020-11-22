#pragma once
#include "Resource.h"
#include "cSession.h"
#include "Protocol.h"
 

class cUser : public  cSession
{
public:
	cUser();
	~cUser();

	void setDBnum(int _dbnum) { mDBnum = _dbnum; }
	int getDBnum() { return mDBnum; }
	int getHp(int _damage) { return mHP -=_damage; }
	void ClearHp() { mHP = 100; }
	void setRoomNum(int _roomnum) { mRoomnum = _roomnum; }
	int getRoomNum() { return mRoomnum; }
	void SetGameResult(int _result);
	USER_INFO* getUserinfo() { return &mUserinfo; }
	 
	
	typedef void (cUser:: *fp)(PACKET_HEAD* _phead);
	void Parsing(PACKET_HEAD* _phead);



private:
	map<int, fp> mPacketMap;
	map<int, fp>::iterator mPacketIter;

	void Newuser_Req(PACKET_HEAD* _phead);
	void Login_Req(PACKET_HEAD* _phead);
	void MAKEROOM_REQ(PACKET_HEAD* _phead);
	void INOUT_ROOM_REQ(PACKET_HEAD* _phead);
	void ROOMLIST_REQ(PACKET_HEAD* _phead);
	void READY_REQ(PACKET_HEAD* _phead);
 

	USER_INFO mUserinfo;
	int mHP = 100;
	int mRoomnum = -1;
	int mDBnum=0;
};

