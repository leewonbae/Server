#include "cUserManager.h"
cUserManager::cUserManager()
{
	mUsercount = 0;
}
cUserManager::~cUserManager()
{

}
void cUserManager::InputUser(cUser* _user, int _key)
{
	cLog::Server_print(__FUNCTION__, " ");
	_user->SetUser(true);
	mUserArray[_key] = _user;
	mUsercount++;
	ShowUser();
}
void cUserManager::DeleteUser(int _key)
{
	mUserArray[_key] = NULL;
	mUsercount--;
	ShowUser();
}
void cUserManager::ShowUser()
{
	cout << "현재 유저 = " << mUsercount << endl;
}
void cUserManager::UserParsing(int _key, PACKET_HEAD* _recvpacket)
{
	cLog::Server_print(__FUNCTION__, " ");
	cLog::Session_print(_key);
	if (_recvpacket->mPacket_cmd == PROTO_USER_ORDER_REQ)
	{
		PACKET_ORDER* order = (PACKET_ORDER*)_recvpacket;
		mUserArray[order->mMasterkey]->Parsing(_recvpacket);
	}
	else {
		mUserArray[_key]->Parsing(_recvpacket);
	}
	
}