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

// ���� �ʱ�ȭ
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
//init �Լ����� ȣ�� , cp ����
void cIOCP::MakeCP()
{
	mHcp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
}

// thread cpu*2 ��ŭ ����
void cIOCP::MakeThread()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	for (int i = 0;i < (int)si.dwNumberOfProcessors * 2;i++)
	{
		CreateThread(NULL, 0, switchthread, this, 0, NULL);
	}
}

// accpet �� �񵿱� recv ����
void cIOCP::AcceptClient()
{
	SOCKET clientsock;
	SOCKADDR_IN clientaddr;
	
	while (1)
	{
		
		int addlen = sizeof(clientaddr);
		clientsock = accept(mListenSock, (SOCKADDR*)&clientaddr, &addlen);
		SOCKETINFO* NewUser = new SOCKETINFO;

		cout << "Ŭ���̾�Ʈ ����" << endl;
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
// GQCP ó�� //�ٽ� RECV �غ�
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
			cout << "Ŭ���̾�Ʈ ����" << endl;
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
			cout << "���� " << endl;
			break;
		}
			
		 
		
 
	}
}
