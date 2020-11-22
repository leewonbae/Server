#include "cAcceptor.h"
cAcceptor::cAcceptor()
{

}
cAcceptor::~cAcceptor()
{
 
}
void cAcceptor::InitServer()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	mLsock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(PORT);
	serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	if (bind(mLsock, (SOCKADDR*)&serveraddr, sizeof(serveraddr)) == SOCKET_ERROR)
	{
		cout<<"bind error"<<endl;
	}

	if (listen(mLsock, SOMAXCONN) == SOCKET_ERROR)
	{
		cout << "listen error" << endl;
	}

	cout << "acceptor init ok" << endl;

}