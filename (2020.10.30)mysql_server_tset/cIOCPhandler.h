#pragma once
#include "Resource.h"
#include "cSession.h"
class cIOCPhandler
{
public:
	cIOCPhandler();
	~cIOCPhandler();

	void MakeHcp();
	void SetHCP(cSession* _sessionPtr, SOCKET _clientsock);
	HANDLE getHcp();
private:
	HANDLE mHCP;
};

