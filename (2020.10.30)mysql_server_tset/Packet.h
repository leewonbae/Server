#pragma once
#include "Resource.h"

enum PROTOCOL
{
	PTC_HEAD = 1,
	// 로그인 관련
	PTC_LOGIN,

	// 아이템 관련
	PTC_ITEM_UPLOAD,

	// 방 관련
	PTC_ROOM_MAKE,
	PTC_ROOM_IN_OUT,
	PTC_ROOM_LIST,
	PTC_READY_CHECK_CANCLE,
	// 게임 관련
	PTC_GAME_CHECK,
	PTC_GAME_DATA,
	 
};


enum MSG_PROTOCOL
{
	MSG_HEAD = 1,
	MSG_LOGIN_OK,
	MSG_LOGIN_FAIL,

	MSG_NEWUSER_FAIL,
	MSG_NEWUSER_OK,

	MSG_ITEM_USE_OK,
	MSG_ITEM_USE_FAIL,

	MSG_ITEM_UPDATE_OK,
	MSG_ITEM_UPDATE_FAIL,

	MSG_GAME_START,
	MSG_GAME_OVER,

	MSG_IN_OK,
	MSG_IN_FAIL,
	MSG_OUT_OK,
	MSG_OUT_FAIL,
	MSG_MAKE_ROOM_FAIL,
	MSG_MAKE_ROOM_OK,
	MSG_READY_OK,
	MSG_READY_CANCLE_OK,
	
};


class PACKET_HEAD {
public:
	int mCmd;
	int mPacket_size;
	int mMsg;
};

class PACKET_ROOM_IN_OUT : public PACKET_HEAD {
public:
	PACKET_ROOM_IN_OUT()
	{
		mCmd = PTC_READY_CHECK_CANCLE;
		mPacket_size = sizeof(PACKET_ROOM_IN_OUT);
		mMsg = 0;
	}
	bool InOutFlag = false;
	int mWantInRoom; 
	// false = out true = in/
	 

};

class PACKET_READY : public PACKET_HEAD {
public:
	PACKET_READY()
	{
		mCmd = PTC_READY_CHECK_CANCLE;
		mPacket_size = sizeof(PACKET_READY);
		mMsg = 0;
	}
	
	bool mReadyFlag = false;
	bool mGameStartFlag = false;
	
	// true = ready req, false = ready cancle req//

};


class PACKET_ROOM_LIST : public PACKET_HEAD {
public:
	PACKET_ROOM_LIST()
	{
		mCmd = PTC_ROOM_LIST;
		mPacket_size = sizeof(PACKET_ROOM_LIST);
		mMsg = 0;
	}
	int mInRoomUserCount[MAX_ROOM_COUNT] = { 0, };
	 

};

class PACKET_GAME_CHECK : public PACKET_HEAD {
public:
	PACKET_GAME_CHECK()
	{
		mCmd = PTC_GAME_CHECK;
		mPacket_size = sizeof(PACKET_GAME_CHECK);
		mMsg = 0;
	}
	 
	
};

class PACKET_ITEM_UPLOAD : public PACKET_HEAD {
public:
	PACKET_ITEM_UPLOAD()
	{
		mCmd = PTC_ITEM_UPLOAD;
		mPacket_size = sizeof(PACKET_ITEM_UPLOAD);
		mMsg = 0;
	}
	bool mUSEandGET = false;// use = false , get = true;
	char mITEM_NAME[20] = { 0, };
	int mItemKinds = 0;
	int mItemCount = 0;
};



 
class PACKET_LOGIN  : public PACKET_HEAD{
public:
	PACKET_LOGIN()
	{
		mCmd = PTC_LOGIN;
		mPacket_size = sizeof(PACKET_LOGIN);
		mMsg = 0;
	}
	char mName[10] = {0,};
	int mPassword;
	int mLoginCheck = false;
	// false 는 회원가입  true 는 로그인
};