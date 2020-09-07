#include "cServer.h"

int main()
{
	cServer server;
	server.MakeThread();
	server.AcceptClient();

	return 0;
}