#pragma once
#include "Resource.h"
#include "Packet.h"
 
#include "cUser.h"

class cMySQL
{
public:
	// 공통 기능만 구현//
	// 숫자 관련해서는 제한//
	cMySQL();
	~cMySQL();

	void DB_connect();
	static void AllShowTBL(int _tblnum);

	//tbl 이름 가져오기
	static string getTBLname(int _tblnum);
	 
	// user 관련// 
	static bool InputUserData(PACKET_LOGIN* _packet);
	static bool CheckUserInfo(PACKET_LOGIN* _packet, cUser* _userSession);
	
	// 아이템 관련
	static bool Item_Get_Process(PACKET_ITEM_UPLOAD* _packet, int _dbnum);
	static bool Item_Use_Process(PACKET_ITEM_UPLOAD* _packet, int _dbnum);




private:
	static MYSQL* connections;
	static MYSQL_RES* sql_result;
	static MYSQL_ROW sql_row;
	
	MYSQL mysql;
	
};

