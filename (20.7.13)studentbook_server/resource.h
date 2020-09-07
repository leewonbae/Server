#pragma once
#include <iostream>
#include <WinSock2.h>
#include <fstream>
#include <map>
#pragma comment (lib,"ws2_32.lib")

using namespace std;

#define BUFFER_SIZE 1024
#define PORT 7296
#define FLEG_SEND 1
#define FLEG_RECV 0
#define FLEG_ACCEPT 2

struct OVERDATA {
	OVERLAPPED mOver;
	WSABUF mWbuf;
	char mDatabuf[BUFFER_SIZE];

};
struct sStudentInfo {
	char mName[10];
	int mGrade; // ÇÐ³â
	int mClassNum; //¹Ý
	int mMyNum;
	int mMathNum;
	int mScienceNum;
	int mSocialNum;
	int mKoreanNum;
	 
};

enum ePROTOCOL {
	MSG_MAKE_STUDENTBOOK_REQ = 0,
	MSG_UPDATA_DATA_REQ,
	MSG_DOWNLOAD_REQ,

};

struct PACKET_HEAD {
	int mCmd;
	int mPacketSize;


};
struct PACKET_STUDENTBOOK {
	char mFileName[20];
	int mFilesize;
	char mFile[500];
};
struct PACKET_DOWNLOAD {
	int mGrade;
	int mClassNum;
	int mFilesize;
	char* mFile;
};
