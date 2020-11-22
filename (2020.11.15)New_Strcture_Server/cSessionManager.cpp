#include "cSessionManager.h"
cSessionManager::cSessionManager()
{
	 
	mKeyCount = 0;
}
cSessionManager::~cSessionManager()
{

}
void cSessionManager::OutSession(cSession* _session)
{
	mCS_SM.LOCK();
	
	mSessionArrayIter = find(mSessionArray.begin(), mSessionArray.end(), _session);
	mSessionArray.erase(mSessionArrayIter);
	delete _session;
	mCS_SM.UN_LOCK();
	cout << "SESSION COUNT = " << mSessionArray.size() << endl;
 
}
cSession* cSessionManager::getNewSession()
{
	if (MAX_SESSION_SIZE <= mSessionArray.size())
	{
		return NULL;
	}

	mCS_SM.LOCK();
	cUser* newsession = new cUser;
	mSessionArray.push_back(newsession);
	newsession->setKey(mKeyCount);
 
	mKeyCount++;
 
	mCS_SM.UN_LOCK();
	cout << "SESSION COUNT = " << mSessionArray.size() << endl;
	return newsession;
}
 