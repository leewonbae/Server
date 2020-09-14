#pragma once
#include "Resource.h"
#include "cSession.h"
#include "cSessionManager.h"
#include "cUserManager.h"
#include "Packet.h"
#include "cAcceptor.h"
#include "cIOCPhandle.h"

class cServer
{
public:
	cServer();
	~cServer();

	void ClientAccept();
	void PacketParsing(cSession* _session,PACKET_HEAD* _recvpacket);
	void ClientOut(cSession* _session);
	void SendUserManager(cUser* _user);
	HANDLE getHandle();
private:
	cAcceptor mAcceptor;
	cIOCPhandle mHandle;
	cSessionManager mSessionManager;
	cUserManager mUserManager;
};

