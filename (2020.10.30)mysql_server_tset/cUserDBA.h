#pragma once
#include "Resource.h"
#include "Packet.h"
#include "cMySQL.h"
#include "cSession.h"
#include "cCriticalSection.h"
class cUserDBA
{
public:
	cUserDBA();
	~cUserDBA();

	void InputUserInfo(PACKET_HEAD* _phead,cSession* _session);
	void CheckUserLogin(PACKET_HEAD* _phead, cSession* _session);

private:
	cCriticalSection mCS_userDba;
};

