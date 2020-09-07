#include "cSessionManager.h"
cSessionManager::cSessionManager()
{
	mSessionCount = 0;
	mKeycount = 0;
}
cSessionManager::~cSessionManager()
{

}
bool cSessionManager::InputSession(cSession* _session)
{
	mSessionCount+=1;
	_session->SetKEY(mKeycount);
	mKeycount++;
	
	for (int i = 0;i < mSessionCount;i++)
	{
		if (mListCheck[i] == false)
		{
			mSessionList[i] = _session;
			mListCheck[i] = true;
		
			return true;
			break;
		}
	}
	
	return false;
}
bool cSessionManager::DeleteSession(int _key)
{
	for (int i = 0;i < mSessionCount;i++)
	{
		if (mSessionList[i]->getKey() == _key)
		{
			mListCheck[i] = false;
			mSessionList[i] = NULL;
			mSessionCount--;
			return true;
		}
	}
	return false;
}

void cSessionManager::ParsingSession(int _key, OVERDATA* _over)
{
	
	
	for (int i = 0;i < mSessionCount;i++)
	{
		if (mSessionList[i]->getKey() == _key)
		{
			mSessionList[i]->Parsing(_over);
		}
	}
	
	
}
void cSessionManager::Setrecv(int _key)
{
	for (int i = 0;i < mSessionCount;i++)
	{
		if (mSessionList[i]->getKey() == _key)
		{
			mSessionList[i]->Onrecv();
		}
	}
}