#pragma once
#include "Resource.h"
#include "packet.h"

class cSession
{
public:
	cSession();
	~cSession();
	int getkey();
	bool getMode();

	void SetSock(SOCKET _sock);
	void SetKey(int _key);
	void SetUserMode(bool _check);
	void OnRecv();
	void OnSend(void* _packet, int packet_size);

	virtual void Parsing(PACKET_HEAD* _phead) = 0;
private:
	bool mUserMode;
	OVERDATA mOver;
	SOCKET mSocket;
	int mSessionKey;

};

