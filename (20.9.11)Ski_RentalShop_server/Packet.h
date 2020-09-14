#pragma once
enum PROTOCOL {
	PROTOCOL_HEAD = 0,

	PTC_LOGIN_REQ,
	PTC_NEWUSER_REQ,
	 
	PTC_EQUIPMENT_LIST_REQ,
	PTC_RETAL_REQ,
	PTC_RETURN_REQ,


};
enum SEND_MSG {
	MSG_HEAD,


	MSG_LOGIN_OK,
	MSG_LOGIN_FAIL,

	MSG_NEWUSER_OK,
	MSG_NEWUSER_FAIL,

	MSG_RENTAIL_OK,
	MSG_RENTAIL_FAIL,

	MSG_RETURN_OK,
	MSG_RETURN_FAIL,
	 
	MSG_LIST_OK,
	MSG_LIST_FAIL,

};

class PACKET_HEAD {
public:
	int mCmd;
	int mPacket_size;
	int mPacket_MSG;


};
class PACKET_LOGIN : public PACKET_HEAD
{
public:
	PACKET_LOGIN()
	{
		mCmd = PTC_LOGIN_REQ;
		mPacket_size = sizeof(PACKET_LOGIN);
		mPacket_MSG = MSG_LOGIN_FAIL;
	}
	RESERVATION mReserv;
	char mName[10];
	int mPassword;
};

class PACKET_NEWUSER : public PACKET_HEAD
{
public:
	PACKET_NEWUSER()
	{
		mCmd = PTC_NEWUSER_REQ;
		mPacket_size = sizeof(PACKET_NEWUSER);
		mPacket_MSG = MSG_NEWUSER_FAIL;
	}
	char mName[10];
	int mPassword;
	 

};

class PACKET_LIST : public PACKET_HEAD
{
public:
	PACKET_LIST()
	{
		mCmd = PTC_EQUIPMENT_LIST_REQ;
		mPacket_size = sizeof(PACKET_LIST);
		mPacket_MSG = MSG_RETURN_FAIL;
	}

	int mSKIcount;
	int mBOARDcount;
	int mCLOTHINGcount;

};

class PACKET_RENTAL : public PACKET_HEAD
{
public:
	PACKET_RENTAL()
	{
		mCmd = PTC_RETAL_REQ;
		mPacket_size = sizeof(PACKET_RENTAL);
		mPacket_MSG = MSG_RENTAIL_FAIL;
	}
 
	int mSKIcount;
	int mBOARDcount;
	int mCLOTHINGcount;
};


class PACKET_RETURN : public PACKET_HEAD
{
public:
	PACKET_RETURN()
	{
		mCmd = PTC_RETURN_REQ;
		mPacket_size = sizeof(PACKET_RETURN);
		mPacket_MSG = MSG_LIST_FAIL;
	}

	int mSKIcount;
	int mBOARDcount;
	int mCLOTHINGcount;

};