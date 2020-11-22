#pragma once
#include <WinSock2.h>
#include <iostream>
#include <mysql.h>
#include <vector>
#include <string>
#include <map>

using namespace std;

#pragma comment (lib,"ws2_32.lib")
#pragma comment (lib,"libmysql.lib")

#define PORT 7296
#define BUFFER_SIZE 1024


#define FLAG_RECV 0
#define FLAG_SEND 2
 
#define DB_ID "root"
#define DB_HOST "127.0.0.1"
#define DB_NAME "TEST_SERVER"
#define DB_PASSWORD "814dnjsqo*"
#define DB_PORT 3306
//////////////////////////////////////////////////
#define PACKET_TRUE 1
#define PACKET_FAIL 2

#define MAX_ROOM_SIZE 50
#define MAX_SESSION_SIZE 50
#define MAX_ITEM_LIST 10

#define GAMESTATE_START 1
#define GAMESTATE_END 2
#define GAME_RESULT_WIN 1
#define GAME_RESULT_LOSE 2
#define GAME_RESULT_DRAW 0

#define INFO_CASE_ITEM 1
//////////////////////////////////////////////////
struct OVERDATA {
	OVERLAPPED mOverlapped;
	WSABUF mWsabuf;
	int mWorkFlag;
};

