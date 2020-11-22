#include "cWorkerThread.h"
DWORD WINAPI swichthread(LPVOID arg)
{
	cWorkerThread* thread_ptr = (cWorkerThread*)arg;
	thread_ptr->WorkerThread();
	return 0;
}
cWorkerThread::cWorkerThread()
{

}
cWorkerThread::~cWorkerThread()
{

}
void cWorkerThread::MakeThread()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	for (int i = 0;i < (int)si.dwNumberOfProcessors * 2 + 1;i++)
	{
		CreateThread(NULL, 0, swichthread, this, 0, NULL);
	}

	cout << "make thread ok" << endl;
}

void cWorkerThread::RecvDataParsing(OVERDATA* _overdata, cUser* _user)
{
	bool check = _user->getAuth();
	PACKET_HEAD* phead = (PACKET_HEAD*)_overdata->mWsabuf.buf;


	if (check == true && phead->mCmd < PTC_PERSONAL)
	{
		if (phead->mCmd > PTC_ROOM && phead->mCmd <= PTC_ROOMLIST_REQ)
		{
			mRoomManager.RoomManagerParsing(phead, _user);
		}

	}
	if (check == false)
	{
		mUserManager.UserManagerParsing(phead, _user);
		 
	}

	
	_user->OnRecv();

}
void cWorkerThread::SendDataParsing(OVERDATA* _overdata, cUser* _user)
{
	PACKET_HEAD* phead = (PACKET_HEAD*)_overdata->mWsabuf.buf;
	mRoomManager.SendMsgCheck(phead, _user);
}
void cWorkerThread::WorkerThread()
{
	cSession* ptr_session;
	OVERDATA* ptr_over;
	DWORD retval, transbytes;
	while (1)
	{
		HANDLE hcp = getHANDLE();

		retval = GetQueuedCompletionStatus(hcp, &transbytes, (PULONG_PTR)&ptr_session, (LPOVERLAPPED*)&ptr_over, INFINITE);
		if (retval == 0 || transbytes == 0)
		{
			if (ptr_session->getAuth() == true)
			{
				mUserManager.OutUser((cUser*)ptr_session);
			}

			OutSession(ptr_session);
			cout << "클라이언트 종료" << endl;
			continue;
		}

		switch (ptr_over->mWorkFlag)
		{
		case FLAG_RECV:
			ptr_session->Upsize(transbytes);
			RecvDataParsing(ptr_over, (cUser*)ptr_session); 
			break;


		case FLAG_SEND:
			if (ptr_session->getSize() != 0)
			{
				ptr_session->Downsize(transbytes);
				 
			}
			SendDataParsing(ptr_over, (cUser*)ptr_session);
		 
			break;
		}



	}
}