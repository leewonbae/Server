#include "cIOCP.h"
DWORD WINAPI Switchthread(LPVOID arg)
{
	cIOCP* iocp = (cIOCP*)arg;
	iocp->WorkerThread();
	return 0;
}
cIOCP::cIOCP()
{

}
cIOCP::~cIOCP()
{
	closesocket(mListensock);
	WSACleanup();
}
void cIOCP::InitServer()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	mListensock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(PORT);
	serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	bind(mListensock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	listen(mListensock, SOMAXCONN);

	cLOG::Print_log(__FUNCTION__,0 ,"INIT SERVER OK");

}
void cIOCP::MakeThread()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	for (int i = 0;i < (int)si.dwNumberOfProcessors;i++)
	{
		CreateThread(NULL, 0, Switchthread, this, 0, NULL);
	}
	cLOG::Print_log(__FUNCTION__,0 ,"MAKE THREAD OK");
}
void cIOCP::MakeHcp()
{
	mHcp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	cLOG::Print_log(__FUNCTION__, 0,"MAKE HANDLE HCP OK");
}

void cIOCP::Acceptor(cUserDB* _database)
{
	SOCKET clientsock;
	SOCKADDR_IN clientaddr;
	int addlen;

	while (1)
	{
		addlen = sizeof(clientaddr);
		clientsock = accept(mListensock, (SOCKADDR*)&clientaddr, &addlen);
		cLOG::Print_log(__FUNCTION__, 0,"CLIENT ACCEPT OK");
		cUser* newsession = new cUser;
		newsession->SetSOCK(clientsock);
		newsession->SetDB(_database);
		newsession->SetUM(&mUsermanager);
		CreateIoCompletionPort((HANDLE)clientsock, mHcp, (ULONG_PTR)newsession, 0);

		if (mSessionManager.InputSession(newsession))
		{
			newsession->Onrecv();
		}
		else
		{
			cLOG::Print_log(__FUNCTION__,0 ,"SESSIONMANAGER FAIL");
		}
	}
}
void cIOCP::WorkerThread()
{
	DWORD transbytes;
	int retval;
	int hashkey;
	OVERDATA* over;
	cSession* sessionptr;
	while (1)
	{
		retval = GetQueuedCompletionStatus(mHcp, &transbytes, (LPDWORD)&sessionptr, (LPOVERLAPPED*)&over, INFINITE);
		hashkey = sessionptr->getKey();
		
		if (retval == 0 || transbytes == 0)
		{
			cLOG::Print_log(__FUNCTION__, hashkey, "CLIENT OUT OK");
			mSessionManager.DeleteSession(hashkey);
			continue;
		}
		
		
		switch (over->mWorkFleg)
		{
		case WORK_FLEG_RECV:
			mSessionManager.ParsingSession(hashkey, over);
			break;
		case WORK_FLEG_SEND:
			mSessionManager.Setrecv(hashkey);
			break;
		default:
			cLOG::Print_log(__FUNCTION__,0, "packet error");
			break;
		}
	
	}


}