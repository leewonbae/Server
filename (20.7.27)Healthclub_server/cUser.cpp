#include "cUser.h"
cUser::cUser()
{ 
	mFmap.insert(map<int, fp>::value_type(MSG_NEWUSER_REQ, &cUser::MSG_NEWUSER));
	mFmap.insert(map<int, fp>::value_type(MSG_LOGIN_REQ, &cUser::MSG_LOGIN));
	mFmap.insert(map<int, fp>::value_type(MSG_NOTICE_CHECK_REQ, &cUser::MSG_NOTICE_CHECK));
	mFmap.insert(map<int, fp>::value_type(MSG_DATA_REQ, &cUser::MSG_DATA));
	mFmap.insert(map<int, fp>::value_type(MSG_NOTICE_SEND_REQ, &cUser::MSG_NOTICE_SEND));
	mFmap.insert(map<int, fp>::value_type(MSG_DATA_SEND_REQ, &cUser::MSG_DATA_SEND));
}
cUser::~cUser()
{

}
void cUser::SetDatabase(cDatabase* _database)
{
	mDatabase = _database;
}
void cUser::Parsing(OVERDATA* _over)
{
	PACKET_HEAD phead;
	memset(&phead, 0, sizeof(PACKET_HEAD));
	memcpy(&phead, _over->mDatabuf, sizeof(PACKET_HEAD));
	 

	fp	Temp;
	mMapIteratior = mFmap.find(phead.mCmd);


	Temp = mMapIteratior->second;
	(this->*Temp)(_over);
}


void cUser::MSG_NEWUSER(OVERDATA* over)
{  
	PACKET_USERDATA puser;
	memset(&puser, 0, sizeof(PACKET_USERDATA));
	memcpy(&puser, over->mDatabuf+sizeof(PACKET_HEAD), sizeof(PACKET_USERDATA));
	mDatabase->InputNewUser(&puser);
	OnSend(MSG_NEWUSER_REQ, mSendbuf);
}

void cUser::MSG_LOGIN(OVERDATA* over)
{
	 
	PACKET_USERDATA puser;
	memset(&puser, 0, sizeof(PACKET_USERDATA));
	memcpy(&puser, over->mDatabuf+sizeof(PACKET_HEAD), sizeof(PACKET_USERDATA));
	
	PACKET_CHECKUSER pcheck;
	
	pcheck.mCheckUser = mDatabase->CompareUser(&puser);
	memcpy(mSendbuf + sizeof(PACKET_HEAD), &pcheck, sizeof(PACKET_USERDATA));
	OnSend(MSG_LOGIN_REQ, mSendbuf);
}



void cUser::MSG_NOTICE_CHECK(OVERDATA* over)
{
	PACKET_NOTICECOUNT pncount;
	 
	pncount.mNoticecount = mDatabase->getNoticeCount();
	memcpy(mSendbuf + sizeof(PACKET_HEAD), &pncount, sizeof(PACKET_NOTICECOUNT));
	OnSend(MSG_NOTICE_CHECK_REQ, mSendbuf);
}


void cUser::MSG_DATA(OVERDATA* over)
{
	PACKET_NOTICECOUNT pncount;

	pncount.mNoticecount = mDatabase->getDataCount();
	memcpy(mSendbuf + sizeof(PACKET_HEAD), &pncount, sizeof(PACKET_NOTICECOUNT));
	OnSend(MSG_DATA_REQ, mSendbuf);
}


void cUser::MSG_NOTICE_SEND(OVERDATA* over)
{
	NOTICE_NODE* cur = mDatabase->getNotice();
	while (cur!=NULL)
	{
		memcpy(mSendbuf + sizeof(PACKET_HEAD), &cur->mNoticedata, sizeof(PAKCET_NOTICE));
		OnSend(MSG_NOTICE_SEND_REQ, mSendbuf);
		cur = cur->mNextnode;
	}
	OnRecv();
}
void cUser::MSG_DATA_SEND(OVERDATA* over)
{
	NOTICE_NODE* cur = mDatabase->getData();
	while (cur != NULL)
	{
		memcpy(mSendbuf + sizeof(PACKET_HEAD), &cur->mNoticedata, sizeof(PAKCET_NOTICE));
		OnSend(MSG_DATA_SEND_REQ, mSendbuf);
		cur = cur->mNextnode;
	}
	OnRecv();
}