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
	cout << "�Ӱ� ���� ����" << endl;
}
void cCriticalSection::Unlock()
{
	cout << "�Ӱ� ���� ����" << endl;
	LeaveCriticalSection(&cs);
}