#include "cSession.h"
cSession::cSession()
{
	mSessionKey = 0;
	mUserMode = false;
}
cSession::~cSession()
{

}

void cSession::SetSock(SOCKET _sock)
{
	mSocket = _sock;
}
void cSession::SetKey(int _key)
{
	mSessionKey = _key;
}
void cSession::SetUserMode(bool _check)
{
	mUserMode = _check;
}
int cSession::getkey()
{
	return mSessionKey;
}
bool cSession::getMode()
{
	return mUserMode;
}

void cSession::OnRecv()
{
	DWORD recvbytes, flags = 0;
	ZeroMemory(&mOver.mOverlapped, sizeof(mOver.mOverlapped));
	// 초기화를 해줘야한다.
	ZeroMemory(&mOver.mDataBuf, sizeof(mOver.mDataBuf));
	mOver.mWsabuf.buf = mOver.mDataBuf;
	mOver.mWsabuf.len = BUFFER_SIZE;
	mOver.mMODE = MODE_RECV;
	
	WSARecv(mSocket, &mOver.mWsabuf, 1, &recvbytes, &flags, &mOver.mOverlapped, NULL);
	

}
void cSession::OnSend(void* _packet, int packet_size)
{
	DWORD sendbytes;
	memcpy(mOver.mDataBuf, _packet, packet_size);
	mOver.mWsabuf.buf = mOver.mDataBuf;
	mOver.mWsabuf.len = BUFFER_SIZE;
	mOver.mMODE = MODE_SEND;

	WSASend(mSocket, &mOver.mWsabuf, 1, &sendbytes, 0, &mOver.mOverlapped, NULL);


}