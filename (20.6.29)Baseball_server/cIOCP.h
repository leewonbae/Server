#pragma once
#include "resource.h"


class cIOCP
{
public:
	cIOCP();
	~cIOCP();
	void IOCP_controller();
	bool Init_server();
	bool MakeThread();
	void Workerthread();
	virtual void Parsing(SOCKETINFO* _ptr) = 0;
	void PacketSend(SOCKETINFO* _ptr);
	//RECV
	// PARSING
	// SEND
	//THREAD


private:
	SOCKET listen_sock;
	HANDLE hcp;
};

