#include "cMysql.h"
cMysql::cMysql()
{
	mysql_init(&mMysql);
	 
}
cMysql::~cMysql()
{
	mysql_close(&mMysql);
}

int cMysql::MakeConnectMysql()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	int max_connection = (int)si.dwNumberOfProcessors * 2 + 1;
	mCS_MYSQL.LOCK();
	for (int i = 0;i < max_connection;i++)
	{
		if (mConnectionArray[i] == NULL)
		{
			mConnectionArray[i] = mysql_real_connect(&mMysql, DB_HOST, DB_ID, DB_PASSWORD, DB_NAME, 3306, NULL, 0);
			mCS_MYSQL.UN_LOCK();
			return i;
		}
	}
	mCS_MYSQL.UN_LOCK();
	return -1;
	
}
void cMysql::UpdateUserinfo(cUser* _user)
{
	UpdateIteminfo(&_user->getUserinfo()->mItem_info, _user->getDBnum());
	UpdateGameRecordinfo(&_user->getUserinfo()->mGame_info, _user->getDBnum());

}
void cMysql::UpdateGameRecordinfo(GAME_RECONRD_INFO* _gamerecord, int _dbnum)
{
	int index = MakeConnectMysql();
	char sql_record[256] = { 0, };
	sprintf(sql_record, "CALL GAME_RECORD_UPDATE(%d,%d,%d,%d);",
		_dbnum, _gamerecord->mWinCount, _gamerecord->mLoseCount, _gamerecord->mDrawCount);
	int querystate = mysql_query(mConnectionArray[index], sql_record);
	if (querystate != 0)
	{
		PrintLastError(index);
	}
	
	ConnectClear(index);
}
void cMysql::UpdateIteminfo(ITEM_INFO* _iteminfo, int _dbnum)
{
	int index = MakeConnectMysql();
	char sql_item[256] = { 0, };
	for (int i = 0;i < MAX_ITEM_LIST;i++)
	{
		if (_iteminfo->mUpdateArray[i] == true)
		{
			sprintf(sql_item, "CALL ITEM_UPDATE(%d,%d,%d);",
				_dbnum, i, _iteminfo->mItemArray[i]);
			int querystate = mysql_query(mConnectionArray[index], sql_item);
			if (querystate != 0)
			{
				PrintLastError(index);
			}
		}
		
	}
	
	ConnectClear(index);
}
void cMysql::MysqlParsing(PACKET_HEAD* _phead, cSession* _session)
{
	cUser* user = (cUser*)_session;
	if (_phead->mCmd == PTC_LOGIN)
	{
		UseLoginCheck((PACKET_LOGIN*)_phead, (cUser*)_session);
		if (_phead->mPacket_ACK == PACKET_TRUE)
		{
			if (SetUserinfo(user->getUserinfo(), user->getDBnum()) == false)
			{
				_phead->mPacket_ACK = PACKET_FAIL;
			}
		}
	}
	if (_phead->mCmd == PTC_NEWUSER)
	{
		UseNewUser((PACKET_NEWUSER*)_phead, (cUser*) _session);
		_phead->mPacket_ACK = PACKET_TRUE;
	}
}


void cMysql::ConnectClear(int _index)
{
	mCS_MYSQL.LOCK();
	
	mysql_close(mConnectionArray[_index]);
	mConnectionArray[_index] = NULL;
	mCS_MYSQL.UN_LOCK();
}
 
void cMysql::UseLoginCheck(PACKET_LOGIN* _phead, cUser* _session)
{
	
	char sql_login[256] = { 0, };
	int cindex = MakeConnectMysql();
	MYSQL_RES* mysqlRes;
	MYSQL_ROW mysqlRow;

	sprintf(sql_login, "CALL CHECK_USERDATA('%s',%d); ",
		_phead->mID, _phead->mPassword);
	
	
	int query_state = mysql_query(mConnectionArray[cindex], sql_login);
	if (query_state != 0)
	{
		
		PrintLastError(cindex);
		_phead->mPacket_ACK = PACKET_FAIL;

	}
	else
	{
		

		mysqlRes = mysql_store_result(mConnectionArray[cindex]);
		while ((mysqlRow = mysql_fetch_row(mysqlRes)) != NULL)
		{
			if (strcmp(_phead->mID, mysqlRow[1]) == 0)
			{
				
				if (_phead->mPassword == stoi(mysqlRow[2]))
				{
					mCS_MYSQL.LOCK();
					mListIter = find(mUsingDBnumlist.begin(), mUsingDBnumlist.end(), stoi(mysqlRow[0]));
					
					if (mListIter == mUsingDBnumlist.end())
					{	
						mUsingDBnumlist.push_back(stoi(mysqlRow[0]));

						_session->setDBnum(stoi(mysqlRow[0]));
						_session->setAuthority(true);

						cout << "회원 정보 = " << stoi(mysqlRow[0]) << endl;
						_phead->mPacket_ACK = PACKET_TRUE;
						
						mCS_MYSQL.UN_LOCK();
						break;
					}
					else
					{
						mCS_MYSQL.UN_LOCK();
					}
					
					
				}
			}

		}
		 
		mysql_free_result(mysqlRes);
		
	}
	ConnectClear(cindex);
}

