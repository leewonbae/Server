#include "cIOCP.h"
DWORD WINAPI swtichthread(LPVOID arg)
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
	WSACleanup();
}
void cIOCP::Init_Server()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cout << "error" << endl;
	}
	mListenSock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN mServeraddr;
	mServeraddr.sin_family = AF_INET;
	mServeraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	mServeraddr.sin_port = htons(PORT);

	bind(mListenSock, (SOCKADDR*)&mServeraddr, sizeof(mServeraddr));
	
	listen(mListenSock, SOMAXCONN);
	cout << "server init ok" << endl;
}
void cIOCP::MakeCP()
{
	mHCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	cout << "make cp ok" << endl;
}
void cIOCP::MakeThread()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	for (int i = 0;i < (int)si.dwNumberOfProcessors;i++)
	{
		CreateThread(NULL, 0, swtichthread, this, 0, NULL);
	}
	cout << "make thread ok" << endl;
}
void cIOCP::Acceptor()
{
	SOCKET client_sock;
	SOCKADDR_IN client_addr;
	int addlen;
	cDatabase maindatabase;
	while (1)
	{
		addlen = sizeof(client_addr);
		client_sock = accept(mListenSock, (SOCKADDR*)&client_addr, &addlen);
		cout << "클라이언트 접속" << endl;
		cUsers* newclient = new cUsers;
		newclient->setSock(client_sock);
		newclient->setAddr(client_addr);
		newclient->setDatabase(&maindatabase);
		CreateIoCompletionPort((HANDLE)client_sock, mHCP, (ULONG_PTR)newclient, 0);
		newclient->OnRecv();
	}
}
void cIOCP::WorkerThread()
{
	DWORD transbytes;
	int retval;
	int check_fleg;
	OVERDATA* overUserData;
	cUsers* user;
	while (1)
	{
		retval = GetQueuedCompletionStatus(mHCP, &transbytes, (LPDWORD)&user, (LPOVERLAPPED*)&overUserData, INFINITE);
		if (retval == 0 || transbytes == 0)
		{
			cout << "클라이언트 종료" << endl;
			delete user;
			continue;
		}
		
		check_fleg=user->getWorkfleg();
		switch (check_fleg)
		{
		case FLEG_RECV:
			user->Parsing(overUserData);
			
			break;
		case FLEG_SEND:
			user->OnRecv();
			break;
		case FLEG_ACCEPT:
			continue;
			break;
		default:
			cout << "플레그 확인 불가능" << endl;
			break;
		}
	}
}