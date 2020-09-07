#include "cUser.h"
cUser::cUser()
{
	mReservation = false;
	mFmap.insert(map<int, fp>::value_type(MSG_LOGIN_REQ, &cUser::MSG_LOGIN));
	mFmap.insert(map<int, fp>::value_type(MSG_ROOM_INFO, &cUser::MSG_ROOM));
	mFmap.insert(map<int, fp>::value_type(MSG_RESERVATION_INFO, &cUser::MSG_RESERVATION));
	mFmap.insert(map<int, fp>::value_type(MSG_ROOMCHATTING_REQ, &cUser::MSG_ROOMCHATTING));
}
cUser::~cUser()
{

}
void cUser::setDB(cDatabase* _db)
{
	mDatabase = _db;
}
void cUser::Parsing(OVERDATA* _over)
{
	
	PACKET_HEAD phead;
	memset(&phead, 0, sizeof(PACKET_HEAD));
	memcpy(&phead, _over->mDatabuf, sizeof(PACKET_HEAD));
	cout << "phead" << phead.mCmd << endl;
	 
	fp	Temp;
	mIter = mFmap.find(phead.mCmd);


	Temp = mIter->second;
	(this->*Temp)(_over);
}
void cUser::MSG_LOGIN(OVERDATA* _over)
{
	PACKET_LOGIN plogin;

	memcpy(&plogin,_over->mDatabuf + sizeof(PACKET_HEAD), sizeof(PACKET_LOGIN));
	memcpy(&mUserLogindata, &plogin, sizeof(PACKET_LOGIN));
	if (mDatabase->CheckReserv(mUserLogindata) == true)
	{
		plogin.password = LOGIN_RESERVATION_OK;
		
	}
	else 
	{
		plogin.password = LOGIN_RESERVATION_NO;
	}
	memcpy(mSendbuf + sizeof(PACKET_HEAD), &plogin, sizeof(PACKET_LOGIN));
	OnSend(MSG_LOGIN_REQ, mSendbuf);
}
void cUser::MSG_ROOM(OVERDATA* _over)
{
	PACKET_ROOMINFO proom;
	memcpy(proom.mUsercount, mDatabase->getroomuser(), sizeof(proom.mUsercount));
	memcpy(mSendbuf + sizeof(PACKET_HEAD), &proom, sizeof(PACKET_ROOMINFO));
	OnSend(MSG_ROOM_INFO, mSendbuf);
}
void cUser::MSG_RESERVATION(OVERDATA* _over)
{
	PACKET_RESERVATION preserv;
	memset(&preserv, 0, sizeof(PACKET_RESERVATION));
	memcpy(&preserv, _over->mDatabuf+sizeof(PACKET_HEAD), sizeof(PACKET_RESERVATION));
	mDatabase->InputData(mUserLogindata);
	mDatabase->ReservationRoom(preserv.mCoiceRoomNum, preserv.mReservUserCount, mUserLogindata);
	
	OnSend(MSG_RESERVATION_INFO, mSendbuf);
}
void cUser::MSG_ROOMCHATTING(OVERDATA* _over)
{
	PACKET_CHATTING pchat;
	memset(&pchat, 0, sizeof(PACKET_CHATTING));
	memcpy(&pchat, _over->mDatabuf + sizeof(PACKET_HEAD), sizeof(PACKET_CHATTING));
	
	mRoomNuber = mDatabase->getroomnumber(mUserLogindata);
	cout << mRoomNuber << " 방 에서 메세지가 도착했습니다. " << endl;
	cout << pchat.mChat << endl;
	
	OnSend(MSG_ROOMCHATTING_REQ, mSendbuf);
}