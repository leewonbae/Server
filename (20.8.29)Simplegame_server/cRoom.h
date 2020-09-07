#pragma once
#include "Resource.h"
#include "Packet.h"
#include "cUser.h"
class cRoom
{
public:
	cRoom();
	~cRoom();
	void SetRoomNum(int _roomnum);

	void MakeInroom(cUser* _user);
	void LeaveRoom();
	void GameStartMsg();// 여기서 센드
	bool GameResult(cUser* _user, int _inputnum);// 여기서 센드


	bool getStartfleg();
	bool Ready();

	int getUsercount();
	int getRoomnum();
private:
	cUser* mRoomInUserArray[2];
	int mResultInputArray[2];
	int mInputcount;
	int mUsercount;
	int mReadycount;
	int mRoomnum;
	bool mStartfleg;
};

