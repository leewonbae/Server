#pragma once

#include "cIOCP.h"
#include "resource.h"
#include "cDatabase.h"

class cUser : public cIOCP
{
public:
	cUser();
	~cUser();

	typedef void (cUser:: *fp)(SOCKETINFO* _ptr);
	virtual void Parsing(SOCKETINFO* _ptr);

	

	
private:
	void MSG_NEW_USER(SOCKETINFO* _ptr);
	void MSG_CHECK_USER(SOCKETINFO* _ptr);
	void MSG_CHECK_VERSION(SOCKETINFO* _ptr);
	void MSG_NEW_VERSION(SOCKETINFO* _ptr);
	void MSG_PAYMENT(SOCKETINFO* _ptr);
	void MSG_RECHARGE(SOCKETINFO* _ptr);
	FILE* mTextfile;
	cDatabase m_cData;
	map<int, fp>			mFmap;
	map<int, fp>::iterator	iter;
	 
};

