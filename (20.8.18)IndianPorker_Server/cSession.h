#pragma once
#include "resource.h"
class cSession
{
public:
	cSession();
	~cSession();

	void SetSOCK(SOCKET _sock);
	void SetKEY(int _hashkey);
	void Onrecv();
	void Onsend(int _packetcmd, char* _databuf);
	
	int getKey();
	virtual void Parsing(OVERDATA* _over) = 0;
private:
	OVERDATA mOver;
	int mHashKey;
	SOCKET mSock;
};

