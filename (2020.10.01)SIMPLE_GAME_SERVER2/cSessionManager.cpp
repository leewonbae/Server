#include "cSessionManager.h"
cSessionManager::cSessionManager()
{
	mSessionCount = 0;
}
cSessionManager::~cSessionManager()
{
	
}
 
void cSessionManager::InputSession(cSession* _session)
{
	
	for (int i = 0; i < MAX_SESSION_ARRAY;i++)
	{
		if (mSessionArray[i] == NULL)
		{
			mCS.LockCs();
			_session->SetKey(i);
			mSessionArray[i] = _session;
			mSessionCount++;
			mCS.UnLock();
			break;
		}
	}
	cLog::Print_SessionCount(mSessionCount);
}
void cSessionManager::DelteSession(int _index)
{
	cSession* temp = mSessionArray[_index];
	mCS.LockCs();
	delete temp;
	mSessionArray[_index] = NULL;
	mSessionCount--;
	mCS.UnLock();
	cLog::Print_SessionCount(mSessionCount);
}