#include "cThread.h"
DWORD WINAPI Switchthread(LPVOID arg)
{
	cThread* thread = (cThread*)arg;
	thread->Workerthread();
	return 0;
}
cThread::cThread()
{

}
cThread::~cThread()
{

}
void cThread::Makethread()
{
	cLog::Server_print(__FUNCTION__, " ");
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	for (int i = 0;i < (int)si.dwNumberOfProcessors*2;i++)
	{
		CreateThread(NULL, 0, Switchthread, this, 0, NULL);
	}
}
void cThread::Workerthread()
{
	
	DWORD transbytes;
	HANDLE Hcp = getHcp();
	cSession* sPtr;
	OVERDATA* over;
	int key;
	int retval;
	PACKET_HEAD* recvpacket;

	while (1)
	{
		retval = GetQueuedCompletionStatus(Hcp, &transbytes, (LPDWORD)&sPtr, (LPOVERLAPPED*)&over, INFINITE);
	
		key = sPtr->getKey();
		
		recvpacket = (PACKET_HEAD*)over->mDatabuf;
		if (retval == 0 || transbytes == 0)
		{
			OutSession(sPtr);
			
			continue;
		}
		switch (over->mWorkFleg)
		{
		case FLEG_RECV:
			cLog::Server_print(__FUNCTION__, "DATA RECV OK");
			cLog::Session_print(key);
			DataAnalysis(recvpacket, sPtr);

			cLog::Server_print(__FUNCTION__, "recv 전환 타이밍 체크");
			sPtr->Onrecv();
			break;
		case  FLEG_SEND:

			cLog::Server_print(__FUNCTION__, "DATA SEND OK");
			cLog::Session_print(key);
			break;
		}
		
	}

}