#include "cIOCP.h"
DWORD WINAPI SwitchThread(LPVOID arg)
{
	cIOCP* iocp = (cIOCP*)arg;
	iocp->WorkerThread();
	return 0;
}


cIOCP::cIOCP()
{
	InitializeCriticalSection(&cs);
}


cIOCP::~cIOCP()
{
	DeleteCriticalSection(&cs);
	closesocket(mListen_sock);
	WSACleanup();
}



void cIOCP::Init()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cout << "fail" << endl;
	}
	
	mListen_sock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(PORT);
	serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	bind(mListen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));

	listen(mListen_sock, SOMAXCONN);
	MakeCompletionport();
}



void cIOCP::MakeCompletionport()
{
	mHCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
}



void cIOCP::MakeThread()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	for (int i = 0;i < (int)si.dwNumberOfProcessors * 2; i++)
	{
		CreateThread(NULL, 0, SwitchThread, this, 0, NULL);
		 
	}
}



void cIOCP::AcceptClient()
{
	int addlen = sizeof(mClient_addr);
	while (1)
	{
		mClient_sock = accept(mListen_sock, (SOCKADDR*)&mClient_addr, &addlen);
		cout << "클라이언트 접속" << endl;
		cSession* newclient = new cSession;
		newclient->SetAddr(mClient_addr);
		newclient->SetSOCK(mClient_sock);
		CreateIoCompletionPort((HANDLE)mClient_sock, mHCP,(ULONG_PTR)newclient,0);
		newclient->OnRecv();
	}
}



void cIOCP::WorkerThread()
{
	DWORD transbytes;
	cSession* session;
	SOCKET client_sock;
	OVERDATA* over;
	int sessionkey;
	int retval;
	 
	PACKET_HEAD phead;
	while (1)
	{
		retval = GetQueuedCompletionStatus(mHCP, &transbytes, (LPDWORD)&session,  (LPOVERLAPPED*)&over, INFINITE);
	 
		if (retval == 0 || transbytes == 0)
		{
			cout << "클라이언트 종료" << endl;
			delete session;
			continue;
		}
	
		sessionkey = session->getFleg();
		
		memset(&phead, 0, sizeof(PACKET_HEAD));
		memcpy(&phead, over->mDatabuf, sizeof(PACKET_HEAD));
		switch (sessionkey)
		{
		case FLEG_ACCEPT:
			continue;
			break;
		case FLEG_RECV:
			EnterCriticalSection(&cs);
			Parsing(phead.mCmd,  over);
			LeaveCriticalSection(&cs);
			break;
		case FLEG_SEND:
			session->OnRecv();
			break;
		}

	}
}
 
 