bool cMysql::SetUserinfo(USER_INFO* _userinfo ,int _dbnum)
{
	bool check = true;
	if (SetIteminfo(&_userinfo->mItem_info, _dbnum) == false)
	{
		check =  false;
	}	
	if (SetGameRecord(&_userinfo->mGame_info, _dbnum) == false)
	{
		check = false;
	}
	return check;
	 
}
bool cMysql::SetGameRecord(GAME_RECONRD_INFO* _gameinfo, int _dbnum)
{
	int index = MakeConnectMysql();
	MYSQL_RES* mysqlRes;
	MYSQL_ROW mysqlRow;

	char sql_gamerecord[256] = { 0, };
	sprintf(sql_gamerecord, "CALL GET_GAMERECORD(%d);", _dbnum);
	int query_state = mysql_query(mConnectionArray[index], sql_gamerecord);
	if (query_state != 0)
	{
		PrintLastError(index);
		ConnectClear(index);
		return false;
	}
	else
	{
		mysqlRes = mysql_store_result(mConnectionArray[index]);

		while ((mysqlRow = mysql_fetch_row(mysqlRes)) != NULL)
		{
			_gameinfo->mWinCount = stoi(mysqlRow[1]);
			_gameinfo->mLoseCount = stoi(mysqlRow[2]);
			_gameinfo->mDrawCount = stoi(mysqlRow[3]);

		}
		mysql_free_result(mysqlRes);
		ConnectClear(index);
		return true;
	}
}


bool cMysql::SetIteminfo(ITEM_INFO* _iteminfo, int _dbnum)
{
	int index = MakeConnectMysql();
	MYSQL_RES* mysqlRes;
	MYSQL_ROW mysqlRow;

	char sql_item[256] = { 0, };
	sprintf(sql_item, "CALL GET_ITEM_INFO(%d);", _dbnum);
	int query_state = mysql_query(mConnectionArray[index], sql_item);
	if (query_state != 0)
	{
		PrintLastError(index);
		ConnectClear(index);
		return false;
	}
	else
	{
		mysqlRes = mysql_store_result(mConnectionArray[index]);
	 
		while ((mysqlRow = mysql_fetch_row(mysqlRes)) != NULL)
		{
			_iteminfo->mItemArray[stoi(mysqlRow[1])] = stoi(mysqlRow[2]);
			 
		}
		mysql_free_result(mysqlRes);
		ConnectClear(index);
		return true;
	}
}
void cMysql::UseNewUser(PACKET_NEWUSER* _phead, cSession* _session)
{
	char sql_newuser[256] = { 0, };
	int cindex = MakeConnectMysql();
	
	sprintf(sql_newuser, "CALL INPUT_USERINFO('%s',%d);",
		_phead->mNew_ID,_phead->mNew_Password);
	
	mCS_MYSQL.LOCK();
	int query_state = mysql_query(mConnectionArray[cindex], sql_newuser);
	mCS_MYSQL.UN_LOCK();
	
	
	if (query_state != 0)
	{
		cout << "error" << endl;
		PrintLastError(cindex);
		_phead->mPacket_ACK = PACKET_FAIL;
	}
	else
	{
		cout << "회원가입 오케이" << endl;
		_phead->mPacket_ACK = PACKET_TRUE;
	}
	ConnectClear(cindex);
}


void cMysql::PrintLastError(int _index)
{
	cout << "///////////////mysql query error////////////// " << endl;
	cout << mysql_error(mConnectionArray[_index]) << endl;
}


/*
void cMy_sql::AllShowTBL(int _tblnum)
{
	char sql_select[256] = { 0, };
	string temp = "";
	switch (_tblnum)
	{
	case 1:
		temp = "TBL_USERINFO";
		break;
	case 2:

		break;
	default:
		break;
	}
	sprintf(sql_select, "SELECT * FROM %s;", temp.c_str());
	int query_stat = mysql_query(mConnections, sql_select);
	if (query_stat != 0)
	{
		cout << "state error" << endl;
	}
	else
	{
		mSql_result = mysql_store_result(mConnections);

		while ((mSql_row = mysql_fetch_row(mSql_result)) != NULL)
		{

			printf("%+1s %-30s %-10s\n", mSql_row[0], mSql_row[1], mSql_row[2]);
		}

		mysql_free_result(mSql_result);
	}

}
*/