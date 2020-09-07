#pragma once
#include "resource.h"
class cIOCP
{
public:
	cIOCP();
	~cIOCP();
	void InitServer();
	void MakeCP();
	void MakeThread();
	void AcceptClient();

	void OnRecv(SOCKETINFO* _ptr);
	void OnSend(SOCKETINFO* _ptr);
	
	
	void WorkerThread();
	
	virtual void Parsing(SOCKETINFO* _ptr) = 0;
 
private:
	CRITICAL_SECTION cs;
	SOCKET mListenSock;
	HANDLE mHcp;

};

