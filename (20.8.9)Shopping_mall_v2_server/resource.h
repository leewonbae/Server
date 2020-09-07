#pragma once
#include <iostream>
#include <WinSock2.h>
#include <map>
#include "cLog.h"
#pragma comment (lib,"ws2_32.lib")

using namespace std;

#define BUFFER_SIZE 1024
#define PORT 7296

#define FLEG_SEND 1
#define FLEG_RECV 0
#define FLEG_ACCEPT 2

struct OVERLAPPED_DATA {
	OVERLAPPED mOverLapped;
	WSABUF mWsabuf;
	char mDatabuf[BUFFER_SIZE];
	int mFlegMode;
};

enum PROTOCOL {
	PRO_LOGIN_REQ = 0,
	PRO_NEWUSER_REQ,
	PRO_LOAN_LIST_REQ,
	PRO_ADD_LOAN_REQ,
	PRO_BUY_LOAN_REQ,

	MSG_LOGIN_TRUE,
	MSG_LOGIN_FALSE,
	MSG_NEWUSER_OK,
	MSG_BUY_OK,
	MSG_ADD_OK,
};
struct PACKET_HEAD {
	int mHeadCmd;
	int mPacket_size;


};
struct PACKET_NEWUSER {
	char mNEW_ID[10];
	int mNEW_Password;


};
struct PACKET_LOGIN {
	char mLOGIN_ID[10];
	int mLOGIN_Password;

};
struct PACKET_BUYLOAN {
	int mSortNum;
	int mBuyCount;


};
struct PACKET_ADDLOAN {
	char mTitle[20];
	int mAddCount;
};
struct LOAN {
	char mTitle[20];
	int mCount;
};

struct PACKET_LOANLIST {
	int mLoancount;
	LOAN mLoansort[20];

};