#include "cThread.h"
DWORD WINAPI SwitchThread(LPVOID arg)
{
	cThread* thread = (cThread*)arg;
	thread->WorkerThread();
	return 0;
}
cThread::cThread()
{


}
cThread::~cThread()
{

}

void cThread::MakeThread()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	for (int i = 0;i < (int)si.dwNumberOfProcessors *2;i++)
	{
		CreateThread(NULL, 0, SwitchThread, this, 0, NULL);
 
	}
	cLog::Print_log("make thread ok");
}

void cThread::WorkerThread()
{

	cSession* ptr;
	OVERDATA* over;
	DWORD transbytes;
	
	while (1)
	{
	 
		HANDLE hcp = getHandle();
		int retval = GetQueuedCompletionStatus(hcp, &transbytes, (LPDWORD)&ptr, (LPOVERLAPPED*)&over, INFINITE);
		
		if (retval == 0 || transbytes == 0)
		{
			cLog::Print_log("클라이언트 종료");
			int index = ptr->getkey();
			ClientOut(index);
			continue;
		}

		PACKET_HEAD* phead = (PACKET_HEAD*)over->mDataBuf;
		 

	 
		switch (over->mMODE)
		{
		case MODE_RECV:
			DataParsing(phead, ptr);
			ptr->OnRecv();
			break;
		case MODE_SEND:

			break;
		default:
			break;
		}
	}


	
}