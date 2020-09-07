#include "cSession.h"


cSession::cSession()
{

}
cSession::~cSession()
{

}
void cSession::setSock(SOCKET _sock)
{
	mClientSock = _sock;
}
void cSession::setSockAddr(SOCKADDR_IN _sockaddr)
{
	mClientaddr = _sockaddr;
}

int cSession::getFleg()
{
	return mWorkfleg;
}

void cSession::OnRecv()
{
	DWORD recvbytes, flags = 0;
	int retval;
	mWorkfleg = FLEG_RECV;
	ZeroMemory(&mOverdata.mOver, sizeof(mOverdata.mOver));
	mOverdata.mWbuf.buf = mOverdata.mDatabuf;
	mOverdata.mWbuf.len = BUFFER_SIZE;
	WSARecv(mClientSock, &mOverdata.mWbuf, 1, &recvbytes, &flags, &mOverdata.mOver, NULL);
	

}
void cSession::OnSend(int _packetcmd,char* _data)
{
	DWORD sendbytes;
	int retval;
	mWorkfleg = FLEG_SEND;
	ZeroMemory(&mOverdata.mOver, sizeof(mOverdata.mOver));
	PACKET_HEAD phead;
	memset(&phead, 0, sizeof(PACKET_HEAD));
	phead.mCmd = _packetcmd;
	memcpy(_data, &phead, sizeof(PACKET_HEAD));
	mOverdata.mWbuf.buf = _data;
	mOverdata.mWbuf.len = BUFFER_SIZE;
	WSASend(mClientSock, &mOverdata.mWbuf, 1, &sendbytes, 0, &mOverdata.mOver, NULL);


}