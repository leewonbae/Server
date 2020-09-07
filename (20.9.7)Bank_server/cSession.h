#pragma once
#include "Resource.h"
#include "Packet.h"
class cSession
{
public:
	cSession();
	~cSession();

	void Setkey(int _key);
	void SetSock(SOCKET _sock);
	void SetUserCheck(bool _usercheck);

	void Onrecv();
	void Onsend(void* _packet, int _packetsize);

	virtual void Paring(PACKET_HEAD* _recvpacket) = 0;

	 
	int getKey();
	bool getUserCheck();

private:
	OVERDATA mOver;
	SOCKET mSOCK;
	bool mUsercheck;
	int mKey;
};

