#pragma once
enum PROTOCOL {
	PROTOCOL_HEAD = 0,

	PTC_LOGIN_REQ,
	PTC_NEWUSER_REQ,
	PTC_INPUT_MONEY_REQ,
	PTC_OUTPUT_MONEY_REQ,
	PTC_TRANSFER_MONEY_REQ,



};
enum SEND_MSG {
	MSG_HEAD,


	MSG_LOGIN_OK,
	MSG_LOGIN_FAIL,

	MSG_NEWUSER_OK,
	MSG_NEWUSER_FAIL,

	MSG_INPUT_OK,
	MSG_INPUT_FAIL,

	MSG_OUTPUT_OK,
	MSG_OUTPUT_FAIL,

	MSG_TRANSFER_OK,
	MSG_TRANSFER_FAIL,


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
		mPacket_MSG = 0;
	}
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
		mPacket_MSG = 0;
	}
	char mName[10];
	int mPassword;
	int mTransferNum;

};

class PACKET_INPUT : public PACKET_HEAD
{
public:
	PACKET_INPUT()
	{
		mCmd = PTC_INPUT_MONEY_REQ;
		mPacket_size = sizeof(PACKET_INPUT);
		mPacket_MSG = 0;
	}
	int mInputMoney;

};
class PACKET_OUTPUT : public PACKET_HEAD
{
public:
	PACKET_OUTPUT()
	{
		mCmd = PTC_OUTPUT_MONEY_REQ;
		mPacket_size = sizeof(PACKET_OUTPUT);
		mPacket_MSG = 0;
	}
	int mOutputMoney;

};
class PACKET_TRANSFER : public PACKET_HEAD
{
public:
	PACKET_TRANSFER()
	{
		mCmd = PTC_TRANSFER_MONEY_REQ;
		mPacket_size = sizeof(PACKET_TRANSFER);
		mPacket_MSG = 0;
	}
	int mTo_TransferNum;
	int mSendMoney;

};