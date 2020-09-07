#pragma once
#include "resouce.h"
#include "cSession.h"
class cRoom
{
public:
	cRoom();
	~cRoom();
	bool ReadyInput(cSession* _user);// 전원 레디 
	bool outUser(cSession* _user);
	bool CheckStand(cSession* _user);
	void EnterUser(cSession* _user);// 유저 입장
	int getUserCount();
	bool getStartfleg();
	void setStartFleg(bool _setfleg);
	void setRoomNum(int _roomnum);
	cSession** getUserArry();
private:
	int mRoomNumber;
	bool mStartfleg;
	int mUserCount;
	cSession* mUserArry[4];
	bool mReadyArry[4];
	bool mStandArry[4];
};

