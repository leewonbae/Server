#include "cIOCP.h"
DWORD WINAPI SwitchThread(LPVOID arg)
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
	closesocket(mListenSock);
	WSACleanup();
}
void cIOCP::InitServer()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	mListenSock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(PORT);
	serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	bind(mListenSock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	
	listen(mListenSock, SOMAXCONN);

	cout << "server ok" << endl;
}
void cIOCP::MakeThread()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	for (int i = 0;i < (int)si.dwNumberOfProcessors*2;i++)
	{
		CreateThread(NULL, 0, SwitchThread, this, 0, NULL);
	}
	cout << "make thread ok" << endl;
}
void cIOCP::MakeHCP()
{
	mHcp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	cout << "make hcp ok" << endl;
}
void cIOCP::Acceptor()
{
	cout << "play accept" << endl;
	SOCKET client_sock;
	SOCKADDR_IN client_addr;
	int addlen;
	cDatabase database;
	while (1)
	{
		addlen = sizeof(client_addr);
		client_sock=accept(mListenSock, (sockaddr*)&client_addr, &addlen);
		cout << "클라이언트 접속" << endl;
		cUser* newuser = new cUser;
		newuser->setSock(client_sock);
		newuser->setSockAddr(client_addr);
		newuser->setDB(&database);
		CreateIoCompletionPort((HANDLE)client_sock, mHcp, (ULONG_PTR)newuser, 0);
		newuser->OnRecv();
	}
}

void cIOCP::WorkerThread()
{
	int retval;
	DWORD transbytes;
	int fleg;
	cUser* pUser;
	OVERDATA* mIoOver;
	while (1)
	{
		retval = GetQueuedCompletionStatus(mHcp, &transbytes, (LPDWORD)&pUser, (LPOVERLAPPED*)&mIoOver, INFINITE);
		if (retval == 0 || transbytes == 0)
		{
			cout << "클라이언트 종료" << endl;
			continue;
		}
	
		fleg= pUser->getFleg();
		cout << "fleg" << fleg << endl;
		switch (fleg)
		{
		case FLEG_RECV:
			cout << "recv" << endl;
			pUser->Parsing(mIoOver);
			break;
		case FLEG_SEND:
			cout << "send" << endl;
			pUser->OnRecv();
			break;
		default :
			cout << " 데이터 확인 불가능" << endl;
			break;
		}

	}
}