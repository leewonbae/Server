#pragma once
#include "resource.h"
#include "cSession.h"
#include "cDatabase.h"
class cUser : public cSession
{
public:
	cUser();
	~cUser();

	typedef void (cUser::*fp)(OVERDATA* _over);
	virtual void Parsing(OVERDATA* _over);
	void setDB(cDatabase* _db);
private:
	void MSG_LOGIN(OVERDATA* _over);
	void MSG_ROOM(OVERDATA* _over);
	void MSG_RESERVATION(OVERDATA* _over);
	void MSG_ROOMCHATTING(OVERDATA* _over);
	cDatabase* mDatabase;
	PACKET_LOGIN mUserLogindata;
	bool mReservation;
	char mSendbuf[BUFFER_SIZE];
	int mRoomNuber;

	map<int, fp> mFmap;
	map<int, fp>::iterator mIter;
};

