#include "cIOCP.h"
DWORD WINAPI switchthread(LPVOID arg)
{
	cIOCP* iocp = (cIOCP*)arg;
	iocp->Workerthrad();
	return 0;
}
cIOCP::cIOCP()
{
	mUsercount = 0;

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

	cout << "init server ok" << endl;
}
void cIOCP::MakeHcp()
{
	mHcp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	cout << "hck make ok" << endl;
}
void cIOCP::MakeThread()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	for (int i = 0;i < (int)si.dwNumberOfProcessors;i++)
	{
		CreateThread(NULL, 0, switchthread, this, 0, NULL);
	}
	cout << "thread make ok" << endl;
}
void cIOCP::Acceptor()
{
	SOCKET clientsock;
	SOCKADDR_IN clientaddr;
	int addlen;
	while (1)
	{
		addlen = sizeof(clientaddr);
		clientsock = accept(mListensock, (SOCKADDR*)&clientaddr, &addlen);
		cout << "클라이언트 접속" << endl;
		cSession* newuser = new cSession;
		
		newuser->SetSOCK(clientsock);
		newuser->SetUserKey(mUsercount);
		mUserArray[mUsercount] = newuser;
		mUsercount++;
		mUserclass.SetUserarray(mUserArray);
		mUserclass.SetUsercount(&mUsercount);
		mUserclass.SetEvent(&mEventhandle);
		CreateIoCompletionPort((HANDLE)clientsock, mHcp, (ULONG_PTR)newuser, 0);
		newuser->Onrecv();
	}
	
}
void cIOCP::Workerthrad()
{
	int retval;
	DWORD transbytes;
	cSession* user;
	OVERDATA* over;
	while (1)
	{
		retval = GetQueuedCompletionStatus(mHcp, &transbytes, (LPDWORD)&user, (LPOVERLAPPED*)&over, INFINITE);

		if (retval == 0 || transbytes == 0)
		{
			cout << "클라이언트 종료" << endl;
			continue;
		}
		int userfleg = user->getfleg();
		

		switch (userfleg)
		{
		case FLEG_RECV:
			mUserclass.Parsing(over);
			break;
		case FLEG_SEND:
			user->Onrecv();
			break;
		 
		default:
			cout << "fleg 확인 불가능" << endl;
			break;
		}
	}
}