#pragma once
#include "Resource.h"
class cAcceptor
{
public:
	cAcceptor();
	~cAcceptor();
	SOCKET getlistensock() { return mLsock; }
	
	void InitServer();
	

private:
	SOCKET mLsock;
};

