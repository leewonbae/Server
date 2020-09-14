#include "cServer.h"
cServer::cServer()
{

}
cServer::~cServer()
{

}

HANDLE cServer::getHandle()
{
	return mHandle.getHandle();
}
void cServer::ClientOut(cSession* _session)
{

	int key = _session->getKey();
	bool usercheck = _session->getUserCheck();


	if (usercheck == true)
	{
		mUserManager.DeleteUser(key);
	}

	mSessionManager.DeleteSession(key);

}

void cServer::SendUserManager(cUser* _user)
{
	mUserManager.InputUser(_user);
}
void cServer::PacketParsing(cSession* _session, PACKET_HEAD* _recvpacket)
{
	int key = _session->getKey();
	bool usercheck = _session->getUserCheck();


	if (usercheck == true)
	{
		mUserManager.UserParsing(key, _recvpacket);
	}
	else
	{
		mSessionManager.SessionParsing(key, _recvpacket);
	}
}
void cServer::ClientAccept()
{
	SOCKET clientsock;
	while (1)
	{
		
		clientsock = mAcceptor.getClientSock();
		cout << "클라이언트 접속" << endl;
		cUser* newsession = new cUser;
		
		mHandle.SetHandle(clientsock, newsession);

		mSessionManager.InputSession(clientsock, newsession);

	}
	
}
