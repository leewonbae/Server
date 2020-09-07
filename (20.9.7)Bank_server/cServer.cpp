#include "cServer.h"
DWORD WINAPI SwitchThread(LPVOID arg)
{
	cServer* server = (cServer*)arg;
	server->WorkerThread();
	return 0;

}
cServer::cServer()
{

}
cServer::~cServer()
{

}
 
void cServer::MakeThread()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	for (int i = 0;i < (int)si.dwNumberOfProcessors;i++)
	{
		CreateThread(NULL, 0, SwitchThread, this, 0, NULL);
	}
}


void cServer::AcceptClient()
{
	mSessionManager.SetDataBase(&mDataBase);
	mUserManager.SetDataBase(&mDataBase);
	while (1)
	{
		
		SOCKET clientsock = mAcceptor.getClientSock();

		cout << "클라이언트 접속" << endl;
		cUser* newsession = new cUser;
		mIOCPhandle.SetHandle(clientsock, (cSession*)newsession);
		mSessionManager.InputSession(clientsock, (cSession*)newsession);
	
	
	}
}
 
void cServer::DataAnalysis(PACKET_HEAD* _recvpacket,cSession* _session)
{
	cout << "DataAnalysis" << endl;
	bool usercheck = _session->getUserCheck();
	int key = _session->getKey();
	
	
	if (usercheck == false)
	{
		mSessionManager.SessionParsing(key, _recvpacket);
	}
	else
	{
		mUserManager.UserParsing(key, _recvpacket);
	}
}

void cServer::WorkerThread()
{
 
	int retval;
	DWORD transbytes;
	cSession* session_ptr;
	OVERDATA* over_ptr;
	
	
	while (1)
	{
		retval = GetQueuedCompletionStatus(mIOCPhandle.getHandle(), &transbytes, (LPDWORD)&session_ptr, (LPOVERLAPPED*)&over_ptr, INFINITE);
		int session_key = session_ptr->getKey();
		
		if (retval == 0 || transbytes == 0)
		{
			cout << "클라이언트 종료" << endl;
			if (session_ptr->getUserCheck() == true)
			{
				mUserManager.DeleteUser(session_key);
			}
			
			mSessionManager.DeleteSession(session_key);
			continue;
		}


		PACKET_HEAD* packet = (PACKET_HEAD*)over_ptr->mDatabuf;
		 

		switch (over_ptr->mWorkFleg)
		{
		case WORK_FLEG_RECV:
			DataAnalysis(packet, session_ptr);
			break;


		case WORK_FLEG_SEND:
			if (packet->mPacket_MSG == MSG_LOGIN_OK)
			{
				mUserManager.InputUser((cUser*)session_ptr);
			}
			session_ptr->Onrecv();
			break;
		}
		
	
	
	
	}



}