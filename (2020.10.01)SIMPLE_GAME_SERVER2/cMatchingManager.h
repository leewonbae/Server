#pragma once
#include "cCriticalSection.h"
#include "cLog.h"
#include "packet.h"
#include "cUser.h"
#include <list>
class cMatchingManager
{
public:
	cMatchingManager();
	~cMatchingManager();

	void Matching_Parsing(PACKET_HEAD* _packet, cUser* _user);
	void Matching(PACKET_HEAD* _packet, cUser* _user);
	void CancleMatching(PACKET_HEAD* _packet, cUser* _user);
	void ShowWaitingCount();
private:
	cCriticalSection mCS_Match;
	list<cUser*> mWaitList;
	int mWaitingUserCount;

};

