#pragma once
#include "resource.h"
#include "cSession.h"
#include "cUser.h"
class cIOCP
{
public :
	cIOCP();
	~cIOCP();
	void InitServer();
	void MakeThread();
	void MakeHcp();
	void Acceptor();
	void Workerthrad();
private:
	cSession* mUserArray[10];
	int mUsercount;
	SOCKET mListensock;
	HANDLE mHcp;
	HANDLE mEventhandle;
	cUser mUserclass;
};

