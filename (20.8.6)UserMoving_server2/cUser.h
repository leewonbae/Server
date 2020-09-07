#pragma once
#include "resource.h"
#include "cSession.h"
class cUser  
{
public:
	cUser();
	~cUser();

	typedef void (cUser::* fp)(OVERDATA* _over);
	void Parsing(OVERDATA* over);
	void SetUserarray(cSession** _userarray);
	void SetUsercount(int* _usercount);
	void SetEvent(HANDLE* _handle);
private:
	void MSG_NEWUSER(OVERDATA* over);
	void MSG_USERMOVE(OVERDATA* over);
	
	
	
	HANDLE* mEventhandle;
	char mSendbuf[BUFFER_SIZE];
	cSession** mUserarray;
	int* mUsercount;
	map<int, fp> mFmap;
	map<int, fp>::iterator mMapIteratior;
};

