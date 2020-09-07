#pragma once
#include "Resource.h"
#include "cSession.h"
#include "cDataBase.h"
#include "Packet.h"
#include "cCriticalSection.h"
class cSessionManager
{
public:
	cSessionManager();
	~cSessionManager();

	void SetDataBase(cDataBase* _db);
	void InputSession(SOCKET _SOCK, cSession* _session);
	void DeleteSession(int _key);
	void ShowCount();
	void SessionParsing(int _key, PACKET_HEAD* _recvpacket);
private:
	cDataBase* mPtrDB;
	cSession* mSessionArray[50] = { NULL, };
	int mSessionCount;
};

