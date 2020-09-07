#include "resource.h"
#include "cIOCP.h"
int main()
{
	cIOCP iocp;
	iocp.InitServer();
	iocp.MakeHCP();
	iocp.MakeThread();
	iocp.Acceptor();
	return 0;
}