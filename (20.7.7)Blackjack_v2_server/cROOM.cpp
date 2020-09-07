#include "cROOM.h"
cRoom::cRoom()
{
	mStartfleg = false;
	mUserCount = 0;
	for (int i = 0;i < 4;i++)
	{
		mUserArry[i] = NULL;
		mReadyArry[i] = false;
		mStandArry[i] = false;
	}
}
cRoom::~cRoom()
{
	 
}
void cRoom::setRoomNum(int _roomnum)
{
	mRoomNumber = _roomnum;
}
bool cRoom::getStartfleg()
{
	return mStartfleg;
}
int cRoom::getUserCount()
{
	return mUserCount;
}
void cRoom::setStartFleg(bool _setfleg)
{
	mStartfleg = _setfleg;
}
cSession** cRoom::getUserArry()
{
	return mUserArry;
}
void cRoom::EnterUser(cSession* _user)
{
	mUserArry[mUserCount] = _user;
	mUserCount++;
}
bool cRoom::outUser(cSession* _user)
{
	for (int i = 0;i < mUserCount;i++)
	{
		if (mUserArry[i] == _user)
		{
			mUserArry[i] = NULL;
		}
	}
	mUserCount--;
	if (mUserCount == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool cRoom::CheckStand(cSession* _user)
{
	for (int i = 0;i < mUserCount;i++)
	{
		if (mUserArry[i] == _user)
		{
			mStandArry[i] = true;
		}
	}

	for (int i = 0;i < mUserCount;i++)
	{
		if (mReadyArry[i] == false)
		{
			return false;
		}

	}
	return true;

}
bool cRoom::ReadyInput(cSession* _user)
{
	for (int i = 0;i < mUserCount;i++)
	{
		if (mUserArry[i] == _user )
		{
			mReadyArry[i] = true;
		}
	}
	if (mUserCount >= 2)
	{
		for (int i = 0;i < mUserCount;i++)
		{
			if (mReadyArry[i] == false)
			{
				return false;
			}
		
		}
		return true;
	}

	 
}