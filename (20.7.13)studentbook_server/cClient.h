#pragma once
#include "resource.h"
class cClient
{
public:
	cClient();
	~cClient();

	void setSock(SOCKET _sock);
	void setAddr(SOCKADDR_IN _sockaddr);
	void setWorkfleg(int _fleg);
	void ShowIP_PORT();

	int getWorkfleg();
	void OnRecv();
	void OnSend(int _mCmd,char* _inputdata);
	virtual void Parsing(OVERDATA* _over) = 0;
private:
	OVERDATA mOver;
	SOCKET mSock;
	SOCKADDR_IN mAddr;
	int mWorkfleg;
};

