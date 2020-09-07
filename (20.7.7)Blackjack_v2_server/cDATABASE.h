#pragma once
#include "resouce.h"


class cDATABASE
{
public:
	cDATABASE();
	~cDATABASE();

	int FindData(PACKET_USERDATA* _userdata);
	void InputData(USERDATA* _userdata);
	void ShowRankData();// money기 준으로 정렬 해서 

	USERDATA* getUSER(int _usernum);
private:
	int mUserCount;
	USERDATA* mHead;
	USERDATA* mTail;
};

