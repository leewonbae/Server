#pragma once
#include "Resource.h"
#include "Packet.h"
 
#include "cUser.h"

class cMySQL
{
public:
	// ���� ��ɸ� ����//
	// ���� �����ؼ��� ����//
	cMySQL();
	~cMySQL();

	void DB_connect();
	static void AllShowTBL(int _tblnum);

	//tbl �̸� ��������
	static string getTBLname(int _tblnum);
	 
	// user ����// 
	static bool InputUserData(PACKET_LOGIN* _packet);
	static bool CheckUserInfo(PACKET_LOGIN* _packet, cUser* _userSession);
	
	// ������ ����
	static bool Item_Get_Process(PACKET_ITEM_UPLOAD* _packet, int _dbnum);
	static bool Item_Use_Process(PACKET_ITEM_UPLOAD* _packet, int _dbnum);




private:
	static MYSQL* connections;
	static MYSQL_RES* sql_result;
	static MYSQL_ROW sql_row;
	
	MYSQL mysql;
	
};

