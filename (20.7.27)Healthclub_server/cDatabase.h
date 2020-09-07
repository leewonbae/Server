#pragma once
#include "resource.h"



class cDatabase
{

public :
	cDatabase();
	~cDatabase();

	void InputNewUser(PACKET_USERDATA* _puser);
	bool CompareUser(PACKET_USERDATA* _puser);
	void ShowUserData();
	void InputNotice(PAKCET_NOTICE* _pnotice);
	void InputData(PAKCET_NOTICE* _pnotice);

	int getNoticeCount();
	int getUserCount();
	int getDataCount();

	NOTICE_NODE* getNotice();
	NOTICE_NODE* getData();
private:
	NODE* mNodeHead;
	NODE* mNodeTail;

	NOTICE_NODE* mNoticeHead;
	NOTICE_NODE* mNoticeTail;

	NOTICE_NODE* mDataHead;
	NOTICE_NODE* mDataTail;

	int mUsercount;
	int mNoticecount;
	int mDatacount;

};

