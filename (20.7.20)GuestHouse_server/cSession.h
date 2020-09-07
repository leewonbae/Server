#pragma once
#include "resource.h"
class cSession
{
public:
	cSession();
	~cSession();
	void setSock(SOCKET _sock);
	void setSockAddr(SOCKADDR_IN _sockaddr);
	int getFleg();

	void OnRecv();
	void OnSend(int _packetcmd, char* _data);
	virtual void Parsing(OVERDATA* _over) = 0;
private:
	OVERDATA mOverdata;
	
	SOCKET mClientSock;
	SOCKADDR_IN mClientaddr;
	int mWorkfleg;
};

