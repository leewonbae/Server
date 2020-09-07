#pragma once
#include "resource.h"
struct NODE
{
	PACKET_LOGIN mLogindata;
	bool mReserveOk = false;
	int mRoomNumber;
	NODE* nextnode=NULL;
};



class cDatabase
{
public:
	cDatabase();
	~cDatabase();
	void InputData(PACKET_LOGIN _logindata);
	bool CheckReserv(PACKET_LOGIN _checkdata);
	void ReservationRoom(int _roomnum, int _usercount, PACKET_LOGIN _checkdata);
	int* getroomuser();
	int getroomnumber(PACKET_LOGIN _checkdata);
private:
	int mDBcount;
	int mRoomUser[5] = { 0, };
	NODE* mHead;
	NODE* mTail;

};

