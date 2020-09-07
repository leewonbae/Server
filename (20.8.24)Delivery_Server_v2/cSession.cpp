#include "cSession.h"
cSession::cSession()
{
	mUsercheck = false;
}
cSession::~cSession()
{

}
void cSession::Setsock(SOCKET _sock)
{
	mClientsock = _sock;
}
void cSession::SetUser(bool _checkuser)
{
	mUsercheck = _checkuser;
}
void cSession::SetKey(int _key)
{
	mKey = _key;
}
void cSession::Onrecv()
{
	DWORD recvbytes, flags = 0;
	ZeroMemory(&mOver.mOverlapped, sizeof(mOver.mOverlapped));
	ZeroMemory(&mOver.mDatabuf, sizeof(mOver.mDatabuf));

	mOver.mWsabuf.buf = mOver.mDatabuf;
	mOver.mWsabuf.len = BUFFER_SIZE;
	mOver.mWorkFleg = FLEG_RECV;

	WSARecv(mClientsock, &mOver.mWsabuf, 1, &recvbytes, &flags, &mOver.mOverlapped, NULL);
}
void cSession::Onsend(void* _data, int _size)
{
	DWORD sendbytes;
	ZeroMemory(&mOver.mOverlapped, sizeof(mOver.mOverlapped));
	ZeroMemory(&mOver.mDatabuf, sizeof(mOver.mDatabuf));
	memcpy(mOver.mDatabuf, _data, _size);
	mOver.mWsabuf.buf = mOver.mDatabuf;
	mOver.mWsabuf.len = BUFFER_SIZE;
	mOver.mWorkFleg = FLEG_SEND;

	WSASend(mClientsock, &mOver.mWsabuf, 1, &sendbytes,0, &mOver.mOverlapped, NULL);
}
int cSession::getKey()
{
	return mKey;
}
bool cSession::getUsercheck()
{
	return mUsercheck;
}