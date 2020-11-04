#include "cThread.h"
DWORD WINAPI SwitchThread(LPVOID arg)
{
	cThread* sthread = (cThread*)arg;
	sthread->WorkerThread();
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
	for (int i = 0;i < (int)si.dwNumberOfProcessors * 2;i++)
	{
		CreateThread(NULL, 0, SwitchThread, this, 0, NULL);
	}
}
void cThread::WorkerThread()
{
	int retval;
	DWORD transbytes;

	cSession* ptr_session;
	OVERDATA* ptr_over;
	
	while (1)
	{
		HANDLE IOCPhanle = getHandle();

		retval = GetQueuedCompletionStatus(IOCPhanle, &transbytes, (PULONG_PTR)&ptr_session, (LPOVERLAPPED*)&ptr_over, INFINITE);
		if (retval == 0 || transbytes == 0)
		{
			cout << "클라이언트 종료" << endl;
			ClientOut(ptr_session);
			continue;
		}
		PACKET_HEAD* phead = (PACKET_HEAD*)ptr_over->mDatabuf;
		switch (ptr_over->mWorkFleg)
		{
		case WORKFLEG_RECV:
			cout << "=======================================" << endl;
			Manager_Parsing(ptr_session, phead);
			
			break;
		case WORKFLEG_SEND:
			ptr_session->OnRecv();
			cout << "=======================================" << endl;
			break; 
		}
		
	}

}
 
