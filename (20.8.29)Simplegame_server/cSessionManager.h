#pragma once
#include "Resource.h"
#include "cSession.h"
#include "Packet.h"
class cSessionManager
{
public: 
	cSessionManager();
	~cSessionManager();

	void InputSession(cSession* _session, SOCKET _sock);
	void DelteSession(int _key);
	void ShowCount();
	void SessionParsing(int _key,PACKET_HEAD* _recvpacket);
private:
	cSession* mSessionArray[20] = { NULL, };
	int mSessionCount;
};

