#pragma once
#include "resource.h"
#include "cUser.h"
#include "cCard.h"

class cRoom
{
public:
	cRoom();
	~cRoom();
	int getCount();
	int getRoomnum();
	cUser** getUsers();
	void SetRoomnum(int _roomnum);
	void Makeroom(cUser* _user);
	void Inroom(cUser* _user);
	void SetStart(bool _fleg);
	bool SetReady(cUser* _user);
	bool Startcheck();
	bool DeleteReq();
private:
	cCard mMainCard;
	cUser* mUserarray[2] = {NULL,};
	bool mReadyArray[2] = { false, };
	int mUsercount;
	int mRoomNum;
	int mDeleteReqCount;
	bool mStartfleg;
};

