#pragma once
#include <iostream>
#include <WinSock2.h>
#include <map>
#include <time.h>
#pragma comment (lib, "ws2_32.lib")



#define serverip "192.168.43.208"

#define PORT 7296
#define BUFFER_SIZE 1024


#define FLEG_ACCEPT 0
#define FLEG_RECV 1
#define FLEG_SEND 2


#define USER_PASSWORD_ERROR 0
#define USER_NO_DATA_ERROR -1

using namespace std;

struct OVERDATA {
	OVERLAPPED mSOCKETover;
	WSABUF mSOCKETbuf;
	char mDatabuf[BUFFER_SIZE];
	int mSOCKETworkflag;
};

enum PROTOCOL {
	MSG_LOGIN_REQ = 0,
	MSG_NEWUSER_REQ,
	MSG_ROOMLIST_REQ,
	MSG_MAKEROOM_REQ,
	MSG_ENTERROOM_REQ,
	MSG_OUTROOM_REQ,
	MSG_PLAER_READY_REQ,
	MSG_HIT_REQ,
	MSG_STAND_REQ,
	MSG_RESULT_REQ,
	MSG_REGAME_REQ


};

struct USERDATA {
	int mUserNum;
	char mName[10];
	int mPassword;
	int mMoney;
	USERDATA* mNextData;
};

struct PACKET_HEAD {
	int mCmd;
	int mPacketSize;
};
struct PACKET_USERDATA
{
	char mName[10];
	int mPassword;
};

struct PACKET_ENTERROOM
{
	int mEnterRoomNum;
};

struct PACKET_READY
{
	bool mReady;
};

struct PACKET_ROOMINFO
{
	int mRoomcount;
	int mRoominfo[6] = {0,};
	bool mStartFleg[6] = { false, };
};
struct PACKET_RESULT
{
	bool mResult;//WIN TRUE , LOSE FALSE;
	int mBattingMoney;
};
struct PACKET_STAND
{
	bool mStandRsult;//WIN TRUE , LOSE FALSE;
	 
};
struct PACKET_CARD
{
	int mIntCardCount = 0;
	int mCharCardCount = 0;
	int mINTCardArray[2] = {0,};
	char mCHARCardArray[2] = {0,};
	int mCardScore=0;
};