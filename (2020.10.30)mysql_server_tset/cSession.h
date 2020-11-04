#pragma once
#include "Resource.h"
#include "Packet.h"
class cSession
{
public:
	cSession();
	~cSession();
	void SetSock(SOCKET _socket);
	void SetUser(bool _check);
	void SetKey(int _key);
	
	
	bool getUserCheck();
	int getKey();
	
	void OnRecv();
	void Onsend(void* _packet, int _packetsize);
	
	virtual void Parsing(PACKET_HEAD* _phead) = 0;
private:
	OVERDATA mOverdata;
	SOCKET mSock;
	bool mUserCheck;
	int mKey;
};

