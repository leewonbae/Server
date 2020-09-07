#pragma once
#include "Resource.h"
class cThread
{
public:
	cThread();
	~cThread();

	void MakeThread();
	virtual void Workerthread() = 0;
private:
	SYSTEM_INFO mSI;
};

