#pragma once
#include "cThread.h"
#include "cCPhanle.h"
#include "cAccept.h"
#include "cUser.h"
#include "cSessionManager.h"
#include "cUserManager.h"
#include "Packet.h"
#include "cRoomManager.h"
#include "cDataBase.h"

class cServer : public cThread
{
public:
	cServer();
	~cServer();
	void Workerthread();
	void Acceptor();
	void DataAnalysis(cSession* _session,PACKET_HEAD* _recvpacket);
private:
	cDatabase mDatabase;
	cRoomManager mRoomManager;
	cUserManager mUserManager;
	cSessionManager mSessionManager;
	cCPhanle mCPhandle;
	cAccept mAccept;
};

