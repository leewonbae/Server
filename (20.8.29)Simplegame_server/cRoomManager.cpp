#include "cRoomManager.h"
cRoomManager::cRoomManager()
{
	mRoomcount = 0;

}

cRoomManager::~cRoomManager()
{

}

void cRoomManager::RoomParsing(cUser* _user, PACKET_HEAD* _recvpacket)
{
	switch (_recvpacket->mCmd)
	{
	case PTC_ROOMLIST_REQ:
		cout << "PTC_ROOMLIST_REQ" << endl;
		setRoomLIST(_user, _recvpacket);
		break;
	case PTC_IN_ROOM_REQ:
		cout << "PTC_IN_ROOM_REQ" << endl;
		InRoom(_user, _recvpacket);
		break;
	case PTC_MAKE_ROOM_REQ:
		cout << "PTC_MAKE_ROOM_REQ" << endl;
		MakeRoom(_user, _recvpacket);
		break;
	case PTC_READY_REQ:
		cout << "PTC_READY_REQ" << endl;
		ReayReq(_user, _recvpacket);
		break;
	case PTC_GAME_RESULT_REQ:
		cout << "PTC_GAME_RESULT_REQ" << endl;
		GameResult(_user, _recvpacket);
		break;
	}
}
void cRoomManager::GameResult(cUser* _user, PACKET_HEAD* _recvpacket)
{
	PACKET_RESULT* presult = (PACKET_RESULT*)_recvpacket;
	int roomnum = _user->getRoomNUM();
	if (mRoomArray[roomnum]->GameResult(_user, presult->mInputnum))
	{
		DelteRoom(roomnum);
	}
}
void cRoomManager::MakeRoom(cUser* _user, PACKET_HEAD* _recvpacket)
{
	PACKET_MAKEROOM pmakeroom;
	if (mRoomcount > 20)
	{
		pmakeroom.mMsg = MSG_MAKEROOM_FAIL;
	}
	else {
		cRoom* newroom = new cRoom;
		for (int i = 0;i < 20;i++)
		{
			if (mRoomArray[i] == NULL)
			{
				pmakeroom.mMsg = MSG_MAKEROOM_OK;
				newroom->SetRoomNum(i);
				newroom->MakeInroom(_user);
				mRoomArray[i] = newroom;
				_user->SetRoomNum(i);
				mRoomcount++;
				break;
			}

		}
	}

	_user->Onsend((void*)&pmakeroom, pmakeroom.mPacketSize);


}
void cRoomManager::InRoom(cUser* _user, PACKET_HEAD* _recvpacket)
{
	PACKET_INROOM* pinroom = (PACKET_INROOM*)_recvpacket;
	if (mRoomArray[pinroom->mChoiceRoomNum]->getStartfleg() == false &&
		mRoomArray[pinroom->mChoiceRoomNum]->getUsercount() < 2)
	{
		mRoomArray[pinroom->mChoiceRoomNum]->MakeInroom(_user);
		_user->SetRoomNum(pinroom->mChoiceRoomNum);
		_recvpacket->mMsg = MSG_INROOM_OK;
	}
	else
	{
		_recvpacket->mMsg = MSG_INROOM_FAIL;
	}


	_user->Onsend((void*)pinroom, pinroom->mPacketSize);

}
void cRoomManager::setRoomLIST(cUser* _user, PACKET_HEAD* _recvpacket)
{
	PACKET_ROOMLIST* plist = (PACKET_ROOMLIST*)_recvpacket;

	for (int i = 0;i < 20;i++)
	{
		if (mRoomArray[i] == NULL)
		{
			continue;
		}
		else
		{
			plist->mRoomArray[plist->mRoomcount] = mRoomArray[i]->getRoomnum();
			plist->mRoomcount++;
		}

	}
	_user->Onsend((void*)plist, plist->mPacketSize);

}
void cRoomManager::ReayReq(cUser* _user, PACKET_HEAD* _recvpacket)
{
	int roomnum = _user->getRoomNUM();
	cout << "roomnum = " << roomnum;
	if (mRoomArray[roomnum]->Ready())
	{
		cout << "start msg send" << endl;
		mRoomArray[roomnum]->GameStartMsg();
	}
	else
	{
		cout << " 조건 충족 x" << endl;
	}

}
void cRoomManager::DelteRoom(int _roomnum)
{
	mRoomcount--;
	cRoom* temproom = mRoomArray[_roomnum];
	mRoomArray[_roomnum] = NULL;

	delete temproom;
}
