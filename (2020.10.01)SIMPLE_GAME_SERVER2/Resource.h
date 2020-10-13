#pragma once
#include <iostream>
#include <WinSock2.h>
#include <stdarg.h>
#include <map>
#pragma comment (lib,"ws2_32.lib")
using namespace std;


#define PORT 7296
#define BUFFER_SIZE 1024

#define MODE_RECV 1
#define MODE_SEND 2
#define MODE_ACCEPT 0
#define MAX_SESSION_ARRAY 50


struct OVERDATA {
	OVERLAPPED mOverlapped;
	WSABUF mWsabuf;
	char mDataBuf[BUFFER_SIZE];
	int mMODE;
 
};