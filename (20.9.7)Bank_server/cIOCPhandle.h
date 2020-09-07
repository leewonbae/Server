#pragma once
#include "Resource.h"
#include "cSession.h"

class cIOCPhandle
{
public:
	cIOCPhandle();
	~cIOCPhandle();

	void InitHandle();
	void SetHandle(SOCKET _sock, cSession* _session);
	HANDLE getHandle();
private:
	HANDLE mIOCPhandle;

};

