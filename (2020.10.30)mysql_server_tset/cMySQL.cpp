#include "cMySQL.h"
MYSQL* cMySQL::connections =NULL;
MYSQL_RES* cMySQL::sql_result = NULL;
MYSQL_ROW  cMySQL::sql_row;


cMySQL::cMySQL()
{

}
cMySQL::~cMySQL()
{
	cout << "mysql close" << endl;
	mysql_close(&mysql);
}

void cMySQL::DB_connect()
{
	mysql_init(&mysql);
	connections = mysql_real_connect(&mysql, DB_HOST, DB_ID, DB_PASSWORD, DB_NAME, 3306, NULL, 0);
	if (connections == NULL)
	{
		cout << "NULL" << endl;

	}
	else
	{
		cout <<"SQL CONNECT OK  "<< mysql_get_client_info() << endl;
	}
}
 
string cMySQL::getTBLname(int _tblnum)
{
	string temp = "";

	switch (_tblnum)
	{
	case TBL_USERINFO:
		temp = "TBL_USERINFO";
		break;
	case CONSUMPTION_TBL:
		temp = "CONSUMPTION_TBL";
		break;
	case ITEM_ETC_TBL:
		temp = "ITEM_ETC_TBL";
		break;
	case WAPONE_TBL:
		temp = "WAPONE_TBL";
		break;

	case USER_INFO_LOG:
		temp = "USER_INFO_LOG";
		break;
	}

	return temp;
}


bool cMySQL::Item_Get_Process(PACKET_ITEM_UPLOAD* _packet, int _dbnum)
{
	char sql_get[256] = { 0, };
	string tbl_name = getTBLname(_packet->mItemKinds);
	_dbnum = 22;// test 를위해서 고정 숫자  나중에 지워줘야함

	cout <<"name = "<< _packet->mITEM_NAME << endl;
	sprintf(sql_get, "UPDATE %s SET %s = %s + %d WHERE USER_NUM = %d;",
		tbl_name.c_str(), _packet->mITEM_NAME, _packet->mITEM_NAME, _packet->mItemCount, _dbnum
	);

	int query_state = mysql_query(connections, sql_get);

	
	if(query_state !=0)
	{
		cout << "state error" << endl;
	}
	else
	{
		cout << "반영 확인" << endl;
		return true;
	}
	return false;
}
bool cMySQL::Item_Use_Process(PACKET_ITEM_UPLOAD* _packet, int _dbnum)
{
	string tbl_name = getTBLname(_packet->mItemKinds);
	char sql_use[256] = {0,};
	_dbnum = 22;////////////////////삭제 예정
	sprintf(sql_use, "SELECT %s FROM %s WHERE USER_NUM = %d",
		_packet->mITEM_NAME, tbl_name.c_str(), _dbnum
	);

	int query_state = mysql_query(connections, sql_use);
	if (query_state != 0)
	{
		cout << "use_error" << endl;
	}
	else
	{
		sql_result = mysql_store_result(connections);
		if ((sql_row = mysql_fetch_row(sql_result)) != NULL)
		{
			int item_have_count = stoi(sql_row[0]);
			if (item_have_count - _packet->mItemCount >= 0)
			{
				memset(sql_use, 0, sizeof(sql_use));
				sprintf(sql_use, "UPDATE %s SET %s = %s - %d WHERE USER_NUM = %d;",
					tbl_name.c_str(), _packet->mITEM_NAME, _packet->mITEM_NAME, _packet->mItemCount, _dbnum
				);

				int query_state = mysql_query(connections, sql_use);
				mysql_free_result(sql_result);
				return true;
			}
			
		}
		else
		{
			cout << "NO DATA" << endl;
		}
		mysql_free_result(sql_result);
	}


	return false;
}


bool cMySQL::InputUserData(PACKET_LOGIN* _packet)
{
	bool result = false;
	char sql_newuser[256] = { 0, };
	cout << "===========================" << endl;
	cout << "회원가입 데이터 아이디  = " << _packet->mName << endl;
	cout << "회원가입 데이터 비번 = " << _packet->mPassword << endl;
	cout << "===========================" << endl;
	 
	sprintf(sql_newuser, "SELECT * FROM TBL_USERINFO WHERE USER_ID = '%s' AND USER_PASSWORD = %d;",_packet->mName,_packet->mPassword);
	bool check_user = true;
	int query_stat = mysql_query(connections, sql_newuser);
	if (query_stat != 0)
	{
		cout << "state error" << endl;
	}
	else
	{
		
		sql_result = mysql_store_result(connections);
		cout << mysql_field_count(connections) << endl;
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL)// 같은 아이디가 잇다는 뜻
		{
			if (strcmp(sql_row[1], _packet->mName) == 0)
			{
				if (stoi(sql_row[2]) == _packet->mPassword)
				{
					check_user = false;
					break;
				}
			}
				

		}

		mysql_free_result(sql_result);
		if (check_user == true)
		{
				
			memset(sql_newuser, 0, sizeof(sql_newuser));
			sprintf(sql_newuser, "INSERT INTO TBL_USERINFO VALUE(NULL,'%s',%d) ;", _packet->mName, _packet->mPassword);
			int query_stat_newuser = mysql_query(connections, sql_newuser);
			if (query_stat_newuser == 0)
			{
				result = true;
				cout << "회원 정보 입력 완료" << endl;
				return result;
			}

			
		}

		
		 
	}
	return result;
}
bool cMySQL::CheckUserInfo(PACKET_LOGIN* _packet, cUser* _userSession)
{
	char sql_login[256] = { 0, };
	cout << "===========================" << endl;
	cout << "로그인 데이터 아이디  = " << _packet->mName << endl;
	cout << "로그인 데이터 비번 = " << _packet->mPassword << endl;
	cout << "===========================" << endl;
	bool check = false;
	sprintf(sql_login, "SELECT * FROM TBL_USERINFO WHERE USER_ID = '%s' AND USER_PASSWORD = %d;", _packet->mName,_packet->mPassword);
	int query_stat_login = mysql_query(connections, sql_login);
	if (query_stat_login == 0)
	{
		sql_result = mysql_store_result(connections);
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL)// 같은 아이디가 잇다는 뜻
		{
			cout << sql_row[1] << " , " << sql_row[2] << endl;
			if (strcmp(sql_row[1], _packet->mName) == 0)
			{
				
				if (stoi( sql_row[2]) ==  _packet->mPassword)
				{
					 
					_userSession->SetDB_Num(stoi(sql_row[0]));

					memset(sql_login, 0, sizeof(sql_login));
					sprintf(sql_login, "INSERT INTO USER_INFO_LOG VALUE(NULL,NOW(),'%s',%d,'LOG_IN');", _packet->mName, _packet->mPassword);
					query_stat_login = mysql_query(connections, sql_login);
					if (query_stat_login == 0)
					{
						cout << "회원 정보 입력 완료" << endl;
						check = true;
						break;
					}
				}
			}
			 
		}
		mysql_free_result(sql_result);
		if (check == true)
		{
			return true;
		}
		 
	}
	 
	cout << "login error" << endl;
	return false;
	 
}

void cMySQL::AllShowTBL(int _tblnum)
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
	int query_stat = mysql_query(connections, sql_select);
	if (query_stat != 0)
	{
		cout << "state error" << endl;
	}
	else
	{
		sql_result = mysql_store_result(connections);
		
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
		{
		
			printf("%+1s %-30s %-10s\n", sql_row[0], sql_row[1], sql_row[2]);
		}

		mysql_free_result(sql_result);
	}
	
}
