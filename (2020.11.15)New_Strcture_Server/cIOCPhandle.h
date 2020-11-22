#pragma once
#include "Resource.h"
#include "cSession.h"
class cIOCPhandle
{
public:
	cIOCPhandle();
	~cIOCPhandle();
	HANDLE getHCP() { return mHCP; }

	void InitHCP();
	void CreateHcpListenSOCK(SOCKET _listensock);
	void CreateHcpClientSOCK(SOCKET _clientsock, cSession* _session);

private:
	HANDLE mHCP;
};

