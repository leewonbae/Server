#pragma once
#include "resource.h"
#include "cSession.h"
struct Session_NODE {
	cSession* mSessionNode;
	Session_NODE* mNextNode;
};
class cSessionManager
{
public:
	cSessionManager();
	~cSessionManager();
	void InputNewSession(cSession* _session, SOCKET _sock, SOCKADDR_IN _sockaddr);
	void DeleteSession(cSession* _session);
private:
	int mSessionCount;
	Session_NODE* mHeadNode;
	Session_NODE* mTailNode;
};

