#include "cDATABASE.h"
cDATABASE::cDATABASE()
{
	mUserCount = 0;
	mHead = NULL;
	mTail = NULL;
}
cDATABASE::~cDATABASE()
{

}
void cDATABASE::InputData(USERDATA* _userdata)
{
	mUserCount++;
	_userdata->mUserNum = mUserCount;
	if (mHead == NULL)
	{
		mHead = _userdata;
		mTail = _userdata;
	}
	else
	{
		mTail->mNextData = _userdata;
		mTail = _userdata;
	}

}
int cDATABASE::FindData(PACKET_USERDATA* _finddata)
{
	USERDATA* cur = mHead;
	if (cur == NULL)
	{
		cout << "cur == null" << endl;
		return USER_NO_DATA_ERROR;
	}
	while (cur != NULL)
	{
		if (strcmp(cur->mName, _finddata->mName) == 0 && cur->mPassword == _finddata->mPassword)
		{
			return cur->mUserNum;
		}
		else if (strcmp(cur->mName, _finddata->mName) == 0 && cur->mPassword != _finddata->mPassword)
		{
			return USER_PASSWORD_ERROR;
		}
		else
			cur = cur->mNextData;
			
		
	}
	return USER_NO_DATA_ERROR;
}
USERDATA* cDATABASE::getUSER(int _usernum)
{
	USERDATA* cur = mHead;
	
	while (cur != NULL)
	{
		if (cur->mUserNum == _usernum)
		{
			return cur;
			
		}
		cur = cur->mNextData;
	}
	
}
