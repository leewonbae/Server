#pragma once
#include "Resource.h"

class cAcceptor
{
public:
	cAcceptor();
	~cAcceptor();

	void InitAcceptor();
	SOCKET getClientSock();
private:
	SOCKET mListensock;
};

