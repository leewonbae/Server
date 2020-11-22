#pragma once
#include "cServer.h"
#include "cUserManager.h"
class cWorkerThread : public cServer
{
public:
	cWorkerThread();
	~cWorkerThread();

	void MakeThread();
	void WorkerThread();
	void RecvDataParsing(OVERDATA* _overdata, cUser* _user);
	void SendDataParsing(OVERDATA* _overdata, cUser* _user);


private:
	cUserManager mUserManager;
	cRoomManager mRoomManager;
};

