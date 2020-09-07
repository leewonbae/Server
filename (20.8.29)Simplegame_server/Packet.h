#pragma once
#include "Resource.h"

enum PROTOCOL {
	PTC_HEAD,
	//DB 관련 패킷
	PTC_LOGIN_REQ,
	PTC_NEW_USER_REQ,
	PTC_SCORE_UPDATA_REQ,


	//룸 관련 패킷
	PTC_ROOMLIST_REQ,
	PTC_IN_ROOM_REQ,
	PTC_MAKE_ROOM_REQ,
	PTC_READY_REQ,
	PTC_GAME_RESULT_REQ,



};

enum MSG_PROTOCOL {
	MSG_HEAD,
	MSG_LOGIN_OK,
	MSG_LOGIN_FAIL,
	MSG_NEWUSER_OK,
	MSG_MAKEROOM_OK,
	MSG_MAKEROOM_FAIL,
	MSG_INROOM_OK,
	MSG_INROOM_FAIL,
	MSG_RESULT_WIN,
	MSG_RESULT_LOSE,
	MSG_RESULT_DRAW,
	MSG_START_CHECK_OK,

};
class PACKET_HEAD {
public:
	int mCmd;
	int mPacketSize;
	int mMsg;
	bool mDbNecessity;
	int mManagerType;

};
class PACKET_NEWUSER :public PACKET_HEAD
{
public:
	PACKET_NEWUSER()
	{
		mCmd = PTC_NEW_USER_REQ;
		mPacketSize = sizeof(PACKET_NEWUSER);
		mMsg = 0;
		mDbNecessity = true;
		mManagerType = MANAGER_TYPE_SM;
	}
	char mID[10];
	int mPassword;

};
class PACKET_LOGIN :public PACKET_HEAD
{
public:
	PACKET_LOGIN()
	{
		mCmd = PTC_LOGIN_REQ;
		mPacketSize = sizeof(PACKET_LOGIN);
		mMsg = 0;
		mDbNecessity = true;
		mManagerType = MANAGER_TYPE_SM;
	}
	char mID[10];
	int mPassword;

};
class PACKET_ROOMLIST :public PACKET_HEAD
{
public:
	PACKET_ROOMLIST()
	{
		mCmd = PTC_ROOMLIST_REQ;
		mPacketSize = sizeof(PACKET_ROOMLIST);
		mMsg = 0;
		mDbNecessity = false;
		mManagerType = MANAGER_TYPE_RM;
	}
	int mRoomArray[20] = { 0, };
	int mRoomcount = 0;

};
class PACKET_INROOM :public PACKET_HEAD
{
public:
	PACKET_INROOM()
	{
		mCmd = PTC_IN_ROOM_REQ;
		mPacketSize = sizeof(PACKET_INROOM);
		mMsg = 0;
		mDbNecessity = false;
		mManagerType = MANAGER_TYPE_RM;
	}
	int mChoiceRoomNum;

};
class PACKET_MAKEROOM :public PACKET_HEAD
{
public:
	PACKET_MAKEROOM()
	{
		mCmd = PTC_MAKE_ROOM_REQ;
		mPacketSize = sizeof(PACKET_MAKEROOM);
		mMsg = 0;
		mDbNecessity = false;
		mManagerType = MANAGER_TYPE_RM;
	}
};
class PACKET_READY :public PACKET_HEAD
{
public:
	PACKET_READY()
	{
		mCmd = PTC_READY_REQ;
		mPacketSize = sizeof(PACKET_READY);
		mMsg = 0;
		mDbNecessity = false;
		mManagerType = MANAGER_TYPE_RM;
	}


};
class PACKET_RESULT :public PACKET_HEAD
{
public:
	PACKET_RESULT()
	{
		mCmd = PTC_GAME_RESULT_REQ;
		mPacketSize = sizeof(PACKET_RESULT);
		mMsg = 0;
		mDbNecessity = false;
		mManagerType = MANAGER_TYPE_RM;
	}
	int mInputnum;

};