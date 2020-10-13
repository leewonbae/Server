#pragma once
#include "cLog.h"

class cCriticalSection
{
public:
	cCriticalSection()
	{
		InitializeCriticalSection(&cs);
	}
	~cCriticalSection()
	{
		DeleteCriticalSection(&cs);
	}
	void LockCs()
	{
		EnterCriticalSection(&cs);
		cLog::Print_log("CS LOCK");
	}
	void UnLock()
	{
		LeaveCriticalSection(&cs);
		cLog::Print_log("CS UNLOCK");
	}
private:
	CRITICAL_SECTION cs;


};