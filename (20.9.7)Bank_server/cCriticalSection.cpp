#include "cCriticalSection.h"
cCriticalSection::cCriticalSection()
{
	InitializeCriticalSection(&cs);
}
cCriticalSection::~cCriticalSection()
{
	DeleteCriticalSection(&cs);
}
void cCriticalSection::Lock()
{
	EnterCriticalSection(&cs);
}
void cCriticalSection::Unlock()
{
	LeaveCriticalSection(&cs);
}