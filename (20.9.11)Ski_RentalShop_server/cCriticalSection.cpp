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
	cout << "임계 구역 시작" << endl;
}
void cCriticalSection::Unlock()
{
	cout << "임계 구역 해제" << endl;
	LeaveCriticalSection(&cs);
}