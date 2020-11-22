#pragma once
#include "Resource.h"
 
#include "cAcceptor.h"
#include "cSessionManager.h"
#include "cIOCPhandle.h"
class cServer  
{
public:
	cServer();
	~cServer();

	HANDLE getHANDLE() { return mIOCPhandle.getHCP(); }
	// init
	void InitServer();
	
	// accept client
	void MainAccept();

	// out client
	void OutSession(cSession* _session);



private:
	cIOCPhandle mIOCPhandle;
	cSessionManager mSessionManager;
	SOCKET mListensock;
};

