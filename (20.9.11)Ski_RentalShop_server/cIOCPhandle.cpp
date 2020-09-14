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
	mHCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	cout << "HANDLE INIT OK" << endl;
}
void cIOCPhandle::SetHandle(SOCKET _sock, cSession* _session)
{
	cout << "handle set ok" << endl;
	CreateIoCompletionPort((HANDLE)_sock, mHCP, (ULONG_PTR)_session, 0);
}
HANDLE cIOCPhandle::getHandle()
{
	return mHCP;
}