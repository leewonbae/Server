#include "cRoom.h"
cRoom::cRoom()
{
	mUsercount = 0;
	mRoomNum = 0;
	mStartfleg = false;
	mDeleteReqCount = 0;
}
cRoom::~cRoom()
{

}
int cRoom::getCount()
{
	return  mUsercount;
}
int cRoom::getRoomnum()
{
	return  mRoomNum;
}
cUser** cRoom::getUsers()
{
	return  mUserarray;
}
void cRoom::SetStart(bool _fleg)
{
	mStartfleg = _fleg;
}
void cRoom::SetRoomnum(int _roomnum)
{
	mRoomNum = _roomnum;
}
void cRoom::Makeroom(cUser* _user)
{
	mUserarray[0] = _user;
	mUsercount++;
}
void cRoom::Inroom(cUser* _user)
{
	mUserarray[1] = _user;
	mUsercount++;
}
bool cRoom::DeleteReq()
{
	mDeleteReqCount++;
	if (mDeleteReqCount >= 2)
	{
		return true;
	}
	else
		return false;
}
bool cRoom::SetReady(cUser* _user)
{
	for (int i = 0;i < mUsercount;i++)
	{
		if (mUserarray[i] == _user)
		{
			mReadyArray[i] = true;
			return true;
		}
	}
	return false;
	
}
bool cRoom::Startcheck()
{
	if (mUsercount >= 2)
	{
		for (int i = 0;i < mUsercount;i++)
		{
			if (mReadyArray[i] == false)
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
	
}