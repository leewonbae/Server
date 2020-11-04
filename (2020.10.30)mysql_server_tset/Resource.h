#pragma once
#include <WinSock2.h>
#include <mysql.h>
#include <string>
#include <iostream>
#include <map>

#pragma comment (lib,"libmysql.lib")
#pragma comment (lib,"ws2_32.lib")


#define MAX_SESSION_ARRAY 50
#define MAX_ROOM_COUNT 10



#define BUFFER_SIZE 1024
#define PORT 7296
#define DB_ID "root"
#define DB_HOST "127.0.0.1"
#define DB_NAME "TEST_SERVER"
#define DB_PASSWORD "814dnjsqo*"
#define DB_PORT 3306

#define WORKFLEG_SEND 0
#define WORKFLEG_RECV 1
#define WORKFLEG_ACCEP 2
 
#define ITEM_MAX_SIZE 3
using namespace std;

struct OVERDATA {
	OVERLAPPED mOverlapped;
	WSABUF mWsabuf;
	char mDatabuf[BUFFER_SIZE];
	int mWorkFleg;


};

enum TBL_NAME {
	// 회원 테이블
	TBL_USERINFO = 0,

	// 아이템 관련
	CONSUMPTION_TBL,
	ITEM_ETC_TBL,
	WAPONE_TBL,

	// 로그 관련
	USER_INFO_LOG,

};