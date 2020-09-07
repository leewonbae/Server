#include "cUser.h"
cUser::cUser()
{
	 
	mMap.insert(std::map<int, fp>::value_type(PROTO_LOGIN_REQ, &cUser::PROTO_LOGIN));
	mMap.insert(std::map<int, fp>::value_type(PROTO_NEWUSER_REQ, &cUser::PROTO_NEWUSER));
	mMap.insert(std::map<int, fp>::value_type(PROTO_MENULIST_REQ, &cUser::PROTO_MENULIST));
	mMap.insert(std::map<int, fp>::value_type(PROTO_USER_ORDER_REQ, &cUser::PROTO_USER_ORDER));
 
}
cUser::~cUser()
{

}
void cUser::SetUserinfo(PACKET_NEWUSER* _userinfo)
{
	memcpy(&mUserinfo, _userinfo, sizeof(PACKET_NEWUSER));
}
void cUser::SetMasterkey(int _key)
{
	mMasterkey = _key;
}
int cUser::getMasterkey()
{
	return mMasterkey;
}

void cUser::Parsing(PACKET_HEAD* _phead)
{
	cLog::Server_print(__FUNCTION__, " ");
	PACKET_HEAD* m_Packet = _phead;

	fp	Temp;

	mIter = mMap.find(_phead->mPacket_cmd);

	if (mIter != mMap.end())
	{
		Temp = mIter->second;
		(this->*Temp)(_phead);
	}
}
void cUser::PROTO_LOGIN(PACKET_HEAD* _phead)
{
	cLog::Server_print(__FUNCTION__, " ");
	PACKET_LOGIN* login = (PACKET_LOGIN*)_phead;
	cout << "[packet ]id = " << login->ID << endl;
	cout << "[packet ]pass = " << login->PASSWORD << endl;
	
}
void cUser::PROTO_NEWUSER(PACKET_HEAD* _phead)
{
	cLog::Server_print(__FUNCTION__, " ");
	PACKET_NEWUSER* newuser = (PACKET_NEWUSER*)_phead;
	cout << "[packet ]id = " <<newuser->ID << endl;
	cout << "[packet ]PASSWORD = " << newuser->PASSWORD << endl;
	cout << "[packet ]DB_TYPE = " << newuser->DB_TYPE << endl;
	cout << "[packet ]MENU = " << newuser->MENU << endl;
}
void cUser::PROTO_MENULIST(PACKET_HEAD* _phead)
{
	cLog::Server_print(__FUNCTION__, " ");
	PACKET_MENULIST* menulist = (PACKET_MENULIST*)_phead;
	for (int i = 0;i < menulist->mMenucount;i++)
	{
		cout << "[packet ]Menulist" << menulist->mMenulist[i] << endl;
	}
	
}
void cUser::PROTO_USER_ORDER(PACKET_HEAD* _phead)
{
	cLog::Server_print(__FUNCTION__, " ");
	
	PACKET_ORDER* order = (PACKET_ORDER*)_phead;
	cout << "[packet ]mOrdercount " <<order->mOrdercount<< endl;
	cout << "[packet ]mOrderMaster " << order->mOrderMaster << endl;
}