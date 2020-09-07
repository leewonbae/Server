#pragma once
#include <iostream>
#include <WinSock2.h>
#include <map>
#include <time.h>
#include <stdarg.h>
#pragma comment (lib,"ws2_32.lib")

using namespace std;

#define BUFFER_SIZE 1024
#define PORT 7296

#define WORK_FLEG_SEND 1
#define WORK_FLEG_RECV 0

enum PROTOCOL {
	PRO_LOGIN_REQ = 0,
	PRO_NEWUSER_REQ,
	PRO_MAKEROOM_REQ,
	PRO_ROOMLIST_REQ,
	PRO_INROOM_REQ,
	PRO_READY_REQ,
	PRO_START_REQ,
	PRO_CARD_REQ,
	PRO_BATTING_REQ,
	PRO_RESULT_REQ,
	PRO_GAME_END_REQ,
	MSG_LOGIN_OK,
	MSG_LOGIN_FAIL,
	MSG_READY_OK,
	MSG_READY_FAIL,
	MSG_PLAY_OK,
};



struct OVERDATA {
	OVERLAPPED mOverlapped;
	WSABUF mWsabuf;
	char mDatabuf[BUFFER_SIZE];
	int mWorkFleg;
};

struct PACKET_HEAD {
	int mProtocol_cmd;
	int mMsg_cmd;

};
struct PACKET_USERINFO {
	char mName[20];
	int mPassword;

};
struct PACKET_ROOMLIST {
	int mRoomUser[20];
	int mRoomcount;

};
struct PACKET_IN_ROOM {
	int roomnum;

};
struct PACKET_ENEMYCARD {
	int mCardnum;
};
struct PACKET_BATTING {
	int mBatiing_money;
	int mBatting_mycard;
};