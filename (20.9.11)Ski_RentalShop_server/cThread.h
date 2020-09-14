#pragma once
#include "Resource.h"
#include "cServer.h"
#include "cSession.h"

class cThread
{
public:
	cThread();
	~cThread();

	void SetServer(cServer* _serverptr);
	void MakeThread();
	void WorkerThread();
private:
	cServer* mServerPtr;
};

