#pragma once
#include <iostream>

#include <WinSock2.h>
#include <cstring>
#pragma comment (lib,"ws2_32.lib")
using namespace std;

#define BUFFER_SIZE 1024
#define PORT 7296


#define FLAG_SEND 1
#define FLAG_RECV 0


enum ACT_RIST {

	act_room = 0,
	act_inRoom,
	act_makeRoom,
	act_ready,
	act_word,
	act_end,
	act_echo,
	act_start,
	act_turncheck,
};
struct SEND_ROOMINFO {
	int roomcount;
	int roomlist[10];


};
struct DATA_INFO {
	int _msg_number;
	char _data[BUFFER_SIZE];

};
struct SOCKETINFO {
	OVERLAPPED _overlapped;
	SOCKET _sock;
	WSABUF _wsabuf;
	DATA_INFO _d_info;
	int _workerflag;
	int _roomNumber;
	 
};
struct START_ROOM_SEND_DATA {
	bool Playflag;
	int user_count;
	char startword[7];
};

struct START_ROOM_INFO {
	SOCKETINFO** User_list;
	int s_user_count;
	int s_play_user;
	START_ROOM_SEND_DATA STSD;

};