#pragma once
#include "Resource.h"
#include "cUser.h"
#include "cCriticalSection.h"
class cSessionManager
{
public:
	cSessionManager();
	~cSessionManager();

 
	cSession* getNewSession();
	void OutSession(cSession* _session);
private:
	cCriticalSection mCS_SM;
	vector<cSession*> mSessionArray;
	vector<cSession*>::iterator mSessionArrayIter;
	int mKeyCount;
	 
};

