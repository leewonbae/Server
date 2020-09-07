#pragma once
#include "resource.h"
#include "cClient.h"
#include "cDatabase.h"
class cUsers : public cClient
{
public:
	cUsers();
	~cUsers();
	typedef void (cUsers:: *ptr)(OVERDATA* _over);
	virtual void Parsing(OVERDATA* _over);
	void setDatabase(cDatabase* _database);
private:
	
	void	MSG_SAVE_NEW_STUDENTBOOK(OVERDATA* _over);
	void	MSG_UPDATA_DATA(OVERDATA* _over);
	void	MSG_DOWNLOAD(OVERDATA* _over);

	char mDatabuf[BUFFER_SIZE];
	cDatabase* mDataBase;
	map<int, ptr> mFmap;
	map<int, ptr>::iterator mIter;
};

