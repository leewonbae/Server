#include "cSession.h"
cSession::cSession()
{
	mUsermode = false;

}
cSession::~cSession()
{

}
void cSession::SetSock(SOCKET _sock)
{
	mSocket = _sock;
}
void cSession::ChangeUserMode(bool _modechange)
{
	mUsermode = _modechange;
}
void cSession::SetKey(int _key)
{
	mKey = _key;
}
void cSession::Onrecv()
{
	cout << "recv 받을 준비를 시작 합니다." << endl;
	DWORD recvbytes, flags = 0;
	ZeroMemory(&mOver.mOverlapped, sizeof(mOver.mOverlapped));
	ZeroMemory(&mOver.mDatabuf, sizeof(mOver.mDatabuf));

	mOver.mWsabuf.buf = mOver.mDatabuf;
	mOver.mWsabuf.len = BUFFER_SIZE;
	mOver.mWork_fleg = WORK_FLEG_RECV;

	WSARecv(mSocket, &mOver.mWsabuf, 1, &recvbytes, &flags, &mOver.mOverlapped, NULL);
}
void cSession::Onsend(void* _data, int _size)
{
	cout << "send 데이터를 보냅니다." << endl;
	DWORD sendbytes;
	ZeroMemory(&mOver.mOverlapped, sizeof(mOver.mOverlapped));

	memcpy(mOver.mDatabuf, _data, _size);
	mOver.mWsabuf.buf = mOver.mDatabuf;
	mOver.mWsabuf.len = BUFFER_SIZE;
	mOver.mWork_fleg = WORK_FLEG_SEND;

	WSASend(mSocket, &mOver.mWsabuf, 1, &sendbytes, 0, &mOver.mOverlapped, NULL);
}
bool cSession::getModeCheck()
{
	return mUsermode;
}

int cSession::getKey()
{
	return mKey;
}