#pragma once
#include "resource.h"
#include "cDatabase.h"
class cSession
{
public:
	cSession();
	~cSession();

	void OnRecv();
	void OnSend(int _packet_cmd, char* _send_data);
	virtual void Parsing(OVERDATA* _over)=0;

	void SetConnect(int _connect);
	void SetSock(SOCKET _sock);
	void SetAddr(SOCKADDR_IN _sockaddr);
	
	int getfleg();
	
private:
	OVERDATA mOverData;
	SOCKET mClientsock;
	SOCKADDR_IN mClientaddr;
	
	int mConnect;
	int mWorkFleg;
};

