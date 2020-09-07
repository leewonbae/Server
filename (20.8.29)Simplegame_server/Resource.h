#pragma once
#include <iostream>
#include <WinSock2.h>
#include <map>
#include <stdarg.h>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

#define BUFFER_SIZE 1024
#define PORT 7296

#define WORK_FLEG_SEND 1
#define WORK_FLEG_RECV 0

#define MANAGER_TYPE_SM 0
#define MANAGER_TYPE_UM 1
#define MANAGER_TYPE_RM 2

 

struct OVERDATA {
	OVERLAPPED mOverlapped;
	WSABUF mWsabuf;
	char mDatabuf[BUFFER_SIZE];
	int mWork_fleg;

};

