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
void cIOCP::Play()
{
	InitServer();
	MakeHCP();
	MakeThread();
	Acceptor();
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
	cLog::Print_log(__FUNCTION__,0,"init server ok");
	 
}
void cIOCP::MakeHCP()
{
	mHCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	cLog::Print_log(__FUNCTION__,0,"MAKE HCP OK");
	 
}
void cIOCP::MakeThread()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	for (int i = 0;i < (int)si.dwNumberOfProcessors;i++)
	{
		CreateThread(NULL, 0, Switchthread, this, 0, NULL);
	}
	cLog::Print_log(__FUNCTION__,0,"MAKE THREAD OK");

}
void cIOCP::Acceptor()
{
	SOCKET clientsock;
	SOCKADDR_IN clientaddr;
	int addlen;
	cSessionManager sm;
	cUserDB udb;
	cLoanDB ldb;
	
	while (1)
	{
		addlen = sizeof(clientaddr);
		clientsock = accept(mListensock, (SOCKADDR*)&clientaddr, &addlen);
		// 만들어 주는것도 그냥 sessionmanager에서 할걸 그랫나
		// newsession 이 맞는 건가 , newuser가 맞는건가
		// 아직 로그인 체크를 안햇으니 newsession이라고 표기하자


		cUser* newsession = new cUser;
		newsession->SetUserDb(&udb);
		newsession->SetLoanDb(&ldb);
		// 근데 그렇게 하면 mhcp를 가져와서 세션매니저에서 등록해야 하네
		// 그래서 어차피 mhcp를 복사를 해와야 하니 그냥 여기서 복사해서 
		// 객체의 주소를 보내버리자
		CreateIoCompletionPort((HANDLE)clientsock, mHCP, (ULONG_PTR)newsession, 0);
		sm.InputNewSession(newsession, clientsock, clientaddr);

	}
}
void cIOCP::WorkerThread()
{
	DWORD transbytes;
	int retval;
	int User_key;
	OVERLAPPED_DATA* over;
	cSession* sessionPointer;
	cUserManager um;
	while (1)
	{
		retval = GetQueuedCompletionStatus(mHCP, &transbytes, (LPDWORD)&sessionPointer, (LPOVERLAPPED*)&over, INFINITE);

		if (retval == 0 || transbytes == 0)
		{
			cLog::Print_log(__FUNCTION__,0,"클라이언트 종료");
			continue;
		}

		switch (over->mFlegMode)
		{
		case FLEG_RECV:
			sessionPointer->Parsing(over);
			break;

		case FLEG_SEND:
			PACKET_HEAD phead;
			memcpy(&phead, over->mDatabuf, sizeof(PACKET_HEAD));
			if (phead.mHeadCmd == MSG_LOGIN_TRUE)
			{
				
				um.InputUser((cUser*)over);
			}
			sessionPointer->Onrecv();
			break;

		}
	}

}
