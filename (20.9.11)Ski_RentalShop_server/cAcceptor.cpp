#include "cAcceptor.h"
cAcceptor::cAcceptor()
{
	InitAcceptor();

}
cAcceptor::~cAcceptor()
{

}

void cAcceptor::InitAcceptor()
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

	cout << "ACCEPTOR INIT OK" << endl;
}
SOCKET cAcceptor::getClientSock()
{
	SOCKET clientsock;
	SOCKADDR_IN clientaddr;
	int len = sizeof(clientaddr);

	clientsock = accept(mListensock, (SOCKADDR*)&clientaddr, &len);


	return clientsock;
}
