#pragma once
#include "Resource.h"


enum PROTOCOL {
	PTC_HEAD,

	 
	PTC_LOGIN_REQ,// 게임 회원 관련
	PTC_MATCHING_REQ,// 게임 매칭 관련
	PTC_GAMEINFO_REQ,//게임 정보 관련
	PTC_RESULT_SAVE_REQ,// 결과 반영 관련





};
enum MSG_PROTOCOL {
	MSG_HEAD,

	MSG_LOGIN_OK,
	MSG_LOGIN_FAIL,

	MSG_NEWUSER_OK,
	MSG_NEWUSER_FAIL,
	
	MSG_START_WAITING,
	MSG_MATCH_OK,
	MSG_CANCLE_OK,

	MSG_GAMEINFO_OK,
	MSG_GAMEINFO_FAIL,

	MSG_RESULT_OK,
	MSG_RESULT_FAIL,




};
class PACKET_HEAD {
public:
	int mCmd;
	int mPacket_size;
	int mPacket_msg;
};
class PACKET_GAMEINFO : public PACKET_HEAD
{
public:
	PACKET_GAMEINFO()
	{
		mCmd = PTC_GAMEINFO_REQ;
		mPacket_size = sizeof(PACKET_GAMEINFO);
		mPacket_msg = 0;
	}
	int mSendCount = 0;
	int mNumArray[3] = { 0, };
	 
};
class PACKET_MATCHING : public PACKET_HEAD
{
public:
	PACKET_MATCHING()
	{
		mCmd = PTC_MATCHING_REQ;
		mPacket_size = sizeof(PACKET_MATCHING);
		mPacket_msg = 0;
	}
	bool CheckReq;// startreq -> true , canclereq -> false 
};
class PACKET_LOGIN : public PACKET_HEAD
{
public:
	PACKET_LOGIN()
	{
		mCmd = PTC_LOGIN_REQ;
		mPacket_size = sizeof(PACKET_LOGIN);
		mPacket_msg = 0;
	}
	char ID[10];
	int Password;
	bool NewUser;
};
class PACKET_RESULT : public PACKET_HEAD
{
public:
	PACKET_RESULT()
	{
		mCmd = PTC_RESULT_SAVE_REQ;
		mPacket_size = sizeof(PACKET_RESULT);
		mPacket_msg = 0;
	}
	bool result; // true면 윈, false 짐
	
};
 
 