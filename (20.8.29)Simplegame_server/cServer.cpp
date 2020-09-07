#include "cServer.h"
cServer::cServer()
{
	cout << "server ������" << endl;
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
			cout << "Ŭ���̾�Ʈ ����" << endl;
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
		cout << "Ŭ���̾�Ʈ ����" << endl;
		// ��ü ���� ������ ���ְ� �ʱ�ȭ�� ���ǸŴ������� ����
		cUser* newsession = new cUser;

		// ¦�����ֱ� cp �� 
		mCPhandle.InputClient(clientsock, (cSession*)newsession);

		// ���ǸŴ����� �ż� ��ü �߰� 
		mSessionManager.InputSession((cSession*)newsession, clientsock);
	
	}
}