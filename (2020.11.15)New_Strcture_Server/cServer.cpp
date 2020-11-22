#include "cServer.h"

cServer::cServer()
{
	cout << "server in" << endl;
}
cServer::~cServer()
{
	cout << "server out" << endl;
	closesocket(mListensock);
	WSACleanup();
}
void cServer::OutSession(cSession* _session)
{
	mSessionManager.OutSession(_session);
}
void cServer::InitServer()
{
	cAcceptor Acceptor;
	mIOCPhandle.InitHCP();
	Acceptor.InitServer();
	
	mListensock = Acceptor.getlistensock();
	if (mListensock == INVALID_SOCKET)
	{
		cout << "socket error" << endl;
	}
	mIOCPhandle.CreateHcpListenSOCK(mListensock);
	 
}

void cServer::MainAccept()
{
	
	while (1)
	{
		SOCKADDR_IN clientaddr;
		int len = sizeof(clientaddr);
		SOCKET client = accept(mListensock, (sockaddr*)&clientaddr, &len);
		
		cSession* temp =  mSessionManager.getNewSession();
		if (temp != NULL)
		{
			temp->setSOCK(client);
			mIOCPhandle.CreateHcpClientSOCK(client, temp);
			temp->OnRecv();
		}
		else
		{
			cout << "클라이언트 MAX COUNT 초과" << endl;
		}
	}
}

