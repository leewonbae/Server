#include "cSession.h"

cSession::cSession()
{
	mUsercheck = false;
	mKey = 0;

}
cSession::~cSession()
{

}
void cSession::Setkey(int _key)
{
	mKey = _key;
}
void cSession::SetSock(SOCKET _sock)
{
	mSOCK = _sock;
}
void cSession::SetUserCheck(bool _usercheck)
{
	mUsercheck = _usercheck;
}
void cSession::Onrecv()
{
	cout << "recv 받을 준비를 시작 합니다." << endl;
	DWORD recvbytes, flags = 0;
	ZeroMemory(&mOver.mOverlapped, sizeof(mOver.mOverlapped));
	ZeroMemory(&mOver.mDatabuf, sizeof(mOver.mDatabuf));

	mOver.mWsabuf.buf = mOver.mDatabuf;
	mOver.mWsabuf.len = BUFFER_SIZE;
	mOver.mWorkFleg = WORK_FLEG_RECV;

	WSARecv(mSOCK, &mOver.mWsabuf, 1, &recvbytes, &flags, &mOver.mOverlapped, NULL);
}
void cSession::Onsend(void* _packet, int _packetsize)
{
	DWORD sendbyes;
	ZeroMemory(&mOver.mOverlapped, sizeof(mOver.mOverlapped));


	mOver.mWorkFleg = WORK_FLEG_SEND;

	memcpy(mOver.mDatabuf, _packet, _packetsize);
	mOver.mWsabuf.buf = mOver.mDatabuf;
	mOver.mWsabuf.len = BUFFER_SIZE;

	WSASend(mSOCK, &mOver.mWsabuf, 1, &sendbyes, 0, &mOver.mOverlapped, NULL);
}
int cSession::getKey()
{
	return mKey;
}
bool cSession::getUserCheck()
{
	return  mUsercheck;
}
