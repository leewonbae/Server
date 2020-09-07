#include "cServer.h"

int main()
{
	cServer server;
	server.MakeThread();
	server.Acceptor();
	return 0;
}