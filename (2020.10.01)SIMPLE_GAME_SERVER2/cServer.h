#pragma once
#include "cAcceptor.h"
#include "cIOCPhandle.h"
#include "cUser.h"
#include "cSessionManager.h"
#include "cUserManager.h"
#include "packet.h"
#include "cLog.h"
#include "cUserDB.h"
#include "cCriticalSection.h"
#include "cMatchingManager.h"

class cServer
{

public:
	cServer();
	~cServer();

	void StartServer();
	void DataParsing(PACKET_HEAD* _phead, cSession* _ptr);
	void ClientOut(int _index);
	HANDLE getHandle();
private:
	cCriticalSection mServer_CS;
	cMatchingManager mMatchingManager;
	cUserDB mUserDB;
	cUserManager mUserManager;
	cSessionManager mSessionManager;
	cAcceptor mAcceptor;
	cIOCPhandle mIOCPhandle;

};

