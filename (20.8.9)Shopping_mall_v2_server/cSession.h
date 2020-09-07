#pragma once
#include "resource.h"
class cSession
{
public:
	cSession();
	~cSession();
	void Setsock(SOCKET _sock);
	void SetAddr(SOCKADDR_IN _addr);
	void OnSend(int _cmd, char* _databuf);
	void Onrecv();
	virtual void Parsing(OVERLAPPED_DATA* _over) = 0;
private:
	OVERLAPPED_DATA mOver_data;
	SOCKET mSessionSOCK;
	SOCKADDR_IN mSessionAddr;


};

