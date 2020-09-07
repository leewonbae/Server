#include "cIOCP.h"
int main()
{
	cIOCP iocp;
	iocp.InitServer();
	iocp.MakeHCP();
	iocp.MakeThread();
	iocp.MakeAdmin();
	iocp.Acceptor();
	return 0;
}