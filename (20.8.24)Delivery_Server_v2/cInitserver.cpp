#include "cInitserver.h"
cInitserver::cInitserver()
{
	 
}
cInitserver::~cInitserver()
{
	 
}
void cInitserver::Init()
{
	cLog::Server_print(__FUNCTION__, " ");
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	mInitnsock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN serveraddr;
	serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(PORT);
	serveraddr.sin_family = AF_INET;

	bind(mInitnsock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));

	listen(mInitnsock, SOMAXCONN);

}
SOCKET cInitserver::getSock()
{
	 
	return mInitnsock;
}
SOCKET cInitserver::Acceptor()
{

	SOCKET clientsock;
	SOCKADDR_IN clientaddr;
	int addlen = sizeof(clientaddr);
	clientsock = accept(mInitnsock, (SOCKADDR*)&clientaddr, &addlen);
	
	return clientsock;

}