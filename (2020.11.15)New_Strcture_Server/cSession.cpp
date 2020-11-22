#include "cSession.h"
cSession::cSession()
{
 
}
cSession::~cSession()
{

}
 
void cSession::OnRecv()
{
	DWORD recvbytes, flag = 0;

	ZeroMemory(&mRecv_Overdata.mOverlapped, sizeof(mRecv_Overdata.mOverlapped));
	ZeroMemory(mRecvBuf, BUFFER_SIZE);

	mRecv_Overdata.mWorkFlag = FLAG_RECV;
	mRecv_Overdata.mWsabuf.buf = mRecvBuf;
	mRecv_Overdata.mWsabuf.len = BUFFER_SIZE;

	WSARecv(mSock, &mRecv_Overdata.mWsabuf, 1, &recvbytes, &flag,
		&mRecv_Overdata.mOverlapped, NULL);


}
void cSession::OnSend(void* _packet, int _packet_size)
{
	DWORD sendbytes;
	ZeroMemory(&mSend_Overdata.mOverlapped, sizeof(mSend_Overdata.mOverlapped));
	ZeroMemory(mSendBuf, BUFFER_SIZE);

	memcpy(mSendBuf, _packet, _packet_size);


	mSend_Overdata.mWorkFlag = FLAG_RECV;
	mSend_Overdata.mWsabuf.buf = mSendBuf;
	mSend_Overdata.mWsabuf.len = BUFFER_SIZE;



	WSARecv(mSock, &mSend_Overdata.mWsabuf, 1, &sendbytes, 0,
		&mSend_Overdata.mOverlapped, NULL);

}