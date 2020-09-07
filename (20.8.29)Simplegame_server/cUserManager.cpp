#include "cUserManager.h"
cUserManager::cUserManager()
{
	mUserCount = 0;
}
cUserManager::~cUserManager()
{

}
void cUserManager::InputUser(cUser* _user)
{
	int userkey = _user->getKey();
	mUserArray[userkey] = _user;
	mUserCount++;
	ShowCount();
}
void cUserManager::DelteUser(int _key)
{
	mUserArray[_key] = NULL;
	mUserCount--;
	ShowCount();
}
void cUserManager::ShowCount()
{
	cout << "유저 카운트 = " << mUserCount << endl;
}
void cUserManager::UserParsing(int _key,PACKET_HEAD* _recvpacket)
{
	mUserArray[_key]->Parsing(_recvpacket);
}