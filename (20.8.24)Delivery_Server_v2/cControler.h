#pragma once
#include "Resource.h"
#include "cInitserver.h"
#include "cUser.h"
#include "cUserManager.h"
#include "cSessionManager.h"
#include "cDatabase.h"
#include "Packet.h"
#include "Log.h"
class cControler
{
public:
	cControler();
	~cControler();
	void SetSOCK();
	void Playserver(); 
	void OutSession(cSession* _session);
	void DataAnalysis(PACKET_HEAD* _recvpacket, cSession* _session);
	HANDLE getHcp();
private:
	cInitserver mInitserver;
	HANDLE mHCP;
	SOCKET mListensock;
	cUserManager mUManager;
	cSessionManager mSManager;
	cDatabase mDatabase;
	 

};

