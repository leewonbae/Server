#pragma once
#include "Resource.h"
#include "cUser.h"
#include "cCriticalSection.h"
#include "Packet.h"

class cRoom
{
public:
	cRoom();
	~cRoom();

 

	bool InUser(cUser* _user);
	bool OutUser(cUser* _user);
	int getUserCount();
	void ClearRoominfo();
	void SendStartMsg();
	int ReadyCount(int _userindex);
	void CancleReady(int _userindex);

private:
	cUser* mUserArray[2] = {NULL,};
	bool Readyflag[2] = { false, };
	cCriticalSection mCS_room;
	int mRoomUserCount;
	int mRoomNumber;
	int mReadyCount;
};

