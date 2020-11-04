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
	_user->SetUser(true);
	mUser_CS.lock();
	mUserCount++;
	mUser_CS.Unlock();
	ShowUserCount();
}
void cUserManager::OutUser()
{
	mUser_CS.lock();
	mUserCount--;
	mUser_CS.Unlock();
	ShowUserCount();
}
void cUserManager::ShowUserCount()
{
	cout << "ÇöÀç UserCount = " << mUserCount << endl;
}
void cUserManager::UserManager_Parsing(cUser* _user, PACKET_HEAD* _phead)
{
	cout << "UserManager_Parsing START" << endl;
	switch (_phead->mCmd)
	{
	case PTC_ITEM_UPLOAD:
		mItemDBA.ItemParsing(_user, _phead);
		break;
	default:
		cout << "USER_MANAGER  [PACKET_CHECK_ERROR]" << endl;
		break;
	}
}