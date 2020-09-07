#include "cDatabase.h"
cDatabase::cDatabase()
{
	cout << "데이터 베이스를 불러 옵니다." << endl;
	mDBcount = 0;
	mHead = NULL;
	mTail = NULL;
}
cDatabase::~cDatabase()
{

}
void cDatabase::InputData(PACKET_LOGIN _logindata)
{

	NODE* newnode = new NODE;
	memcpy(&newnode->mLogindata, &_logindata, sizeof(PACKET_LOGIN));
	newnode->mReserveOk = false;
	newnode->nextnode = NULL;

	if (mHead == NULL)
	{
		mHead = newnode;
		mTail = newnode;
	}
	else
	{
		mTail->nextnode = newnode;
		mTail = newnode;
	}
	mDBcount++;
}
bool cDatabase::CheckReserv(PACKET_LOGIN _checkdata)
{
	NODE* cur = mHead;
	while (cur != NULL)
	{
		if (strcmp(cur->mLogindata.name, _checkdata.name) == 0)
		{
			if (cur->mLogindata.password == _checkdata.password)
			{
				cur->mReserveOk = true;
				return true;
			}
		}
		cur = cur->nextnode;
	}
	return false;
}

void cDatabase::ReservationRoom(int _roomnum,int _usercount, PACKET_LOGIN _checkdata)
{

	mRoomUser[_roomnum - 1] += _usercount;
	NODE* cur = mHead;
	while (cur != NULL)
	{
		if (strcmp(cur->mLogindata.name, _checkdata.name) == 0)
		{
			if (cur->mLogindata.password == _checkdata.password)
			{
				cur->mRoomNumber = _roomnum ;
			}
		}
		cur = cur->nextnode;
	}

}
int* cDatabase::getroomuser()
{
	return mRoomUser;
}

int cDatabase::getroomnumber(PACKET_LOGIN _checkdata)
{
	NODE* cur = mHead;
	while (cur != NULL)
	{
		if (strcmp(cur->mLogindata.name, _checkdata.name) == 0)
		{
			if (cur->mLogindata.password == _checkdata.password)
			{
				return cur->mRoomNumber;
			}
		}
		cur = cur->nextnode;
	}
	
}