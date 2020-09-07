#pragma once
#include "resource.h"
#include "cUser.h"
#include "cSessionManager.h"
#include "cUserManager.h"
class cIOCP
{
public:
	cIOCP();
	~cIOCP();
	void Play();
	void InitServer();
	void MakeThread();
	void MakeHCP();
	void WorkerThread();
	void Acceptor();
private:
	SOCKET mListensock;
	HANDLE mHCP;
};

