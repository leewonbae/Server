#pragma once
#include "Resource.h"
#include "Packet.h"
#include "Log.h"
class cSession
{
public:
	cSession();
	~cSession();
	void Setsock(SOCKET _sock);
	void SetKey(int _key);
	void SetUser(bool _checkuser);
	void Onrecv();
	void Onsend(void* _data,int _size);

	int getKey();
	bool getUsercheck();
	virtual void Parsing(PACKET_HEAD* _phead) = 0;
private:
	OVERDATA mOver;
	SOCKET mClientsock;
	bool mUsercheck;
	int mKey;
};

