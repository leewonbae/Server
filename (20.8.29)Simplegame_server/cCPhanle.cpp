#include "cCPhanle.h"
cCPhanle::cCPhanle()
{
	InitHandle();
}
cCPhanle::~cCPhanle()
{

}
void cCPhanle::InitHandle()
{
	mHCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
}
void cCPhanle::InputClient(SOCKET _sock, cSession* _session)
{
	CreateIoCompletionPort((HANDLE)_sock, mHCP, (ULONG_PTR)_session, 0);
}
HANDLE cCPhanle::getHandle()
{
	return mHCP;
}