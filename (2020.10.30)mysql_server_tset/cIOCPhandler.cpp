#include "cIOCPhandler.h"
cIOCPhandler::cIOCPhandler()
{

}
cIOCPhandler::~cIOCPhandler()
{

}
void cIOCPhandler::MakeHcp()
{
	mHCP=CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
}

void cIOCPhandler::SetHCP(cSession* _sessionPtr, SOCKET _clientsock)
{
	CreateIoCompletionPort((HANDLE)_clientsock, mHCP, (ULONG_PTR)_sessionPtr, 0);
}
HANDLE cIOCPhandler::getHcp()
{
	return mHCP;
}