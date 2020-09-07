#include "cRoom.h"
cRoom::cRoom()
{
	mUsercount = 0;
	mReadycount = 0;
	mStartfleg = false;
	mInputcount = 0;
}
cRoom::~cRoom()
{

}
void cRoom::SetRoomNum(int _roomnum)
{
	mRoomnum = _roomnum;
}

void cRoom::MakeInroom(cUser* _user)
{
	mRoomInUserArray[mUsercount] = _user;
	mUsercount++;
}
void cRoom::LeaveRoom()
{
	mUsercount--;
}
void cRoom::GameStartMsg()
{
	PACKET_READY pready;
	pready.mMsg = MSG_START_CHECK_OK;
	for (int i = 0;i < 2;i++)
	{
		mRoomInUserArray[i]->Onsend((void*)&pready, pready.mPacketSize);
	}

}
bool  cRoom::GameResult(cUser* _user, int _inputnum)
{
	mInputcount++;
	for (int i = 0;i < 2;i++)
	{
		if (mRoomInUserArray[i] == _user)
		{
			mResultInputArray[i] = _inputnum;
		}
	}
	if (mInputcount < 2)
	{
		return false;
	}
	else
	{
		PACKET_RESULT presult;
		if (mResultInputArray[0] < mResultInputArray[1])
		{
			presult.mMsg = MSG_RESULT_LOSE;
			mRoomInUserArray[0]->Onsend((void*)&presult, presult.mPacketSize);
			presult.mMsg = MSG_RESULT_WIN;
			mRoomInUserArray[1]->Onsend((void*)&presult, presult.mPacketSize);
		}
		else if (mResultInputArray[0] > mResultInputArray[1])
		{
			presult.mMsg = MSG_RESULT_WIN;
			mRoomInUserArray[0]->Onsend((void*)&presult, presult.mPacketSize);
			presult.mMsg = MSG_RESULT_LOSE;
			mRoomInUserArray[1]->Onsend((void*)&presult, presult.mPacketSize);
		}
		else
		{
			presult.mMsg = MSG_RESULT_DRAW;
			mRoomInUserArray[0]->Onsend((void*)&presult, presult.mPacketSize);
			mRoomInUserArray[1]->Onsend((void*)&presult, presult.mPacketSize);
		}

		return true;
	}
}
bool cRoom::Ready()
{
	mReadycount++;
	if (mUsercount == 2 && mReadycount == 2)
	{
		mStartfleg = true;
		return true;
	}
	return false;
}
bool cRoom::getStartfleg()
{
	return mStartfleg;
}


int cRoom::getRoomnum()
{
	return mRoomnum;
}
int cRoom::getUsercount()
{
	return mUsercount;
}
