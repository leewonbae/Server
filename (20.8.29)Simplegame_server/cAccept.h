#pragma once
#include "Resource.h"
class cAccept
{
public:
	cAccept();
	~cAccept();

	void InitServer();
	SOCKET Accept();

private:
	SOCKET mListensock;
};

