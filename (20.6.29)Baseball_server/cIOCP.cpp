#include "cIOCP.h"
// 생성자

DWORD WINAPI SwitchThread(LPVOID arg)
{
	cIOCP* _cIOCP = (cIOCP*)arg;
	_cIOCP->Workerthread();
	return 0;
}

cIOCP::cIOCP()
{

}


cIOCP::~cIOCP()
{
	closesocket(listen_sock);
	WSACleanup();
}
bool cIOCP::Init_server()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return false;
	}

	listen_sock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, NULL, WSA_FLAG_OVERLAPPED);
		//socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(PORT);
	serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	hcp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);


	if (bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr)) == SOCKET_ERROR)
	{
		return false;
	}
	if (listen(listen_sock, SOMAXCONN) == SOCKET_ERROR)
	{
		return false;
	}
	return true;
}


bool cIOCP::MakeThread()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	for (int i = 0;i < (int)si.dwNumberOfProcessors*2;i++)
	{
		CreateThread(NULL, 0, SwitchThread, this, 0, NULL);
	}

	return true;
}



void cIOCP::Workerthread()
{
	cout << "thread" << endl;
	int retval;
	DWORD transbytes;
	SOCKET client_sock;
	SOCKETINFO* ptr;
	PACKET_HEAD p_head;
	while (1)
	{
		retval =GetQueuedCompletionStatus(hcp, &transbytes, (LPDWORD)&client_sock, (LPOVERLAPPED*)&ptr, INFINITE);
		if (retval == 0 || transbytes == 0)
		{
			cout << "클라이언트 종료" << endl;
			continue;
		}

		if (ptr->_workflag == FLAG_RECV)
		{
			cout << "데이터 받앗음" << endl;
			Parsing(ptr);
		}
		else if (ptr->_workflag == FLAG_SEND)
		{
			cout << "데이터 보냇음" << endl;
			
		}
		

		ZeroMemory(&ptr->_overlapped, sizeof(ptr->_overlapped));
		ZeroMemory(&ptr->_databuf, sizeof(ptr->_databuf));
		ptr->_workflag = FLAG_RECV;
		ptr->_wsabuf.buf = ptr->_databuf;
		ptr->_wsabuf.len = BUFFER_SIZE;


		DWORD recvbytes, flags = 0;
		retval = WSARecv(ptr->_sock, &ptr->_wsabuf, 1, &recvbytes, &flags, &ptr->_overlapped, NULL);
		if (retval == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSA_IO_PENDING)
			{
				cout << "thread _io pending" << endl;
			}
			continue;
		}
		
	}
}

void cIOCP::IOCP_controller()
{
	
	
	SOCKET client_sock;
	SOCKADDR_IN client_addr;
	while (1)
	{
		int addlen = sizeof(client_addr);
		client_sock = accept(listen_sock, (SOCKADDR*)&client_addr, &addlen);

		hcp = CreateIoCompletionPort((HANDLE)client_sock, hcp, client_sock, 0);
		cout << "클라이언트 접속" << endl;
		cout << "port = " << ntohs(client_addr.sin_port) << endl;
		cout << "ip = " << inet_ntoa(client_addr.sin_addr) << endl;

		SOCKETINFO* sINFO = new SOCKETINFO;
		ZeroMemory(&sINFO->_overlapped, sizeof(sINFO->_overlapped));
		sINFO->_sock = client_sock;
		sINFO->_wsabuf.buf = sINFO->_databuf;
		sINFO->_wsabuf.len = BUFFER_SIZE;
		sINFO->_workflag = FLAG_RECV;

		int retval;
		DWORD recvbytes, flags = 0;
		retval = WSARecv(sINFO->_sock, &sINFO->_wsabuf, 1, &recvbytes, &flags, &sINFO->_overlapped, NULL);
		if (retval == SOCKET_ERROR)
		{
			if (WSAGetLastError() != ERROR_IO_PENDING)
			{
				cout << "main wsa_io_pending" << endl;
			}
			continue;
		}

	}


}
void cIOCP::PacketSend(SOCKETINFO* _ptr)
{
	ZeroMemory(&_ptr->_overlapped, sizeof(_ptr->_overlapped));
	_ptr->_workflag = FLAG_SEND;
	int retval;
	DWORD sendbytes;
	_ptr->_wsabuf.buf = _ptr->_databuf;
	_ptr->_wsabuf.len = BUFFER_SIZE;
	retval = WSASend(_ptr->_sock, &_ptr->_wsabuf, 1, &sendbytes, 0, &_ptr->_overlapped, NULL);
	if (retval == SOCKET_ERROR)
	{
		if (WSAGetLastError() != ERROR_IO_PENDING)
		{
			cout << "main wsa_io_pending" << endl;
		}
		
	}
}