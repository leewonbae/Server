#include "cIOCPhandle.h"
cIOCPhandle::cIOCPhandle()
{
	InitHandle();
}

cIOCPhandle::~cIOCPhandle()
{

}

void cIOCPhandle::InitHandle()
{
	mIOCPhandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
}

void cIOCPhandle::SetHandle(SOCKET _sock, cSession* _session)
{
	CreateIoCompletionPort((HANDLE)_sock, mIOCPhandle, (ULONG_PTR)_session, 0);
}

HANDLE cIOCPhandle::getHandle()
{
	return mIOCPhandle;
}