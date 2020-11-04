#include "cServer.h"
cServer::cServer()
{
	mAcceptor.InitServer();
	mIOCPhandle.MakeHcp();
}
cServer::~cServer()
{

}
HANDLE cServer::getHandle()
{
	return mIOCPhandle.getHcp();
}
void cServer::Manager_Parsing(cSession* _session, PACKET_HEAD* _phead)
{
	bool usercheck = _session->getUserCheck();
	cout << "SERVER MANAGER PARSING START" << endl;
	if (usercheck == true)
	{
		// ���� �Ŵ�����
		mUserManager.UserManager_Parsing((cUser*)_session, _phead);
	}
	else
	{
		// session manager
		mSessionManager.SessionManager_Parsing(_session, _phead);
		if (_phead->mMsg == MSG_LOGIN_OK)
		{
			_session->SetKey(true);
			mUserManager.InputUser((cUser*)_session);
		}
	}

	_session->Parsing(_phead);

}
void cServer::ClientOut(cSession* _session)
{
	if (_session->getUserCheck() == true)
	{
		mUserManager.OutUser();
	}
	
	mSessionManager.OutSession(_session);
}
void cServer::PlayAccept()
{
	
	while (1)
	{
		SOCKET clientsock = mAcceptor.AcceptClient();
		cUser* newSession = new cUser;

		// max �ʰ� �� ��� fasle;
		// �ƴϸ� true;
		if (mSessionManager.InputSession(newSession) == true)
		{
			cout << "Ŭ���̾�Ʈ ����" << endl;
			mIOCPhandle.SetHCP(newSession, clientsock);
			newSession->SetSock(clientsock);
			newSession->OnRecv();
		}
		else
		{
			delete newSession;
		}
		
	}
}
