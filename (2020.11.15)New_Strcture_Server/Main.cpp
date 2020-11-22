#include "Resource.h"
#include "cServer.h"
#include "cWorkerThread.h"
int main()
{
 
	cWorkerThread server;
	server.InitServer();
	server.MakeThread();
	server.MainAccept();
	
	 

	return 0;
}