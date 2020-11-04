#pragma once
#include "Resource.h"
class cAcceptor
{
public:
	cAcceptor();
	~cAcceptor();
	void InitServer();
	SOCKET AcceptClient();
private:
	SOCKET mListenSock;
};

