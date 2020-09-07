#include "cServer.h"
cServer::cServer()
{
	cout << "server 생성자" << endl;
}
cServer::~cServer()
{

}
void cServer::Workerthread()
{
	 
	int retval;
	DWORD transbytes;
	cSession* session_ptr;
	OVERDATA* over_ptr;
	while (1)
	{
		retval = GetQueuedCompletionStatus(mCPhandle.getHandle(), &transbytes, (LPDWORD)&session_ptr, (LPOVERLAPPED*)&over_ptr, INFINITE);
		
		if (retval == 0 || transbytes == 0)
		{
			cout << "클라이언트 종료" << endl;
			mSessionManager.DelteSession(session_ptr->getKey());
			continue;
		}
		PACKET_HEAD* recvpacket = (PACKET_HEAD*)over_ptr->mDatabuf;
	
		
		
		switch (over_ptr->mWork_fleg)
		{
		case WORK_FLEG_RECV:
			cout << "[[[[[[[[[[[[[[[recv]]]]]]]]]]]]]]]]]]]]]]" << endl;
			DataAnalysis(session_ptr, recvpacket);
			break;
		case WORK_FLEG_SEND:
			cout << "[[[[[[[[[[[[[[[[[[send]]]]]]]]]]]]]]]]]]]]" << endl;
			cout << endl;
			cout << endl;
			session_ptr->Onrecv();
			break;
		}
	}
}
void cServer::DataAnalysis(cSession* _session, PACKET_HEAD* _recvpacket)
{
	cout << "data anaylics" << endl;
	bool usercheck = _session->getModeCheck();
	int key = _session->getKey();



	if (_recvpacket->mDbNecessity == true)
	{
		cout << "DB CHECK" << endl;
		mDatabase.DBparsing(_recvpacket);
	}

	switch (_recvpacket->mManagerType)
	{
	case MANAGER_TYPE_SM:
		cout << "MANAGER_TYPE_SM PARSING" << endl;
		if (_recvpacket->mMsg == MSG_LOGIN_OK)
		{
			mUserManager.InputUser((cUser*)_session);
		}
		mSessionManager.SessionParsing(key, _recvpacket);
		break;
	case MANAGER_TYPE_UM:
		cout << "MANAGER_TYPE_UM PARSING" << endl;
		mUserManager.UserParsing(key, _recvpacket);
		break;
	case MANAGER_TYPE_RM:
		cout << "MANAGER_TYPE_RM PARSING" << endl;
		mRoomManager.RoomParsing((cUser*)_session, _recvpacket);
		break;
	}

}
void cServer::Acceptor()
{
	SOCKET clientsock;
	while (1)
	{

		clientsock = mAccept.Accept();
		cout << "클라이언트 접속" << endl;
		// 객체 생성 까지만 해주고 초기화는 세션매니저에서 진행
		cUser* newsession = new cUser;

		// 짝지어주기 cp 랑 
		mCPhandle.InputClient(clientsock, (cSession*)newsession);

		// 세션매니저에 셔션 객체 추가 
		mSessionManager.InputSession((cSession*)newsession, clientsock);
	
	}
}