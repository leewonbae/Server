#include "cUserManager.h"
cUserManager::cUserManager()
{
	mUsercount = 0;
	mRoomCount = 0;
	mHead = NULL;
	 
}
cUserManager::~cUserManager()
{

}
void cUserManager::InputUser(cUser* _user)
{
	mUsercount++;
	USER_NODE* newnode = new USER_NODE;
	newnode->mUserptr = _user;
	newnode->mNextnode = NULL;

	if (mHead == NULL)
	{
		mHead = newnode;
	}
	else
	{
		mTail->mNextnode = newnode;
	}
	mTail = newnode;
}
void cUserManager::Makeroom(cUser* _user)
{
	cRoom* newroom = new cRoom;
	newroom->SetRoomnum(mRoomCount);
	newroom->Makeroom(_user);
	_user->SetRoomNum(mRoomCount);
	mRoomArray[mRoomCount] = newroom;
	mRoomCount++;
	_user->Onsend(PRO_MAKEROOM_REQ, mSendbuf);

}
void cUserManager::RoomList(cUser* _user)
{
	PACKET_ROOMLIST proomlist;
	memset(&proomlist, 0, sizeof(PACKET_ROOMLIST));
	proomlist.mRoomcount = mRoomCount;
	for (int i = 0;i < mRoomCount;i++)
	{
		proomlist.mRoomUser[i] = mRoomArray[i]->getCount();
	}
	memcpy(mSendbuf + sizeof(PACKET_HEAD), &proomlist, sizeof(PACKET_ROOMLIST));
	_user->Onsend(PRO_ROOMLIST_REQ, mSendbuf);
}
void cUserManager::Inroom(cUser* _user, int _reqroomnum)
{
	mRoomArray[_reqroomnum]->Inroom(_user);
	_user->Onsend(PRO_INROOM_REQ, mSendbuf);
}
void cUserManager::Startsetroom(int _roomnum)
{
	mRoomArray[_roomnum]->SetStart(true);
}
void cUserManager::Cardreq(cUser* _user)
{

}
void cUserManager::Battingreq(cUser* _user)
{

}
void cUserManager::Delteroom(cUser* _user)
{
	int roomnum = _user->getMyroomnum();
	_user->Onsend(PRO_GAME_END_REQ, mSendbuf);
	if (mRoomArray[roomnum]->DeleteReq()== true)
	{
		delete mRoomArray[roomnum];
		mRoomCount--;
	}
}
void cUserManager::Ready(cUser* _user)
{
	int roomkey;
	roomkey = _user->getMyroomnum();
	if (mRoomArray[roomkey]->SetReady(_user))
	{
		 
		
		if (mRoomArray[roomkey]->Startcheck())
		{
			mUserArray = mRoomArray[roomkey]->getUsers();
			for (int i = 0;i < 2;i++)
			{
				mUserArray[i]->Onsend(MSG_PLAY_OK, mSendbuf);
			}
		}
	}
	else
	{
		_user->Onsend(MSG_READY_FAIL, mSendbuf);
	}

}
