#include "resouce.h"
#include "cUSER.h"

int main()
{
	cUSER iocp;
	iocp.Init();
	iocp.MakeThread();
	iocp.AcceptClient();
	return 0;
}