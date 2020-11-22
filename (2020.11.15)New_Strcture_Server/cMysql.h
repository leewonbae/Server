#pragma once
#include "Resource.h"
#include "cCriticalSection.h"
#include "cUser.h"
#include "Protocol.h"



class cMysql
{
public:
	cMysql();
	~cMysql();

	void MysqlParsing(PACKET_HEAD* _phead, cSession* _session);
	int MakeConnectMysql();
	void PrintLastError(int _index);
	void ConnectClear(int _index);

	// 유저 해당하는 정보 관련
	bool SetUserinfo(USER_INFO* _userinfo ,int _dbnum);
	bool SetIteminfo(ITEM_INFO* _iteminfo,int _dbnum);
	bool SetGameRecord(GAME_RECONRD_INFO* _gameinfo, int _dbnum);


	void UpdateUserinfo(cUser* _user);
	void UpdateIteminfo(ITEM_INFO* _iteminfo, int _dbnum);
	void UpdateGameRecordinfo(GAME_RECONRD_INFO* _gameinfo, int _dbnum);
	// 유저 id, password 관련
	void UseLoginCheck(PACKET_LOGIN* _phead, cUser* _session);
	void UseNewUser(PACKET_NEWUSER* _phead, cSession* _session);
	

private:
	cCriticalSection mCS_MYSQL;

	vector<int> mUsingDBnumlist;
	vector<int>::iterator mListIter;

	MYSQL mMysql;
	MYSQL* mConnectionArray[10] = { NULL, };
	
};

