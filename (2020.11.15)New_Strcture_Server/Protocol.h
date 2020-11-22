#pragma once
#include "Resource.h"


struct ITEM_INFO {
	bool mUpdateArray[MAX_ITEM_LIST] = { false, };
	int mItemArray[MAX_ITEM_LIST] = { 0, };
};
struct GAME_RECONRD_INFO {
	int mWinCount = 0;
	int mLoseCount = 0;
	int mDrawCount = 0;
};
struct USER_INFO {
	ITEM_INFO mItem_info;
	GAME_RECONRD_INFO mGame_info;
};

enum PROTOCOL {
	// 게임 오브젝트와 관련된 패킷
	PTC_HEAD,
	
	PTC_NEWUSER,
	PTC_LOGIN,
	

	PTC_ROOM,// 방관련 패킷 
	PTC_MAKEROOM_REQ,
	PTC_INOUT_ROOM_REQ,
	PTC_ROOMLIST_REQ,
	PTC_READY_REQ,

	PTC_ATTCK_REQ,
	PTC_PERSONAL,
	

	PTC_SEND_GAMESTATE_ACK,
};
class PACKET_HEAD
{
public:
	int mCmd;
	int mPacket_size;
	int mPacket_ACK;
};
class PACKET_ATTACK : public PACKET_HEAD
{
public:
	PACKET_ATTACK()
	{
		mCmd = PTC_ATTCK_REQ;
		mPacket_ACK = 0;
		mPacket_size = sizeof(PACKET_ATTACK);

	}
	bool mUseItem = false;
	int mItemNum = 0;
	int mRemainHp = 0;
	int mAttack_Damage = 0;
};



class PACKET_READY : public PACKET_HEAD
{
public:
	PACKET_READY()
	{
		mCmd = PTC_READY_REQ;
		mPacket_ACK = 0;
		mPacket_size = sizeof(PACKET_READY);

	}
	bool mReadyReq = false;
};




class PACKET_GAMESTATE : public PACKET_HEAD
{
public:
	PACKET_GAMESTATE()
	{
		mCmd = PTC_SEND_GAMESTATE_ACK;
		mPacket_ACK = 0;
		mPacket_size = sizeof(PACKET_GAMESTATE);

	}
	int mGameState = 0;// 1 이면 게임 시작, 2이면 게임종료 0이면 대기
	int mGameRoomNum = 0;
	int mResult = 0;
	
	// mresult ==1 ->lose
	// mresult ==2 ->win
	// mresult ==0 -> draw
};



class PACKET_ROOMLIST : public PACKET_HEAD
{
public:
	PACKET_ROOMLIST()
	{
		mCmd = PTC_INOUT_ROOM_REQ;
		mPacket_ACK = 0;
		mPacket_size = sizeof(PACKET_ROOMLIST);

	}
	int mRoomlist[MAX_ROOM_SIZE] = { 0, };

};

class PACKET_INOUT : public PACKET_HEAD
{
public:
	PACKET_INOUT()
	{
		mCmd = PTC_INOUT_ROOM_REQ;
		mPacket_ACK = 0;
		mPacket_size = sizeof(PACKET_INOUT);

	}
	int mRoomnum=0;
	bool mCheckInOut = false;// DEFINE true = in false =out 
};

class PACKET_MAKEROOM : public PACKET_HEAD
{
public:
	PACKET_MAKEROOM()
	{
		mCmd = PTC_MAKEROOM_REQ;
		mPacket_ACK = 0;
		mPacket_size = sizeof(PACKET_MAKEROOM);
		mRoomnum = -1;
	} 
	int mRoomnum;
};
class PACKET_LOGIN : public PACKET_HEAD
{
public:
	PACKET_LOGIN()
	{
		mCmd = PTC_LOGIN;
		mPacket_ACK = 0;
		mPacket_size = sizeof(PACKET_LOGIN);

	}
	char mID[10] = { 0, };
	int mPassword = 0;
};

class PACKET_NEWUSER : public PACKET_HEAD
{
public:
	PACKET_NEWUSER()
	{
		mCmd = PTC_NEWUSER;
		mPacket_ACK = 0;
		mPacket_size = sizeof(PACKET_NEWUSER);
	
	}
	char mNew_ID[10] = { 0, };
	int mNew_Password = 0;
};