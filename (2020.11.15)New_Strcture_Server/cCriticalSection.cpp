#include "cCriticalSection.h"
cCriticalSection::cCriticalSection()
{
	InitializeCriticalSection(&mCS);
}
cCriticalSection::~cCriticalSection()
{
	DeleteCriticalSection(&mCS);
}

void cCriticalSection::LOCK()
{
	EnterCriticalSection(&mCS);
}
void cCriticalSection::UN_LOCK()
{
	LeaveCriticalSection(&mCS);
}