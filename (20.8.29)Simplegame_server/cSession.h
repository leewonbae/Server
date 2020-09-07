#pragma once
#include "Resource.h"
#include "Packet.h"
class cSession
{
public:
	cSession();
	~cSession();

	void SetSock(SOCKET _sock);
	void SetKey(int _key);
	void ChangeUserMode(bool _modechange);
	void Onrecv();
	void Onsend(void* _data, int _size);

	int getKey();
	bool getModeCheck();
	virtual void Parsing(PACKET_HEAD* _phead) = 0;

private:
	OVERDATA mOver;
	SOCKET mSocket;
	bool mUsermode;
	int mKey;
};

