#include "cRoom.h"
cRoom::cRoom()
{
	mRoomUserCount = 0;
	mReadyCount = 0;
}
cRoom::~cRoom()
{

}
 

int cRoom::getUserCount()
{
	return mRoomUserCount;
}
bool cRoom::InUser(cUser* _user)
{
	for (int i = 0; i < 2;i++)
	{
		if (mUserArray[i] == NULL)
		{
			mCS_room.lock();
			mUserArray[i] = _user;
			_user->SetRoomIndex(i);
			mRoomUserCount++;
			mCS_room.Unlock();
			return true;
		}
	}

	return false;
}
bool cRoom::OutUser(cUser* _user)
{
	int getindex = _user->getRoomIndex();
	
	mCS_room.lock();
	if (Readyflag[getindex] == true)
	{
		Readyflag[getindex] = false;
		mReadyCount--;
	}
	mUserArray[getindex] = NULL;
	mRoomUserCount--;
	mCS_room.Unlock();
	return true;
}
void cRoom::ClearRoominfo()
{
	memset(mUserArray, NULL, sizeof(mUserArray));
	memset(Readyflag, false, sizeof(Readyflag));
	mRoomUserCount = 0;
	mRoomNumber = 0;
	mReadyCount = 0;
}
void cRoom::SendStartMsg()
{
	PACKET_GAME_CHECK pgamecheck;
	pgamecheck.mMsg = MSG_GAME_START;
	for (int i = 0;i < 2;i++)
	{
		mUserArray[i]->Onsend(&pgamecheck, pgamecheck.mPacket_size);
	}
}
int cRoom::ReadyCount(int _userindex)
{
	mCS_room.lock();
	Readyflag[_userindex] = true;
	mReadyCount++;
	mCS_room.Unlock();
	return mReadyCount;
}


void cRoom::CancleReady(int _userindex)
{
	mCS_room.lock();
	Readyflag[_userindex] = false;
	mReadyCount--;
	mCS_room.Unlock();
	 
}