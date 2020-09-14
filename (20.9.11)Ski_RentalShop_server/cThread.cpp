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
void cThread::SetServer(cServer* _serverptr)
{
	mServerPtr = _serverptr;
}
void cThread::MakeThread()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	for (int i = 0;i < (int)si.dwNumberOfProcessors;i++)
	{
		CreateThread(NULL, 0, SwitchThread, this, 0, NULL);
	}
}

void cThread::WorkerThread()
{
	cout << "½º·¹µå" << endl;
	int retval;
	DWORD transbytes;
	OVERDATA* over_ptr;
	cSession* session_ptr;

 
	while (1)
	{
		retval = GetQueuedCompletionStatus(mServerPtr->getHandle(), &transbytes, (LPDWORD)&session_ptr, (LPOVERLAPPED*)&over_ptr, INFINITE);
			
		if (retval == 0 || transbytes == 0)
		{
			mServerPtr->ClientOut(session_ptr);
			continue;
		}
	


		PACKET_HEAD* packet = (PACKET_HEAD*)over_ptr->mDatabuf;
		


		switch (over_ptr->mWorkFleg)
		{
		case WORK_FLEG_RECV:
			cout << "-------------PACKET RECV START------------" << endl;
			mServerPtr->PacketParsing(session_ptr, packet);

			break;
		case WORK_FLEG_SEND:

			if (packet->mPacket_MSG == MSG_LOGIN_OK)
			{
				mServerPtr->SendUserManager((cUser*)session_ptr);
			}

			session_ptr->Onrecv();
		

			break;
		}
	
	}




}