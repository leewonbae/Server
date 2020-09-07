#pragma once
#include "resource.h"

#include "cSession.h"
#include "cLOG.h"
#include "cUserDB.h"

class cUserManager;
class cUser : public cSession
{
	
public:
	cUser();
	~cUser();
	typedef void (cUser::* fp)(OVERDATA* _overdata);
	void SetDB(cUserDB* _db);
	void SetUM(cUserManager* _um);
	void SetRoomNum(int _roomnum);
	int getMyroomnum();
	void Parsing(OVERDATA* _over);
	
private:
	void PRO_LOGIN(OVERDATA* _over);
	void PRO_NEWUSER(OVERDATA* _over);
	void PRO_MAKEROOM(OVERDATA* _over);
	void PRO_ROOMLIST(OVERDATA* _over);
	void PRO_INROOM(OVERDATA* _over);
	void PRO_READY(OVERDATA* _over);
	void PRO_BATTING(OVERDATA* _over);
	void PRO_CARD(OVERDATA* _over);
	void PRO_GAME_END(OVERDATA* _over);
	CRITICAL_SECTION mCS;
	cUserDB* mDBptr;
	cUserManager* mUMptr;
	char mSendbuf[BUFFER_SIZE];
	map<int, fp> mMap;
	map<int, fp>::iterator mMapiter;
	

	int mMyRoomNum;
};

