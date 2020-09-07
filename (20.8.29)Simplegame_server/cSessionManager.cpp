#include "cSessionManager.h"
cSessionManager::cSessionManager()
{
	mSessionCount = 0;
}
cSessionManager::~cSessionManager()
{

}

void cSessionManager::InputSession(cSession* _session,SOCKET _sock)
{
	mSessionCount++;
	for (int i = 0;i < 20;i++)
	{
		if (mSessionArray[i] == NULL)
		{
			mSessionArray[i] = _session;
			_session->SetKey(i);
			_session->SetSock(_sock);
			_session->Onrecv();

			break;
		}
	}

	ShowCount();
}

void cSessionManager::DelteSession(int _key)
{
	mSessionCount--;
	mSessionArray[_key] = NULL;
	ShowCount();
}

void cSessionManager::ShowCount()
{
	cout << "泅犁 技记 立加磊荐 = " <<mSessionCount << endl;
}
void cSessionManager::SessionParsing(int _key, PACKET_HEAD* _recvpacket)
{
	mSessionArray[_key]->Parsing(_recvpacket);
}