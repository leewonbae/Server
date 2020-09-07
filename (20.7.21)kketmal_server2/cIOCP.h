#pragma once


#include "resource.h"
 


class cIOCP
{
public:
	cIOCP();
	~cIOCP();
	
	void	InitServer();
	void	MakeThread();
	void	ServerAccept();
	void	MSG_SEND(SOCKETINFO* _sInfo, char* _data);
	virtual void Switch_msg(int _msg_number, SOCKETINFO* _sinfo)=0;
	void	WOKERTHREAD();
private:
	SOCKET m_ListenSock;
	HANDLE m_hcp;
	SEND_ROOMINFO m_sendinfo;
	CRITICAL_SECTION cs;
};

