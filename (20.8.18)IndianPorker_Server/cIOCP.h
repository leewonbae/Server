#pragma once
#include "resource.h"
#include "cLOG.h"
#include "cUser.h"
#include "cSessionManager.h"
#include "cUserManager.h"
#include "cUserDB.h"
class cIOCP
{
public:
	cIOCP();
	~cIOCP();
	void InitServer();
	void MakeThread();
	void MakeHcp();
	void Acceptor(cUserDB* _database);
	void WorkerThread();
private:
	SOCKET mListensock;
	HANDLE mHcp;
	cSessionManager mSessionManager;
	cUserManager mUsermanager;
};

