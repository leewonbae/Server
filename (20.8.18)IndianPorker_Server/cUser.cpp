#include "cUser.h"
#include "cUserManager.h"
cUser::cUser()
{
	InitializeCriticalSection(&mCS);
	mMap.insert(map<int, fp>::value_type(PRO_LOGIN_REQ, &cUser::PRO_LOGIN));
	mMap.insert(map<int, fp>::value_type(PRO_NEWUSER_REQ, &cUser::PRO_NEWUSER));
	mMap.insert(map<int, fp>::value_type(PRO_MAKEROOM_REQ, &cUser::PRO_MAKEROOM));
	mMap.insert(map<int, fp>::value_type(PRO_ROOMLIST_REQ, &cUser::PRO_ROOMLIST));
	mMap.insert(map<int, fp>::value_type(PRO_INROOM_REQ, &cUser::PRO_INROOM));
	mMap.insert(map<int, fp>::value_type(PRO_READY_REQ, &cUser::PRO_READY));
	mMap.insert(map<int, fp>::value_type(PRO_BATTING_REQ, &cUser::PRO_BATTING));
	mMap.insert(map<int, fp>::value_type(PRO_CARD_REQ, &cUser::PRO_CARD));
	mMap.insert(map<int, fp>::value_type(PRO_GAME_END_REQ, &cUser::PRO_GAME_END));
}
cUser::~cUser()
{
	DeleteCriticalSection(&mCS);
}
int cUser::getMyroomnum()
{
	return mMyRoomNum;
}
void cUser::Parsing(OVERDATA* _over)
{
	
	PACKET_HEAD phead;
	memcpy(&phead, _over->mDatabuf, sizeof(PACKET_HEAD));

	mMapiter = mMap.find(phead.mProtocol_cmd);
	fp temp;
	temp = mMapiter->second;
	(this->*temp)(_over);
}
void cUser::SetDB(cUserDB* _db)
{
	mDBptr = _db;
}
void cUser::SetUM(cUserManager* _um)
{
	mUMptr = _um;
}
void cUser::SetRoomNum(int _roomnum)
{
	mMyRoomNum = _roomnum;
}
void cUser::PRO_LOGIN(OVERDATA* _over)
{
	PACKET_USERINFO ploginuser;
	memset(&ploginuser, 0, sizeof(PACKET_USERINFO));
	memcpy(&ploginuser, _over->mDatabuf + sizeof(PACKET_HEAD), sizeof(PACKET_USERINFO));

	if (mDBptr->CheckDB(ploginuser.mName, ploginuser.mPassword))
	{
		
		cUserManager* temp;
		EnterCriticalSection(&mCS);
		mUMptr->InputUser(this);
		LeaveCriticalSection(&mCS);
		Onsend(MSG_LOGIN_OK, mSendbuf);
	}
	else 
	{
		Onsend(MSG_LOGIN_FAIL, mSendbuf);
	}
}
void cUser::PRO_NEWUSER(OVERDATA* _over)
{
	PACKET_USERINFO puser;
	memset(&puser, 0, sizeof(PACKET_USERINFO));
	memcpy(&puser, _over->mDatabuf + sizeof(PACKET_HEAD), sizeof(PACKET_USERINFO));

	mDBptr->InputUserinfo(puser.mName, puser.mPassword);
	Onsend(PRO_NEWUSER_REQ, mSendbuf);
}
void cUser::PRO_MAKEROOM(OVERDATA* _over)
{
	mUMptr->Makeroom(this);
	 
}

void cUser::PRO_ROOMLIST(OVERDATA* _over)
{
	mUMptr->RoomList(this);
}
void cUser::PRO_INROOM(OVERDATA* _over)
{
	PACKET_IN_ROOM pinroom;
	memset(&pinroom, 0, sizeof(PACKET_IN_ROOM));
	memcpy(&pinroom, _over->mDatabuf + sizeof(PACKET_HEAD), sizeof(PACKET_IN_ROOM));
	mMyRoomNum = pinroom.roomnum;
	mUMptr->Inroom(this, pinroom.roomnum);
}
void cUser::PRO_READY(OVERDATA* _over)
{
	mUMptr->Ready(this);
	
}

void cUser::PRO_BATTING(OVERDATA* _over)
{
	//베팅을 얼마나 했는지 저장해놧다가, 결과를 보내줘야해, 
}
 
void cUser::PRO_CARD(OVERDATA* _over)
{
	//둘다 카드요청이 들어오면 서로 다른 패를 보여줘야해
}

void cUser::PRO_GAME_END(OVERDATA* _over)
{
	mUMptr->Delteroom(this);
	 
}
