#include "cIOCPhandle.h"
cIOCPhandle::cIOCPhandle()
{
	
}
cIOCPhandle::~cIOCPhandle()
{

}
 
void cIOCPhandle::MakeHandle()
{
	mHcp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
}

void cIOCPhandle::Set_CP_SOCKET(SOCKET _sock, cSession* _ptr)
{

	CreateIoCompletionPort((HANDLE)_sock, mHcp,(ULONG_PTR)_ptr ,0);
}

HANDLE cIOCPhandle::getIOCPhandle()
{
	return mHcp;
}