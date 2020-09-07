#include "cSession.h"
cSession::cSession()
{

}
cSession::~cSession()
{

}
void cSession::SetSOCK(SOCKET _sock)
{
	mSock = _sock;
}
void cSession::SetKEY(int _hashkey)
{
	mHashKey = _hashkey;
}
void cSession::Onrecv()
{
	DWORD recvbytes, flag = 0;
	ZeroMemory(&mOver.mOverlapped, sizeof(mOver.mOverlapped));
	mOver.mWsabuf.buf = mOver.mDatabuf;
	mOver.mWsabuf.len = BUFFER_SIZE;
	mOver.mWorkFleg = WORK_FLEG_RECV;

	WSARecv(mSock, &mOver.mWsabuf, 1, &recvbytes, &flag, &mOver.mOverlapped, NULL);
}
void cSession::Onsend(int _packetcmd, char* _databuf)
{
	DWORD sendbytes;
	PACKET_HEAD phead;
	memset(&phead, 0, sizeof(PACKET_HEAD));
	phead.mProtocol_cmd = _packetcmd;

	memcpy(_databuf, &phead, sizeof(PACKET_HEAD));
	mOver.mWsabuf.buf = _databuf;
	mOver.mWsabuf.len = BUFFER_SIZE;
	mOver.mWorkFleg = WORK_FLEG_SEND;

	WSASend(mSock, &mOver.mWsabuf, 1, &sendbytes, 0, &mOver.mOverlapped, NULL);
}
int cSession::getKey()
{
	return mHashKey;
}
