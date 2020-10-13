#include "cServer.h"
cServer::cServer()
{
	mAcceptor.InitServer();
	mIOCPhandle.MakeHandle();
}
cServer::~cServer()
{
	WSACleanup();
}

void cServer::StartServer()
{
	
	while (1)
	{
		SOCKET clientsock = mAcceptor.Accept_client();
		cUser* newsession = new cUser;
		newsession->SetSock(clientsock);
		mIOCPhandle.Set_CP_SOCKET(clientsock, (cSession*)newsession);
		mSessionManager.InputSession(newsession);

		 
		cLog::Print_log("클라이언트 접속");

		newsession->OnRecv();
		// 클라이언트 접속
	}
}

void cServer::DataParsing(PACKET_HEAD* _phead, cSession* _ptr)
{
	//패킷에 따라 나눠주자 // 
	int packet_head = _phead->mCmd;
	cUser* temp;
	cLog::Print_log("DATA_PARSING");
	switch (packet_head)
	{
		// db 관리자
	case PTC_LOGIN_REQ:
		mUserDB.DB_Parsing(_phead, _ptr);
		if (_phead->mPacket_msg == MSG_LOGIN_OK)
		{
			mUserManager.InputUser((cUser*)_ptr);
			
		}
		break;
	case PTC_RESULT_SAVE_REQ:
		mUserDB.ChangeScroe(_phead, _ptr);
		temp = (cUser*)_ptr;
		temp->SetMatchingPartner(NULL);
		// 점수 반영
		break;
		// 매칭매니저
	case PTC_MATCHING_REQ:
		mMatchingManager.Matching_Parsing(_phead, (cUser*)_ptr);
		break;
	 
	}
	_ptr->Parsing( _phead);
}

void cServer::ClientOut(int _index)
{
	mServer_CS.LockCs();
	mSessionManager.DelteSession(_index);
	mUserManager.DeleteUser(_index);
	mServer_CS.UnLock();
}
HANDLE cServer::getHandle()
{
	
	return mIOCPhandle.getIOCPhandle();
}