#include "cSession.h"
cSession::cSession()
{
	mFlag = FlEG_ACCEPT;
}
cSession::~cSession()
{

}
void cSession::SetSOCK(SOCKET _sock)
{
	mSOCK = _sock;
}
void cSession::SetUserKey(int _userkey)
{
	mUserKey = _userkey;
}
int cSession::getfleg()
{
	return mFlag;
}
int cSession::getkey()
{
	return mUserKey;
}


void cSession::Onsend(int _cmd, char* _databuf)
{
	PACKET_HEAD phead;
	ZeroMemory(&mOver.mOverlapped, sizeof(mOver.mOverlapped));
	phead.sPacketCmd = _cmd;
	DWORD sendbytes;
	memcpy(_databuf, &phead, sizeof(PACKET_HEAD));
	mOver.mWsabuf.buf = _databuf;
	mOver.mWsabuf.len = BUFFER_SIZE;
	mFlag = FLEG_SEND;
	
	WSASend(mSOCK, &mOver.mWsabuf, 1, &sendbytes, 0, &mOver.mOverlapped, NULL);
}
void cSession::Onrecv()
{
	ZeroMemory(&mOver.mOverlapped, sizeof(mOver.mOverlapped));
	DWORD recvbytes,flags=0;
	mOver.mWsabuf.buf = mOver.mDatabuf;
	mOver.mWsabuf.len = BUFFER_SIZE;
	mFlag = FLEG_RECV;
	WSARecv(mSOCK, &mOver.mWsabuf, 1, &recvbytes, &flags, &mOver.mOverlapped, NULL);
}