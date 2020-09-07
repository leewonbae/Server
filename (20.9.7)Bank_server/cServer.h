#pragma once
#include "Resource.h"
#include "cIOCPhandle.h"
#include "cUser.h"
#include "cSessionManager.h"
#include "Packet.h"
#include "cAcceptor.h"
#include "cDataBase.h"
#include "cUserManager.h"
#include "cCriticalSection.h"

class cServer
{
public:
	cServer();
	~cServer();

	void MakeThread();
	void ObjectInit();
	void WorkerThread();
	void AcceptClient();
	void DataAnalysis(PACKET_HEAD* _recvpacket, cSession* _session);


private:
	cSessionManager mSessionManager;
	cUserManager mUserManager;
	cDataBase mDataBase;
	cIOCPhandle mIOCPhandle;
	cAcceptor mAcceptor;
};

