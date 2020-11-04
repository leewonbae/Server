#pragma once
#include "Resource.h"
#include "cAcceptor.h"
#include "cIOCPhandler.h"
#include "cUser.h"
#include "Packet.h"
#include "cUserManager.h"
#include "cSessionManager.h"

class cServer
{
public:
	cServer();
	~cServer();
	void PlayAccept();
	void Manager_Parsing(cSession* _session, PACKET_HEAD* _phead);
	void ClientOut(cSession* _session);
	HANDLE getHandle();
private:
	cSessionManager mSessionManager;
	cUserManager mUserManager;
	cAcceptor mAcceptor;
	cIOCPhandler mIOCPhandle;

};

