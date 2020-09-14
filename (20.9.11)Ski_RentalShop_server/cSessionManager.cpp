#include "cSessionManager.h"
cSessionManager::cSessionManager()
{
	mSessionCount = 0;
}
cSessionManager::~cSessionManager()
{

}
void cSessionManager::SessionParsing(int _key, PACKET_HEAD* _recvpacket)
{
	mUserDB.DBparsing(_recvpacket, (cUser*)mSessionArray[_key]);

	mSessionArray[_key]->Paring(_recvpacket);
}

void cSessionManager::InputSession(SOCKET _SOCK, cSession* _session)
{
	mCS.Lock();
	cout << "Ŭ���̾�Ʈ ����" << endl;
	for (int key = 0; key < 50;key++)
	{
		if (mSessionArray[key] == NULL)
		{
			_session->Setkey(key);
			_session->SetSock(_SOCK);

			mSessionArray[key] = _session;
			_session->Onrecv();
			break;
		}
	}
	mSessionCount++;
	mCS.Unlock();
}
void cSessionManager::DeleteSession(int _key)
{
	mCS.Lock();
	cSession* temp = mSessionArray[_key];


	mUserDB.ModifiedRservation((cUser*)temp);


	mSessionArray[_key] = NULL;
	mSessionCount--;
	delete temp;

	mCS.Unlock();
}

void cSessionManager::ShowCount()
{
	cout << "���� ���ӵ� ���� = " << mSessionCount << endl;
}

