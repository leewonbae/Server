#pragma once
#include "resource.h"
#include "cUser.h"

class cIOCP
{
public:
	cIOCP();
	~cIOCP();
	void InitServer();
	void MakeThread();
	void MakeHCP();
	void Acceptor();
	void WorkerThread();

	
private:
	
	SOCKET mListenSock;
	HANDLE mHcp;
	

};

