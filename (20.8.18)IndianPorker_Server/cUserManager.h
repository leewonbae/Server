#pragma once
#include "cRoom.h"
#include "cUser.h"
struct USER_NODE {
	cUser* mUserptr;
	USER_NODE* mNextnode;


};
class cUserManager
{
	 
public:
	cUserManager();
	~cUserManager();
	void InputUser(cUser* _user);
	void Makeroom(cUser* _roomMaster);
	void Inroom(cUser* _user,int _reqroomnum);
	void Delteroom(cUser* _user);
	void Ready(cUser* _user);
	void RoomList(cUser* _user);
	void Cardreq(cUser* _user);
	void Battingreq(cUser* _user);
	void Startsetroom(int _roomnum);
private:
	cRoom* mRoomArray[10];
	cUser** mUserArray;
	char mSendbuf[BUFFER_SIZE];
	USER_NODE* mHead;
	USER_NODE* mTail;
	int mRoomCount;
	int mUsercount;
	
};

