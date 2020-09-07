#include "cSession.h"

cSession::cSession()
{
	 
}
cSession::~cSession()
{

}
void cSession::SetSOCK(SOCKET _sock)
{
	mMYsock = _sock;
}
void cSession::SetAddr(SOCKADDR_IN _sockaddr)
{
	mMYaddr = _sockaddr;
}
 
void cSession::SetUser(USERDATA* _userdata)
{
	mUser = _userdata;
	cout << mUser->mName << endl;
	cout << mUser->mPassword << endl;
}
void cSession::SetmStartRoomNumber(int _startnum)
{
	mStartRoomNumber = _startnum;
}
void cSession::SetRoomNum(int _roomnum)
{
	mRoomNumber = _roomnum;
}
int cSession::getFleg()
{
	return mOverdata.mSOCKETworkflag;
}
int cSession::getStartRoomNumber()
{
	return mStartRoomNumber;
}
int cSession::getRoomNumber()
{
	return mRoomNumber;
}
void cSession::InputMoney(int _inputmoney)
{
	mUser->mMoney += _inputmoney;
}
void cSession::OutputMoney(int _inputmoney)
{
	mUser->mMoney += _inputmoney;
	if(mUser->mMoney<0 ){
		mUser->mMoney = 0;
	}
}
void cSession::OnSend(char* _inputdata)
{

	DWORD sendbytes;
	ZeroMemory(&mOverdata.mSOCKETover, sizeof(mOverdata.mSOCKETover));
	mOverdata.mSOCKETbuf.buf = _inputdata;
	mOverdata.mSOCKETbuf.len = BUFFER_SIZE;
	mOverdata.mSOCKETworkflag = FLEG_SEND;
	WSASend (mMYsock, &mOverdata.mSOCKETbuf, 1, &sendbytes, 0, &mOverdata.mSOCKETover, NULL);
}

void cSession::OnRecv()
{
	 
	DWORD recvbytes, flags = 0;
	ZeroMemory(&mOverdata.mSOCKETover, sizeof(mOverdata.mSOCKETover));
	mOverdata.mSOCKETbuf.buf = mOverdata.mDatabuf;
	mOverdata.mSOCKETbuf.len = BUFFER_SIZE;
	mOverdata.mSOCKETworkflag = FLEG_RECV;
	WSARecv(mMYsock, &mOverdata.mSOCKETbuf, 1, &recvbytes, &flags, &mOverdata.mSOCKETover, NULL);
}