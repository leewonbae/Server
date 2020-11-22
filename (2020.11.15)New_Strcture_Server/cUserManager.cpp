#include "cUserManager.h"


cUserManager::cUserManager()
{
	mUserCount = 0;
}
cUserManager::~cUserManager()
{

}
void cUserManager::ShowUserCount()
{
	cout << "ÇöÀç USER COUNT = " << mUserCount << endl;
}
void cUserManager::OutUser(cUser* _user)
{
	mMysql.UpdateUserinfo(_user);
	mCS_USERMANAGER.LOCK();
	mUserCount--;
	ShowUserCount();
	mCS_USERMANAGER.UN_LOCK();
	
}
void cUserManager::UserManagerParsing(PACKET_HEAD* _phead, cUser* _user)
{ 
		mMysql.MysqlParsing(_phead, _user);
		
		if (_phead->mCmd == PTC_LOGIN )
		{
			PACKET_LOGIN* plog = (PACKET_LOGIN*)_phead;
			if (plog->mPacket_ACK == PACKET_TRUE)
			{
				mCS_USERMANAGER.LOCK();
				mUserCount++;
				ShowUserCount();
				mCS_USERMANAGER.UN_LOCK();
			}
			_user->OnSend(plog, plog->mPacket_size);
		}
		if (_phead->mCmd == PTC_NEWUSER)
		{
			PACKET_NEWUSER* pnew = (PACKET_NEWUSER*)_phead;
			_user->OnSend(pnew, pnew->mPacket_size);
		}

}