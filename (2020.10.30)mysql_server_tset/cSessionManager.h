#pragma once
#include "Resource.h"
#include "cSession.h"
#include "Packet.h"
#include "cUserDBA.h"
#include "cCriticalSection.h"
class cSessionManager
{
public:
	cSessionManager();
	~cSessionManager();

	bool InputSession(cSession* _session);
	void OutSession(cSession* _session);
	void SessionManager_Parsing(cSession* _session, PACKET_HEAD* _phead);

private:
	cSession* mSessionArray[MAX_SESSION_ARRAY] = {NULL,};
	cCriticalSection mCS;
	cUserDBA mUserDba;
	int mSessionCount;
};

