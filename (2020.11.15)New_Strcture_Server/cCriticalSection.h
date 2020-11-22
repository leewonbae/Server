#pragma once
#include "Resource.h"
class cCriticalSection
{
public:
	cCriticalSection();
	~cCriticalSection();
	
	void LOCK();
	void UN_LOCK();
 

private:
	CRITICAL_SECTION mCS;

};

