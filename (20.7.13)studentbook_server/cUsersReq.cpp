#include "cUsersReq.h"
cUsers::cUsers()
{
	mFmap.insert(map<int, ptr>::value_type(MSG_MAKE_STUDENTBOOK_REQ, &cUsers::MSG_SAVE_NEW_STUDENTBOOK));
	mFmap.insert(map<int, ptr>::value_type(MSG_UPDATA_DATA_REQ, &cUsers::MSG_UPDATA_DATA));
	mFmap.insert(map<int, ptr>::value_type(MSG_DOWNLOAD_REQ, &cUsers::MSG_DOWNLOAD));



}
cUsers::~cUsers()
{

}
void cUsers::setDatabase(cDatabase* _database)
{
	mDataBase = _database;
}
void cUsers::Parsing(OVERDATA* _over)
{
	ShowIP_PORT();
	ptr	Temp;
	PACKET_HEAD phead;
	memset(&phead, 0, sizeof(PACKET_HEAD));
	memcpy(&phead, _over->mDatabuf, sizeof(PACKET_HEAD));
	mIter = mFmap.find(phead.mCmd);
	 
	 
	Temp = mIter->second;
	(this->*Temp)(_over);
	 
}

void cUsers::MSG_SAVE_NEW_STUDENTBOOK(OVERDATA* _over)
{
	cout << "make studentbook" << endl;
	PACKET_STUDENTBOOK pbook;
	memset(&pbook, 0, sizeof(PACKET_STUDENTBOOK));
	memcpy(&pbook, _over->mDatabuf + sizeof(PACKET_HEAD), sizeof(PACKET_STUDENTBOOK));
	
	cout <<"이름" <<pbook.mFileName << endl;
	cout <<"사이즈"<< pbook.mFilesize << endl;
	mDataBase->SaveFile(pbook);

	OnSend(MSG_MAKE_STUDENTBOOK_REQ, mDatabuf);
}
void cUsers::MSG_UPDATA_DATA(OVERDATA* _over)
{
	cout << "updata data" << endl;
}
void cUsers::MSG_DOWNLOAD(OVERDATA* _over)
{
	cout << "download req" << endl;
}