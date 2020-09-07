#include "cSessionManager.h"
cSessionManager::cSessionManager()
{
	mSessionCount = 0;
}
cSessionManager::~cSessionManager()
{

}
void cSessionManager::SetDataBase(cDataBase* _db)
{
	mPtrDB = _db;
}
void cSessionManager::InputSession(SOCKET _SOCK, cSession* _session)
{
	cCriticalSection CriticalSection;
	CriticalSection.Lock();
	for (int key = 0; key < MAX_SESSION_COUNT; key++)
	{
		if (mSessionArray[key] == NULL)
		{
			mSessionArray[key] = _session;
			_session->SetSock(_SOCK);
			_session->Setkey(key);
			_session->Onrecv();
		
			
			break;

		}
		
	}
	mSessionCount++;
	ShowCount();
	CriticalSection.Unlock();
	
}

void cSessionManager::DeleteSession(int _key)
{
	cCriticalSection CriticalSection;
	CriticalSection.Lock();
	cSession* temp = mSessionArray[_key];
	mSessionArray[_key] = NULL;
	mSessionCount--;
	ShowCount();

	delete temp;
	CriticalSection.Unlock();
}
void cSessionManager::ShowCount()
{
	cout << "泅犁 立加吝牢 技记 荐 = " << mSessionCount << endl;
}
void  cSessionManager::SessionParsing(int _key, PACKET_HEAD* _recvpacket)
{
	cout << "技记 颇教" << endl;
	mPtrDB->PasingDB((cUser*)mSessionArray[_key],_recvpacket);

	mSessionArray[_key]->Paring(_recvpacket);
}