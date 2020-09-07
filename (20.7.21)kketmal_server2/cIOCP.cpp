#include "cIOCP.h"

DWORD WINAPI ThreadWorker(LPVOID arg)
{
	cIOCP* SWTICH_IOCP = (cIOCP*)arg;
	SWTICH_IOCP->WOKERTHREAD();
	return 0;
}
cIOCP::cIOCP()
{
	cout << " 생성자" << endl;
	InitializeCriticalSection(&cs);
	
	 
}
cIOCP::~cIOCP()
{
	cout << "ciocp exif" << endl;
	DeleteCriticalSection(&cs);
	closesocket(m_ListenSock);
	WSACleanup();
}
void cIOCP::InitServer()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cout << "wsastartup error" << endl;
 
	}
	m_ListenSock = socket(AF_INET, SOCK_STREAM, 0);
	m_hcp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	SOCKADDR_IN serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(PORT);
	serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	bind(m_ListenSock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	
	listen(m_ListenSock, SOMAXCONN);
	
	
	cout << "초기화 ok" << endl;
	 
}
void cIOCP::MakeThread()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	HANDLE hthread;
	for (int i = 0;i < (int)si.dwNumberOfProcessors * 2;i++)
	{
		hthread = CreateThread(NULL, 0, ThreadWorker, this, 0, NULL);
	
	}

}
void cIOCP::ServerAccept()
{
	SOCKET client_sock;
	SOCKADDR_IN client_addr;

	while (1)
	{
		int addlen = sizeof(client_addr);
		client_sock = accept(m_ListenSock, (SOCKADDR*)&client_addr, &addlen);
		cout << "클라이언트 접속" << endl;
		cout << "port = " << ntohs(client_addr.sin_port) << endl;
		cout << "ip = " << inet_ntoa(client_addr.sin_addr) << endl;
		CreateIoCompletionPort((HANDLE)client_sock, m_hcp, client_sock, 0);
		
		
		SOCKETINFO* sInfoClient = new SOCKETINFO;
		ZeroMemory(&sInfoClient->_overlapped, sizeof(sInfoClient->_overlapped));
		sInfoClient->_sock = client_sock;
		sInfoClient->_wsabuf.buf = (char*)&sInfoClient->_d_info;
		sInfoClient->_wsabuf.len = sizeof(DATA_INFO);
		sInfoClient->_workerflag = FLAG_RECV;
		
		int retval;
		
		DWORD recvbytes, flags = 0;
		retval = WSARecv(sInfoClient->_sock, &sInfoClient->_wsabuf, 1, &recvbytes, &flags, &sInfoClient->_overlapped, NULL);
		if (retval == SOCKET_ERROR)
		{
			if (WSAGetLastError() != ERROR_IO_PENDING)
			{
				cout << "io pending" << endl;
			}
			continue;
		}


	}
}

void cIOCP::MSG_SEND(SOCKETINFO* _sInfo, char* _data)
{
	int retval;
	DWORD sendbytes;
	cout << "send" << endl;
	ZeroMemory(&_sInfo->_overlapped, sizeof(_sInfo->_overlapped));
	if (_sInfo->_d_info._msg_number == act_room)
	{
		SEND_ROOMINFO* se;
		se = (SEND_ROOMINFO*)_data;
		cout << se->roomcount << endl;
		memcpy(_sInfo->_d_info._data, _data,sizeof(SEND_ROOMINFO));
		se = (SEND_ROOMINFO*)&_sInfo->_d_info;
		cout << se->roomcount << endl;
	}
	if (_sInfo->_d_info._msg_number == act_ready)
	{
		 
		memcpy(_sInfo->_d_info._data, _data, sizeof(START_ROOM_SEND_DATA));

	}
	if (_sInfo->_d_info._msg_number == act_turncheck)
	{

		memcpy(_sInfo->_d_info._data, _data, sizeof(START_ROOM_SEND_DATA));

	}
	else
	{
		strcpy(_sInfo->_d_info._data, _data);
	}
	
	
	_sInfo->_workerflag = FLAG_SEND;
	_sInfo->_wsabuf.buf = (char*)&_sInfo->_d_info;
	_sInfo->_wsabuf.len = sizeof(DATA_INFO);
	retval = WSASend(_sInfo->_sock, &_sInfo->_wsabuf, 1, &sendbytes, 0, &_sInfo->_overlapped, NULL);
	
	if (retval == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			cout << "thread" << endl;
		}
		
	}
}

void cIOCP::WOKERTHREAD()
{
	cout << "thread" << endl;
	
	int retval;
	int addlen;
	SOCKETINFO* ptr;
	SOCKET client_sock;
	SOCKADDR_IN client_addr;
	DWORD transferred;
	 
	while (1)
	{
		 
		
		
		
		retval = GetQueuedCompletionStatus(m_hcp, &transferred, (LPDWORD)&client_sock, (LPOVERLAPPED*)&ptr, INFINITE);

		addlen = sizeof(client_addr);
		
		DWORD dThreadid = GetCurrentThreadId();
		 
		cout << dThreadid << "asdf" << endl;
			 


		if (retval == 0 || transferred == 0)
		{
			cout << "클라이언트 종료" << endl;
			continue;
		}
		 
		if (ptr->_workerflag == FLAG_RECV)
		{
			cout << "recv ok" << endl;
			getpeername(client_sock, (SOCKADDR*)&client_addr, &addlen);
			cout << "port = " << ntohs(client_addr.sin_port) << endl;
			cout << "ip = " << inet_ntoa(client_addr.sin_addr) << endl;
			cout<<"recv 된 메세지 넘버 = =  " <<ptr->_d_info._msg_number << endl;
			int temp= ptr->_d_info._msg_number;
			 
			Switch_msg(temp, ptr);
			 
			
		}
		 
		 
		 
		else {
			ZeroMemory(&ptr->_overlapped, sizeof(ptr->_overlapped));

			ptr->_wsabuf.buf = (char*)&ptr->_d_info;
			ptr->_wsabuf.len = sizeof(DATA_INFO);
			ptr->_workerflag = FLAG_RECV;

			DWORD recvbytes, flags = 0;
			retval = WSARecv(ptr->_sock, &ptr->_wsabuf, 1, &recvbytes, &flags, &ptr->_overlapped, NULL);
			if (retval == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSA_IO_PENDING)
				{
					cout << "io pending" << endl;
				}
			}

		} 
	}

 
}