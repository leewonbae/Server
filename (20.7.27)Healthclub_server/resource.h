#pragma once
#include <iostream>
#include <WinSock2.h>
#include <map>


#pragma comment (lib,"ws2_32.lib")
using namespace std;

#define PORT 7296
#define BUFFER_SIZE 1024

#define FLEG_SEND 1
#define FLEG_RECV 0
#define FLEG_ACCEPT 2

#define CONNECT_ON 1
#define CONNECT_OFF 0



enum PROTOCOL {
	
	MSG_NEWUSER_REQ,
	MSG_LOGIN_REQ,
	
	MSG_NOTICE_CHECK_REQ,
	MSG_DATA_REQ,
	MSG_NOTICE_SEND_REQ,
	MSG_DATA_SEND_REQ,
};
struct OVERDATA
{
	OVERLAPPED mOver;
	WSABUF mWsabuf;
	char mDatabuf[BUFFER_SIZE];
};

struct PACKET_HEAD {
	int mCmd;
	int mEtc;


};
struct PACKET_CHECKUSER {
	bool mCheckUser;


};
struct PACKET_NOTICECOUNT {
	int mNoticecount;
};
struct PACKET_USERDATA {
	char mName[20];
	int mPassword;
};
struct PAKCET_NOTICE {
	char mTitle[40];
	char mData[100];


};
struct NODE {

	PACKET_USERDATA mUserdata;
	NODE* mNextnode;

};
struct NOTICE_NODE {

	PAKCET_NOTICE mNoticedata;
	NOTICE_NODE* mNextnode;

};