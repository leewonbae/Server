#pragma once
#include "Resource.h"
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
	void lock()
	{
		EnterCriticalSection(&cs);
	}
	void Unlock()
	{
		LeaveCriticalSection(&cs);
	}
private:
	CRITICAL_SECTION cs;

};

