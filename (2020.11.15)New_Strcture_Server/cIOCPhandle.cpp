#include "cIOCPhandle.h"
cIOCPhandle::cIOCPhandle()
{

}
cIOCPhandle::~cIOCPhandle()
{

}

void cIOCPhandle::InitHCP()
{
	mHCP= CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
}
void cIOCPhandle::CreateHcpListenSOCK(SOCKET _listensock)
{
	CreateIoCompletionPort((HANDLE)_listensock, mHCP, 0, 0);
}
void cIOCPhandle::CreateHcpClientSOCK(SOCKET _clientsock, cSession* _session)
{
	CreateIoCompletionPort((HANDLE)_clientsock, mHCP, (ULONG_PTR)_session, 0);
}
 