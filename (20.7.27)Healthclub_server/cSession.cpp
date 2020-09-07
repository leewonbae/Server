#include "cSession.h"
cSession::cSession()
{
	mWorkFleg = FLEG_ACCEPT;
}
cSession::~cSession()
{

}
void cSession::OnRecv()
{
	DWORD recvbytes, flags = 0;
	int retval;
	mWorkFleg = FLEG_RECV;
	ZeroMemory(&mOverData.mOver, sizeof(mOverData.mOver));
	mOverData.mWsabuf.buf = mOverData.mDatabuf;
	mOverData.mWsabuf.len = BUFFER_SIZE;
	WSARecv(mClientsock, &mOverData.mWsabuf, 1, &recvbytes, &flags, &mOverData.mOver, NULL);

}

void cSession::OnSend(int _packet_cmd,char* _send_data)
{
	DWORD sendbytes;
	ZeroMemory(&mOverData.mOver, sizeof(mOverData.mOver));
	PACKET_HEAD phead;
	memset(&phead, 0, sizeof(PACKET_HEAD));
	phead.mCmd = _packet_cmd;
	memcpy(_send_data, &phead, sizeof(PACKET_HEAD));
	mOverData.mWsabuf.buf = _send_data;
	mOverData.mWsabuf.len = BUFFER_SIZE;
	mWorkFleg = FLEG_SEND;
	WSASend(mClientsock, &mOverData.mWsabuf, 1, &sendbytes, 0, &mOverData.mOver, NULL);
}


void cSession::SetConnect(int _connect)
{
	mConnect = _connect;
}
void cSession::SetSock(SOCKET _sock)
{
	mClientsock = _sock;
}
void cSession::SetAddr(SOCKADDR_IN _sockaddr)
{
	mClientaddr = _sockaddr;
}
int cSession::getfleg()
{
	return mWorkFleg;
}