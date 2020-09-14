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
	mCS.Lock();
	int key = _user->getKey();
	mUserArray[key] = _user;
	_user->SetUserCheck(true);

	
	mUsercount++;
	ShowUserCount();


	mCS.Unlock();
}
void cUserManager::DeleteUser(int _key)
{
	mCS.Lock();
	mUserArray[_key] = NULL;
	mUsercount--;
	ShowUserCount();

	mCS.Unlock();
}
void cUserManager::ShowUserCount()
{
	cout << "현재 유저 수는  = " << mUsercount << endl;
}
void cUserManager::UserParsing(int _key, PACKET_HEAD* _recvpacket)
{
	mEquipment.EquipmentParsing(_recvpacket);
	mUserArray[_key]->Paring(_recvpacket);

}