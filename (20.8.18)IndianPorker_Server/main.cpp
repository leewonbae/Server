#include "cIOCP.h"

int main()
{

	cIOCP iocp;
	cUserDB DB;
	iocp.InitServer();
	iocp.MakeHcp();
	iocp.MakeThread();
	iocp.Acceptor(&DB);
	return 0;
}