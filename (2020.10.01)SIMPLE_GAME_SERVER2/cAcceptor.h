#pragma once
#include "Resource.h"
class cAcceptor
{
public:
	cAcceptor();
	~cAcceptor();

	void InitServer();
	SOCKET Accept_client();
private:
	SOCKET mListensock;
	 
};

