#pragma once
#include "resource.h"
#include "cSession.h"
#include "cUserDB.h"
class cSessionManager
{
public:
	cSessionManager();
	~cSessionManager();
	bool InputSession(cSession* _session);
	bool DeleteSession(int _key);
	void Setrecv(int _key);
	void ParsingSession(int _key, OVERDATA* _over);
private:
	int mSessionCount;
	int mKeycount;
	cSession* mSessionList[20];
	bool mListCheck[20] = { false, };
};

