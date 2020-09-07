#pragma once
#include "cSession.h"
#include "Resource.h"
#include "Packet.h"
#include "Log.h"
class cSessionManager
{
public:
	cSessionManager();
	~cSessionManager();

	bool InputSession(cSession* _session);
	void DelteSession(int _key);
	void SessionParsing(int _key, PACKET_HEAD* _phead);
	void ShowSessionCount();
private:
	cSession* mSessionArray[50] = {NULL,};
	int mSessioncount;
	int mkeycount;
};

