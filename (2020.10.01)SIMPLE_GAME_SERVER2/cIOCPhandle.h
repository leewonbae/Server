#pragma once
#include "Resource.h"
#include "cSession.h"
class cIOCPhandle
{
public :
	cIOCPhandle();
	~cIOCPhandle();

	void MakeHandle();
	void Set_CP_SOCKET(SOCKET _sock, cSession* _ptr);
	HANDLE getIOCPhandle();
private:
	HANDLE mHcp;
};

