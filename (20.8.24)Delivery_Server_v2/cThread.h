#pragma once
#include "Resource.h"
#include "cControler.h"
#include "cUser.h"
#include "Log.h"
class cThread : public cControler
{
public:
	cThread();
	~cThread();
	void Makethread();
	void Workerthread();
	
private:
	 
};

