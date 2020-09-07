#pragma once
#include "resource.h"
#include "cUsersReq.h"
class cIOCP
{
public:
	cIOCP();
	~cIOCP();
	void Init_Server();
	void MakeThread();
	void MakeCP();
	void WorkerThread();
	void Acceptor();
	
private:
	SOCKET mListenSock;
	HANDLE mHCP;
	
};

