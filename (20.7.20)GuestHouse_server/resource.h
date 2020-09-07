#pragma once
#include <iostream>
#include <WinSock2.h>
#include <map>
#pragma comment (lib,"ws2_32.lib")
using namespace std;

#define BUFFER_SIZE 1024
#define PORT 7296

#define FLEG_RECV 1
#define FLEG_SEND 0


#define LOGIN_RESERVATION_OK 22
#define LOGIN_RESERVATION_NO 11


struct OVERDATA {
	OVERLAPPED mOver;
	WSABUF mWbuf;
	char mDatabuf[BUFFER_SIZE];

};
enum PROTOCOL {
	MSG_LOGIN_REQ=0,
	MSG_ROOM_INFO,
	MSG_RESERVATION_INFO,
	MSG_ROOMCHATTING_REQ,

};
struct PACKET_HEAD
{
	int mCmd;
	int mPacketsize;
};
struct PACKET_LOGIN
{
	char name[10];
	int password;
};
struct PACKET_ROOMINFO
{
	int mUsercount[5] = { 0, };

};
struct PACKET_RESERVATION
{
	int mCoiceRoomNum;
	int mReservUserCount;
};
struct PACKET_CHATTING
{
	char mChat[100];
	int mChatsize;
};