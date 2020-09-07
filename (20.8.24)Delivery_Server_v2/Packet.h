#pragma once
#include "resource.h"

 
class PACKET_HEAD
{
public:
	int mPacket_cmd;
	int mPacket_msg;
	int mPacket_size;
	bool mDB_Necessity;
};

class PACKET_LOGIN : public PACKET_HEAD {

public:
	PACKET_LOGIN()
	{
		mPacket_cmd = PROTO_LOGIN_REQ;
		mPacket_msg = 0;
		mPacket_size = sizeof(PACKET_LOGIN);
		mDB_Necessity = true;
		
		memset(ID, 0, sizeof(ID));
		PASSWORD = 0;
		
	}

	char ID[20];
	int PASSWORD;
	
};
class PACKET_NEWUSER : public PACKET_HEAD {

public:
	PACKET_NEWUSER()
	{
		mPacket_cmd = PROTO_NEWUSER_REQ;
		mPacket_msg = 0;
		mPacket_size = sizeof(PACKET_NEWUSER);
		mDB_Necessity = true;
		
		memset(ID, 0, sizeof(ID));
		memset(MENU, 0, sizeof(MENU));
		PASSWORD = 0;
		DB_TYPE = 0;
	}

	char ID[20];
	int PASSWORD;
	char MENU[10]; // 사장일때만 사용 
	int DB_TYPE; // 유저인지, 사장인지 기분
};
class PACKET_MENULIST : public PACKET_HEAD {

public:
	PACKET_MENULIST()
	{
		mPacket_cmd = PROTO_MENULIST_REQ;
		mPacket_msg = 0;
		mPacket_size = sizeof(PACKET_MENULIST);
		mDB_Necessity = true;
		mMenucount = 0;
	}
	int mMenucount;
	char mMenulist[20][20];
	 
};
class PACKET_ORDER : public PACKET_HEAD {

public:
	PACKET_ORDER()
	{
		mPacket_cmd = PROTO_USER_ORDER_REQ;
		mPacket_msg = 0;
		mPacket_size = sizeof(PACKET_ORDER);
		mDB_Necessity = true;
		mOrdercount = 0;
		mOrderMaster = 0;
	}
	int mOrdercount;
	int mOrderMaster;
	int mMasterkey;
};

