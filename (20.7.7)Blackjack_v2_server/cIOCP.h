#pragma once
#include "resouce.h"
#include "cSession.h"
class cIOCP
{
public:
	cIOCP();
	~cIOCP();
	void Init();
	void MakeThread();
	void MakeCompletionport();
	void AcceptClient();
	void WorkerThread();
	virtual void Parsing(int _packetCmd, OVERDATA* _over) = 0;
private:
	CRITICAL_SECTION cs;
	SOCKET mClient_sock;
	SOCKADDR_IN mClient_addr;
	SOCKET mListen_sock;
	HANDLE mHCP;
};

