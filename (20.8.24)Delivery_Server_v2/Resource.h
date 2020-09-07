#pragma once
#include <iostream>
#include <WinSock2.h>
#include <map>
#include <stdarg.h>
using namespace std;
#pragma comment (lib,"ws2_32.lib")

#define BUFFER_SIZE 1024
#define PORT 7296


#define FLEG_RECV 0
#define FLEG_SEND 1
#define FLEG_ACCEPT 2

#define SESSION_ARRAY 50

#define USER_TYPE_USER 0
#define USER_TYPE_MASTER 1


struct OVERDATA {
	OVERLAPPED mOverlapped;
	WSABUF mWsabuf;
	char mDatabuf[BUFFER_SIZE];
	int mWorkFleg;
};


enum PROTOCOL {
	PROTO_HEAD,
	PROTO_LOGIN_REQ,
	PROTO_NEWUSER_REQ,
	PROTO_MENULIST_REQ,
	PROTO_USER_ORDER_REQ,

};
enum ACK_MSG {
	MSG_HEAD,
	MSG_LOGIN_OK,
	MSG_LOGIN_FAIL,
	MSG_NEWUSER_OK,
	MSG_NEWUSER_FAIL,
	MSG_ORDER_CALL,
	MSG_ORDER_OK,
	MSG_ORDER_FAIL,
	
};