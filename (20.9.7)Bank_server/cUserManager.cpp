#include "cUserManager.h"
cUserManager::cUserManager()
{
	mUsercount = 0;
}
cUserManager::~cUserManager()
{

}
void cUserManager::InputUser(cUser* _user)
{
	cCriticalSection cs;
	cs.Lock();

	int key = _user->getKey();
	mUserArray[key] = _user;
	mUsercount++;
	ShowUserCount();
	cs.Unlock();
}
void cUserManager::DeleteUser(int _key)
{
	cCriticalSection cs;
	cs.Lock();

	mUserArray[_key]->ActiveCange();
	mUserArray[_key] = NULL;

	mUsercount--;
	ShowUserCount();

	cs.Unlock();
}
void cUserManager::SetDataBase(cDataBase* _DBptr)
{
	mDBPtr = _DBptr;
}
void cUserManager::ShowUserCount()
{
	cout << "UserCount  = " << mUsercount << endl;
}
void cUserManager::UserParsing(int _key, PACKET_HEAD* _recvpacket)
{
	cout << "À¯Àú ÆÄ½Ì" << endl;
	if (_recvpacket->mCmd == PTC_TRANSFER_MONEY_REQ)
	{
		mDBPtr->TransferMoney(_recvpacket);
	}

	mUserArray[_key]->Paring(_recvpacket);
}