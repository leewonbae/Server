#include "cUser.h"
cUser::cUser()
{
	mMap.insert(std::map<int, fp>::value_type(PTC_LOGIN_REQ, &cUser::PTC_LOGIN));
	mMap.insert(std::map<int, fp>::value_type(PTC_NEW_USER_REQ, &cUser::PTC_NEW_USER));
}
cUser::~cUser()
{

}
void cUser::SetRoomNum(int _roomnum)
{
	RoomNum = _roomnum;
}
int cUser::getRoomNUM()
{
	return RoomNum;
}
void cUser::Parsing(PACKET_HEAD* _phead)
{

	PACKET_HEAD* m_Packet = _phead;

	fp	Temp;

	mIter = mMap.find(_phead->mCmd);

	if (mIter != mMap.end())
	{
		Temp = mIter->second;
		(this->*Temp)(_phead);
	}
}

void cUser::PTC_LOGIN(PACKET_HEAD* _phead)
{
	cout << "parsing login" << endl;
	PACKET_LOGIN* plogin = (PACKET_LOGIN*)_phead;
	cout << plogin->mCmd << endl;

	Onsend((void*)plogin, plogin->mPacketSize);
}
void cUser::PTC_NEW_USER(PACKET_HEAD* _phead)
{
	cout << "PTC_NEW_USER " << endl;
	PACKET_NEWUSER* puser = (PACKET_NEWUSER*)_phead;

	Onsend((void*)puser, puser->mPacketSize);
}