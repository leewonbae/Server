#pragma once
#include "Resource.h"
#include "cServer.h"

class cThread : public cServer
{
public:
	cThread();
	~cThread();
	void MakeThread();
	void WorkerThread();

	 
private:
};

