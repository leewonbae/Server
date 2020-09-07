#pragma once
#include "resource.h"
#include "cSession.h"
class cUser : public cSession
{
public:
	cUser();
	~cUser();

	typedef void (cUser::* fp)(OVERDATA* _over);
	void Parsing(OVERDATA* over);
	void SetDatabase(cDatabase* _database);
private:
	void MSG_NEWUSER(OVERDATA* over);
	void MSG_LOGIN(OVERDATA* over);
	void MSG_NOTICE_CHECK(OVERDATA* over);
	void MSG_DATA(OVERDATA* over);
	void MSG_NOTICE_SEND(OVERDATA* over);
	void MSG_DATA_SEND(OVERDATA* over);
	cDatabase* mDatabase;
	char mSendbuf[BUFFER_SIZE];
	map<int, fp> mFmap;
	map<int, fp>::iterator mMapIteratior;
};

