
#include "cThread.h"
#include "cServer.h"


int main()
{
	cThread thread;
	cServer server;

	thread.SetServer(&server);
	
	thread.MakeThread();
	server.ClientAccept();
	

	return 0;
}