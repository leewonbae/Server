#include "cSessionManager.h"
cSessionManager::cSessionManager()
{
	mSessioncount = 0;
	mkeycount = 0;
}
cSessionManager::~cSessionManager()
{

}
bool cSessionManager::InputSession(cSession* _session)
{
	cLog::Server_print(__FUNCTION__, " ");
	for (int i = 0;i < SESSION_ARRAY;i++)
	{
		if (mSessionArray[i] == NULL)
		{
			mSessionArray[i] = _session;
			_session->Onrecv();
			_session->SetKey(mkeycount);
			mSessioncount++;
			mkeycount++;
			return true;
		}
	}
	return false;
}
void cSessionManager::DelteSession(int _key)
{
	cLog::Server_print(__FUNCTION__, " ");
	delete mSessionArray[_key];
	mSessionArray[_key] = NULL;
	mSessioncount--;
	
}
void cSessionManager::SessionParsing(int _key, PACKET_HEAD* _phead)
{
	cLog::Server_print(__FUNCTION__, " ");
	cLog::Session_print(_key);
	mSessionArray[_key]->Parsing(_phead);
}
void cSessionManager::ShowSessionCount()
{
	cout << "[접속 중인 SESSION = " << mSessioncount << " ]" << endl;
}