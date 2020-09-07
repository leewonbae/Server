#include "cIOCP.h"
 

DWORD WINAPI switchthread(LPVOID arg)
{
	cIOCP* ciocp = (cIOCP*)arg;;
	ciocp->WorkerThread();
	return 0;
}
cIOCP::cIOCP()
{
	InitializeCriticalSection(&cs);

}
cIOCP::~cIOCP()
{
	DeleteCriticalSection(&cs);
	closesocket(mListenSock);
	WSACleanup();
}

// 서버 초기화
void cIOCP::InitServer()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cout << "wsa error" << endl;
	}

	mListenSock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

	SOCKADDR_IN serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(PORT);
	serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	
	
	MakeCP();
	
	bind(mListenSock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));

	listen(mListenSock, SOMAXCONN);
	
}
//init 함수에서 호출 , cp 생성
void cIOCP::MakeCP()
{
	mHcp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
}

// thread cpu*2 만큼 생성
void cIOCP::MakeThread()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	for (int i = 0;i < (int)si.dwNumberOfProcessors * 2;i++)
	{
		CreateThread(NULL, 0, switchthread, this, 0, NULL);
	}
}

// accpet 후 비동기 recv 시작
void cIOCP::AcceptClient()
{
	SOCKET clientsock;
	SOCKADDR_IN clientaddr;
	
	while (1)
	{
		
		int addlen = sizeof(clientaddr);
		clientsock = accept(mListenSock, (SOCKADDR*)&clientaddr, &addlen);
		SOCKETINFO* NewUser = new SOCKETINFO;

		cout << "클라이언트 접속" << endl;
		mHcp = CreateIoCompletionPort((HANDLE)clientsock, mHcp, clientsock, 0);
	
		NewUser->mSock = clientsock;
		
		OnRecv(NewUser); 

	}
}

// recv 
void cIOCP::OnRecv(SOCKETINFO* _ptr)
{
	int retval;
	DWORD recvbytes, flags = 0;
	ZeroMemory(&_ptr->mOver, sizeof(_ptr->mOver));
	ZeroMemory(&_ptr->mDatabuf, sizeof(_ptr->mDatabuf));
	
	_ptr->mWbuf.buf = _ptr->mDatabuf;
	_ptr->mWbuf.len = BUFFER_SIZE;
	_ptr->mWorkFleg = FLEG_RECV;
	
	retval = WSARecv(_ptr->mSock, &_ptr->mWbuf, 1, &recvbytes, &flags, &_ptr->mOver, NULL);
	
	if (retval == SOCKET_ERROR)
	{
		if (GetLastError() != ERROR_IO_PENDING)
		{
			cout << " error io pending" << endl;
		}
	}
}
// send
void cIOCP::OnSend(SOCKETINFO* _ptr )
{
	
	int retval;
	DWORD sendbytes;
	
	_ptr->mWbuf.buf = _ptr->mDatabuf;
	_ptr->mWbuf.len = BUFFER_SIZE;
	_ptr->mWorkFleg = FLEG_SEND;

	retval = WSASend(_ptr->mSock, &_ptr->mWbuf, 1, &sendbytes,0, &_ptr->mOver, NULL);

	if (retval == SOCKET_ERROR)
	{
		if (GetLastError() != ERROR_IO_PENDING)
		{
			cout << " error io pending" << endl;
		}
	}
}
// GQCP 처리 //다시 RECV 준비
void cIOCP::WorkerThread()
{
	cout << " thread" << endl;
	int retval;
	DWORD trasferred;
	SOCKET clientsock;
	SOCKETINFO* userinfo;
	
	while (1)
	{
		
		retval = GetQueuedCompletionStatus(mHcp, &trasferred, (LPDWORD)&clientsock, (LPOVERLAPPED*)&userinfo,INFINITE);
		 
		if (retval == 0 || trasferred == 0)
		{
			cout << "클라이언트 종료" << endl;
			continue;
		}	
		 
		switch (userinfo->mWorkFleg)
		{
	 
		case FLEG_SEND:
			cout << "send ok" << endl;	 
			OnRecv(userinfo);
			break;

		case FLEG_RECV:
			cout << "recv" << endl;

			Parsing(userinfo);
			 
			break;
		default :
			cout << "오류 " << endl;
			break;
		}
			
		 
		
 
	}
}
