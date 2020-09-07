#include "cClient.h"
cClient::cClient()
{
	cout << "클라이언트 생성자" << endl;
	mWorkfleg = FLEG_ACCEPT;

}
cClient::~cClient()
{

}
void cClient::setSock(SOCKET _sock)
{
	mSock = _sock;
}
void cClient::setAddr(SOCKADDR_IN _sockaddr)
{
	mAddr = _sockaddr;
}
void cClient::setWorkfleg(int _fleg)
{
	mWorkfleg = _fleg;
}
int cClient::getWorkfleg( )
{
	return mWorkfleg;
}
void cClient::ShowIP_PORT()
{
	cout << "IP    =  "<<inet_ntoa(mAddr.sin_addr) << endl;
	cout << "PORT  =  " << ntohs(mAddr.sin_port) << endl;
}
void cClient::OnRecv()
{
	DWORD recvbytes, flags = 0;
	ZeroMemory(&mOver.mOver, sizeof(mOver.mOver));
	setWorkfleg(FLEG_RECV);
	mOver.mWbuf.buf = mOver.mDatabuf;
	mOver.mWbuf.len = BUFFER_SIZE;
	WSARecv(mSock, &mOver.mWbuf, 1, &recvbytes, &flags, &mOver.mOver, NULL);
}
void cClient::OnSend(int _mCmd, char* _inputdata)
{
	DWORD sendbytes;
	ZeroMemory(&mOver.mOver, sizeof(mOver.mOver));
	setWorkfleg(FLEG_SEND);
	PACKET_HEAD phead;
	memset(&phead, 0, sizeof(PACKET_HEAD));
	phead.mCmd = _mCmd;
	phead.mPacketSize = sizeof(_inputdata);
	mOver.mWbuf.buf = _inputdata;
	mOver.mWbuf.len = BUFFER_SIZE;
	WSASend(mSock, &mOver.mWbuf, 1, &sendbytes,0, &mOver.mOver, NULL);
}