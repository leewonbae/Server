#pragma once
#include "Resource.h"
class cCriticalSection
{
public:
	cCriticalSection();
	~cCriticalSection();

	void Lock();
	void Unlock();
private:

	CRITICAL_SECTION cs;
};

