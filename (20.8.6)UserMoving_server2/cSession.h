#pragma once
#include "resource.h"
class cSession
{
public:
	cSession();
	~cSession();
	void Onsend(int _cmd,char* _databuf);
	void Onrecv();
	void SetSOCK(SOCKET _sock);
	void SetUserKey(int _userkey);
	int getfleg();
	int getkey();
private:
	OVERDATA mOver;
	SOCKET mSOCK;
	int mFlag;
	int mUserKey;
};

