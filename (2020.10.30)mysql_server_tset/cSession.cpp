#include "cSession.h"
cSession::cSession()
{
	mUserCheck = false;
	mKey = MAX_SESSION_ARRAY;
}
cSession::~cSession()
{

}

void cSession::SetSock(SOCKET _socket)
{
	mSock = _socket;
}
void cSession::SetUser(bool _check)
{
	mUserCheck = _check;
}
void cSession::SetKey(int _key)
{
	mKey = _key;
}

bool cSession::getUserCheck()
{
	return mUserCheck;
}
int cSession::getKey()
{
	return mKey;
}
void cSession::OnRecv()
{
	DWORD recvbytes, flag = 0;

	ZeroMemory(&mOverdata.mOverlapped, sizeof(mOverdata.mOverlapped));
	ZeroMemory(&mOverdata.mDatabuf, BUFFER_SIZE);

	mOverdata.mWsabuf.buf = mOverdata.mDatabuf;
	mOverdata.mWsabuf.len = BUFFER_SIZE;
	mOverdata.mWorkFleg = WORKFLEG_RECV;

	WSARecv(mSock, &mOverdata.mWsabuf, 1, &recvbytes, &flag, &mOverdata.mOverlapped, NULL);

}
void cSession::Onsend(void* _packet, int _packetsize)
{
	DWORD sendbytes;
	ZeroMemory(&mOverdata.mDatabuf, BUFFER_SIZE);
	//ZeroMemory(&mOverdata.mOverlapped, sizeof(mOverdata.mOverlapped));
	

	memcpy(mOverdata.mDatabuf, _packet, _packetsize);

	mOverdata.mWsabuf.buf = mOverdata.mDatabuf;
	mOverdata.mWsabuf.len = BUFFER_SIZE;
	mOverdata.mWorkFleg = WORKFLEG_SEND;

	WSASend(mSock, &mOverdata.mWsabuf, 1, &sendbytes, 0, &mOverdata.mOverlapped, NULL);

}