#include "cAcceptor.h"
cAcceptor::cAcceptor()
{

}
cAcceptor::~cAcceptor()
{
	WSACleanup();
}

void cAcceptor::InitServer()
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
	
}

SOCKET cAcceptor::AcceptClient()
{
	SOCKET client;
	SOCKADDR_IN clientaddr;
	int len = sizeof(clientaddr);

	client = accept(mListenSock, (SOCKADDR*)&clientaddr, &len);

	
	return client;
}