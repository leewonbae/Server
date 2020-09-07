#pragma once
#include "Resource.h"
#include "cSession.h"
class cCPhanle
{
public:
	cCPhanle();
	~cCPhanle();
	void InitHandle();
	void InputClient(SOCKET _sock, cSession* _session);
	HANDLE getHandle();
private:
	HANDLE mHCP;
};

