#include "cRoomManager.h"
cRoomManager::cRoomManager()
{
	mRoomCount = 0;
	 
}
cRoomManager::~cRoomManager()
{

}

 


void cRoomManager::RoomManager_Parsing(PACKET_HEAD* _packet, cUser* _user)
{
	switch (_packet->mCmd)
	{
	case PTC_READY_CHECK_CANCLE:
		RoomReadyCheck(_packet,_user);
		break;
	case PTC_ROOM_IN_OUT:
		InOutRoom(_packet,_user);
		break;
	case PTC_ROOM_MAKE:
		MakeRoomReq(_packet,_user);
		break;
	case PTC_ROOM_LIST:
		RoomListReq(_packet);
		break;
	default:
		cout << "room manager packet check error" << endl;
		break;
	}
}
void cRoomManager::InOutRoom(PACKET_HEAD* _packet, cUser* _user)
{
	PACKET_ROOM_IN_OUT* proominout = (PACKET_ROOM_IN_OUT*)_packet;
	
	if (proominout->InOutFlag == true)
	{
		if (mRoomArray[proominout->mWantInRoom]->InUser(_user) == true)
		{
			_packet->mMsg = MSG_IN_OK;
		}
		else
		{
			_packet->mMsg = MSG_IN_FAIL;
		}
	}
	else
	{
		if (mRoomArray[_user->getRoomNum()]->OutUser(_user) == true)
		{
			_packet->mMsg = MSG_OUT_OK;
			if (mRoomArray[_user->getRoomNum()]->getUserCount() == 0)
			{
				mCS_RoomManager.lock();

				cRoom* temp = mRoomArray[_user->getRoomNum()];
				mRoomArray[_user->getRoomNum()] = NULL;
				delete temp;
				mRoomCount--;

				mCS_RoomManager.Unlock();
			}
		}
		else
		{
			_packet->mMsg = MSG_OUT_FAIL;
		}
	}
}

void cRoomManager::MakeRoomReq(PACKET_HEAD* _packet,cUser* _user)
{
	if (mRoomCount + 1 <= MAX_ROOM_COUNT)
	{
		
		for (int i = 0;i < MAX_ROOM_COUNT;i++)
		{
			if (mRoomArray[i] == NULL)
			{
				mCS_RoomManager.lock();
				cRoom* newroom = new cRoom;
				mRoomArray[i] = newroom;
				newroom->InUser(_user);
				_user->SetRoomNum(i);
				mRoomCount++;

				mCS_RoomManager.Unlock();
			}
		}
	 
		_packet->mMsg = MSG_MAKE_ROOM_OK;
	}
	else
	{
		_packet->mMsg = MSG_MAKE_ROOM_FAIL;
	}
}
void cRoomManager::RoomReadyCheck(PACKET_HEAD* _packet,cUser* _user)
{
	PACKET_READY* pready = (PACKET_READY*)_packet;
	int roomnum = _user->getRoomNum();

	if (pready->mReadyFlag == true)
	{

		if (mRoomArray[roomnum]->ReadyCount(_user->getRoomIndex()) == 2)
		{
			
		}
		 
		_packet->mMsg = MSG_READY_OK;
		 
		
	}
	else
	{
		mRoomArray[roomnum]->CancleReady(_user->getRoomIndex());
		_packet->mMsg = MSG_READY_CANCLE_OK;
	}
}

void cRoomManager::RoomListReq(PACKET_HEAD* _packet)
{

}