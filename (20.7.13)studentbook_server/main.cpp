#include "resource.h"
#include "cIOCP.h"
int main()
{
	cIOCP iocp;
	iocp.Init_Server();
	iocp.MakeCP();
	iocp.MakeThread();
	iocp.Acceptor();

	return 0;
}