#pragma once
#include "Resource.h"
#include "cSession.h"
#include "cLog.h"
#include "cCriticalSection.h"
class cSessionManager
{
public:
	cSessionManager();
	~cSessionManager();
	bool CheckEmptyArray();
	void InputSession(cSession* _session);
	void DelteSession(int _index);
	
private:
	cCriticalSection mCS;
	int mSessionCount;
	cSession* mSessionArray[MAX_SESSION_ARRAY] = { NULL, };
	
};

