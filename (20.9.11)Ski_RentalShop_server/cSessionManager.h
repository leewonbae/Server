#pragma once
#include "Resource.h"
#include "cSession.h"
#include "cUserDB.h"
#include "Packet.h"
#include "cCriticalSection.h"
class cSessionManager
{
public:
	cSessionManager();
	~cSessionManager();

	void SessionParsing(int _key, PACKET_HEAD* _recvpacket);
	void InputSession(SOCKET _SOCK, cSession* _session);
	void DeleteSession(int _key);
	void ShowCount();
	
private:
	cUserDB mUserDB;
	cCriticalSection mCS;
	cSession* mSessionArray[50] = { NULL, };
	int mSessionCount;
};

