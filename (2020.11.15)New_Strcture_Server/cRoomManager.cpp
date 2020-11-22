#include "cRoomManager.h"
cRoomManager::cRoomManager()
{

}
cRoomManager::~cRoomManager()
{

}
void cRoomManager::SendMsgCheck(PACKET_HEAD* _phead, cUser* _user)
{
	if (_phead->mCmd == PTC_SEND_GAMESTATE_ACK)
	{
		PACKET_GAMESTATE* pstate = (PACKET_GAMESTATE*)_phead;
		if (pstate->mGameState == GAMESTATE_END)
		{
			mCS_RoomManager.LOCK();
			mDeleteCheckArray[pstate->mGameRoomNum]++;
			if (mDeleteCheckArray[pstate->mGameRoomNum] == 2)
			{
				mDeleteCheckArray[pstate->mGameRoomNum] = 0;
				cRoom* temp = mRoomArray[pstate->mGameRoomNum];
				mRoomArray[pstate->mGameRoomNum] = NULL;
				mRoomCount--;
				delete temp;
			}
			mCS_RoomManager.UN_LOCK();
		}
	}
}

void cRoomManager::RoomManagerParsing(PACKET_HEAD* _phead, cUser* _user)
{
	switch (_phead->mCmd)
	{
	case PTC_MAKEROOM_REQ:
		MakeRoomReq(_phead, _user);
		break;
	case PTC_INOUT_ROOM_REQ:
		InOutRoomReq(_phead, _user);
		break;
	case PTC_ROOMLIST_REQ:
		RoomListReq(_phead, _user);
		break;
	case PTC_READY_REQ:
		ReadyReq(_phead, _user);
		break;
	case PTC_ATTCK_REQ:
		AttackReq(_phead, _user);
		break;
	default:
		break;
	}
}

void cRoomManager::AttackReq(PACKET_HEAD* _phead, cUser* _user)
{
	cRoom* temp = mRoomArray[_user->getRoomNum()];
	temp->AttackUsers((PACKET_ATTACK*)_phead, _user);

}
void cRoomManager::ReadyReq(PACKET_HEAD* _phead, cUser* _user)
{
	cRoom* temp = mRoomArray[_user->getRoomNum()];
	PACKET_GAMESTATE pgame;
	pgame.mPacket_ACK = PACKET_TRUE;
	if (temp->ReadyUser(_user) == true)
	{
		pgame.mGameState = GAMESTATE_START;
		pgame.mGameRoomNum = _user->getRoomNum();
		temp->BroadMsg(&pgame, pgame.mPacket_size);
	}
	else
	{
		pgame.mGameState = 0;
		_user->OnSend(&pgame, pgame.mPacket_size);
	}
	
}

void cRoomManager::RoomListReq(PACKET_HEAD* _phead, cUser* _user)
{
	PACKET_ROOMLIST* plist = (PACKET_ROOMLIST*)_phead;
	int checkcount = 0;
	for (int i = 0;i < MAX_ROOM_SIZE;i++)
	{
		if (mRoomArray[i] != NULL)
		{
			if (mRoomArray[i]->getCondition() == false)
			{
				mCS_RoomManager.LOCK();
				plist->mRoomlist[i] = mRoomArray[i]->getUserCount();
				mCS_RoomManager.UN_LOCK();
				checkcount++;
			}
			
		}
		if (checkcount == mRoomCount)
		{
			break;
		}
	}
	_user->OnSend(plist, plist->mPacket_size);

}

void cRoomManager::InOutRoomReq(PACKET_HEAD* _phead, cUser* _user)
{
	PACKET_INOUT* pinout = (PACKET_INOUT*)_phead;
	
	bool checkreq = pinout->mCheckInOut;
	

	if (checkreq == true)// in 을 요구
	{
		int roomnum = pinout->mRoomnum;
		cRoom* temp = mRoomArray[roomnum];
		mCS_RoomManager.LOCK();
		if (temp->getUserCount() != 2)
		{
			_phead->mPacket_ACK = PACKET_TRUE;
			_user->setRoomNum(roomnum);
			temp->InputRoomUser(_user);
		}
		mCS_RoomManager.UN_LOCK();
		
	}
	else// out을 요구
	{
		mCS_RoomManager.LOCK();
		int outroom = _user->getRoomNum();
		cRoom* temp = mRoomArray[outroom];
		temp->OutRoomUser(_user);
		_user->setRoomNum(-1);
		if (temp->getUserCount() == 0)
		{
		
			mRoomArray[outroom] = NULL;
			mRoomCount--;
			delete temp;
		
		}
		mCS_RoomManager.UN_LOCK();
		_phead->mPacket_ACK = PACKET_TRUE;
	
	
	}
	_user->OnSend(pinout, pinout->mPacket_size);
}
void cRoomManager::MakeRoomReq(PACKET_HEAD* _phead, cUser* _user)
{
	PACKET_MAKEROOM* pmake = (PACKET_MAKEROOM*)_phead;
	if (mRoomCount >= MAX_ROOM_SIZE)
	{
		pmake->mPacket_ACK = PACKET_FAIL;
	}
	else
	{
		pmake->mPacket_ACK = PACKET_TRUE;	

		for (int i = 0;i < MAX_ROOM_SIZE;i++)
		{
			if (mRoomArray[i] == NULL)
			{
				mCS_RoomManager.LOCK();
				cRoom* newroom = new cRoom;
				mRoomArray[i] = newroom;
				newroom->InputRoomUser(_user);
				pmake->mRoomnum = i;
				_user->setRoomNum(i);
				mRoomCount++;
				mCS_RoomManager.UN_LOCK();
				break;
			}
		}
	}

	_user->OnSend(pmake, pmake->mPacket_size);
}