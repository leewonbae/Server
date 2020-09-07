#include "cSession.h"
cSession::cSession()
{

}
cSession::~cSession()
{

}
void cSession::Setsock(SOCKET _sock)
{
	mSessionSOCK = _sock;
}
void cSession::SetAddr(SOCKADDR_IN _addr)
{
	mSessionAddr = _addr;
}
void cSession::Onrecv()
{
	DWORD recvbytes, flag = 0;
	ZeroMemory(&mOver_data.mOverLapped, sizeof(mOver_data.mOverLapped));
	mOver_data.mWsabuf.buf = mOver_data.mDatabuf;
	mOver_data.mWsabuf.len = BUFFER_SIZE;
	mOver_data.mFlegMode = FLEG_RECV;


	WSARecv(mSessionSOCK, &mOver_data.mWsabuf, 1, &recvbytes, &flag, &mOver_data.mOverLapped, NULL);


	
}
void cSession::OnSend(int _cmd, char* _databuf)
{
	DWORD sendbytes;
	ZeroMemory(&mOver_data.mOverLapped, sizeof(mOver_data.mOverLapped));
	
	PACKET_HEAD phead;
	memset(&phead, 0, sizeof(PACKET_HEAD));
	phead.mHeadCmd = _cmd;
	
	memcpy(_databuf, &phead, sizeof(PACKET_HEAD));
	
	mOver_data.mWsabuf.buf = _databuf;
	mOver_data.mWsabuf.len = BUFFER_SIZE;
	mOver_data.mFlegMode = FLEG_SEND;


	WSASend(mSessionSOCK, &mOver_data.mWsabuf, 1, &sendbytes, 0, &mOver_data.mOverLapped, NULL);



}