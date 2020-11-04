#include "cSessionManager.h"
cSessionManager::cSessionManager()
{
	mSessionCount = 0;
}
cSessionManager::~cSessionManager()
{

}
bool cSessionManager::InputSession(cSession* _session)
{
	for (int i = 0; i < MAX_SESSION_ARRAY;i++)
	{
		if (mSessionArray[i] != NULL)
		{
			continue;
		}
		else
		{
			mCS.lock();


			_session->SetKey(i);
			mSessionArray[i] = _session;
			mSessionCount++;


			mCS.Unlock();
			return true;
		}
	}
	return false;
}


void  cSessionManager::SessionManager_Parsing(cSession* _session, PACKET_HEAD* _phead)
{
	cout << "SESSION MANAGER PARSING START" << endl;
	PACKET_LOGIN* plog = (PACKET_LOGIN*)_phead;
	if (plog->mLoginCheck == false && _phead->mCmd == PTC_LOGIN)//회원가입
	{
		mUserDba.InputUserInfo(_phead, _session);
	}
	else if(plog->mLoginCheck == true && _phead->mCmd == PTC_LOGIN)// 로그인
	{
		mUserDba.CheckUserLogin(_phead, _session);
	}
	else
	{
		cout << "[sessionmanager error]" << endl;
	}
	
}

void cSessionManager::OutSession(cSession* _session)
{
	mCS.lock();

	int key = _session->getKey();
	cSession* ptr = mSessionArray[key];
	mSessionArray[key] = NULL;
	mSessionCount--;
	delete ptr;

	mCS.Unlock();
}