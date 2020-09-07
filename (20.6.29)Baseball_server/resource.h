#pragma once
#include <iostream>
#include <WinSock2.h>

#pragma comment (lib,"ws2_32.lib")
using namespace std;
#define FLAG_SEND 1
#define FLAG_RECV 0
#define BUFFER_SIZE 1024
#define PORT 7296

enum class PROTOCOL {
	pro_start,
	pro_ready,
	pro_target,
	pro_result,


};
struct PACKET_HEAD {
	PROTOCOL p_cmd;
	int packet_size;

};
struct sTarget
{
	int _targetNum;
};
struct sResult
{
	int _resultNum;
	// 1 = win 2 = drew 3 = lose
};

struct SOCKETINFO {
	OVERLAPPED _overlapped;
	SOCKET _sock;
	char _databuf[BUFFER_SIZE];
	WSABUF _wsabuf;
	int _workflag;


};