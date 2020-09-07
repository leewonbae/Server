#include "cControler.h"
cControler::cControler()
{
	cLog::Server_print(__FUNCTION__, " ");
	mHCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	mInitserver.Init();
	SetSOCK();
}
cControler::~cControler()
{
	closesocket(mListensock);
	WSACleanup();
}
void cControler::SetSOCK()
{
	mListensock = mInitserver.getSock();
	CreateIoCompletionPort((HANDLE)mListensock, mHCP, 0, 0 );
}
void cControler::Playserver()
{
	SOCKET clientsock;
	while (1)
	{
		clientsock = mInitserver.Acceptor();
		
		cUser* newuser = new cUser;
		newuser->Setsock(clientsock);
		if (mSManager.InputSession(newuser))
		{
			cLog::Server_print(__FUNCTION__, " "); 
			CreateIoCompletionPort((HANDLE)clientsock, mHCP, (ULONG_PTR)newuser, 0);
		}
		
		 
	}
}
void cControler::DataAnalysis(PACKET_HEAD* _recvpacket, cSession* _session)
{
	cLog::Server_print(__FUNCTION__, " ");
	bool usercheck = _session->getUsercheck();
	
	int key = _session->getKey();
	cLog::Session_print(key);
	if (_recvpacket->mDB_Necessity == true)
	{
		mDatabase.Db_Parsing((cUser*)_session,_recvpacket);
	}
	if (_recvpacket->mPacket_msg == MSG_LOGIN_OK || usercheck == true)
	{
		if (_recvpacket->mPacket_msg == MSG_LOGIN_OK)
		{
			mUManager.InputUser((cUser*)_session, key);
			
		}
		mUManager.UserParsing(key,_recvpacket);
		 
		
	}
	else
	{
		mSManager.SessionParsing(key, _recvpacket);
	}
}
void cControler::OutSession(cSession* _session)
{
	int key = _session->getKey();
	cLog::Session_print(key);
	if (_session->getUsercheck())
	{
		mDatabase.DeleteMenu(key);
		mUManager.DeleteUser(key);
	}

	mSManager.DelteSession(key);
	cLog::Server_print(__FUNCTION__, " ");
}
HANDLE cControler:: getHcp()
{
	return mHCP;
}