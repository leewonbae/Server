#pragma once
#include "Resource.h"
#include "packet.h"
#include "cCriticalSection.h"
#include "cLog.h"
#include <list>
#include <vector>

 
#include "cUser.h"
class cUserDB
{
public:
	cUserDB();
	~cUserDB();
	void DB_Parsing(PACKET_HEAD* _phead, cSession* _session);
	void NewUserDB(PACKET_HEAD* phead);// 
	void CheckUserDB(PACKET_HEAD* phead, cSession* _session);
	void ChangeScroe(PACKET_HEAD* phead, cSession* _session);
	void ShowData(PACKET_LOGIN plog, int _havescore);

private:
	 
	vector<pair<PACKET_LOGIN,int>> mUserList;
	vector<int> mScoreVector;
	cCriticalSection mDB_CS;
	int mUserDBCount;
};

