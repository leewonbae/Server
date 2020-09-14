#include "cUser.h"
cUser::cUser()
{
	
	mMap.insert(std::map<int, fp>::value_type(PTC_LOGIN_REQ, &cUser::PTC_LOGIN));
	mMap.insert(std::map<int, fp>::value_type(PTC_NEWUSER_REQ, &cUser::PTC_NEWUSER));
	mMap.insert(std::map<int, fp>::value_type(PTC_EQUIPMENT_LIST_REQ, &cUser::PTC_EQUIPMENT_LIST));
	mMap.insert(std::map<int, fp>::value_type(PTC_RETAL_REQ, &cUser::PTC_RETAL));
	mMap.insert(std::map<int, fp>::value_type(PTC_RETURN_REQ, &cUser::PTC_RETURN));
	 

}
cUser::~cUser()
{


}

void cUser::SetUserinfo(USERINFO _userinfo)
{
	memcpy(&mUserinfo, &_userinfo, sizeof(USERINFO));
}
void cUser::SetReservation(RESERVATION _reserv)
{
	memcpy(&mReserv, &_reserv, sizeof(RESERVATION));
}
 
USERINFO cUser::getUserinfo()
{
	return  mUserinfo;
}

RESERVATION cUser::getReserv()
{
	return  mReserv;
}


void cUser::Paring(PACKET_HEAD* _recvpacket)
{
	fp	Temp;

	mIter = mMap.find(_recvpacket->mCmd);

	if (mIter != mMap.end())
	{
		Temp = mIter->second;
		(this->*Temp)(_recvpacket);
	}
}

void cUser::PTC_LOGIN(PACKET_HEAD* _recvpacket)
{
	cout << "PTC_LOGIN" << endl;
	PACKET_LOGIN* plogin = (PACKET_LOGIN*)_recvpacket;

	Onsend((void*)plogin, plogin->mPacket_size);


}


void cUser::PTC_NEWUSER(PACKET_HEAD* _recvpacket)
{
	cout << "PTC_NEWUSER" << endl;
	PACKET_NEWUSER* pnew = (PACKET_NEWUSER*)_recvpacket;
	Onsend((void*)pnew, pnew->mPacket_size);

}


void cUser::PTC_EQUIPMENT_LIST(PACKET_HEAD* _recvpacket)
{
	cout << "PTC_EQUIPMENT_LIST" << endl;
	PACKET_LIST* plist = (PACKET_LIST*)_recvpacket;
	 
	Onsend((void*)plist, plist->mPacket_size);
 
	

}


void cUser::PTC_RETAL(PACKET_HEAD* _recvpacket)
{
	cout << "PTC_RETAL" << endl;
	PACKET_RENTAL* prental = (PACKET_RENTAL*)_recvpacket;
	if (_recvpacket->mPacket_MSG == MSG_RENTAIL_OK)
	{
		mReserv.mSki_count += prental->mSKIcount;
		mReserv.mBoard_count += prental->mBOARDcount;
		mReserv.mClothing_count += prental->mCLOTHINGcount;
		
	}
	Onsend((void*)prental, prental->mPacket_size);
}


void cUser::PTC_RETURN(PACKET_HEAD* _recvpacket)
{
	cout << "PTC_RETURN" << endl;
	PACKET_RETURN* preturn = (PACKET_RETURN*)_recvpacket;
	if (_recvpacket->mPacket_MSG == MSG_RETURN_OK)
	{
		mReserv.mSki_count -= preturn->mSKIcount;
		mReserv.mBoard_count -= preturn->mBOARDcount;
		mReserv.mClothing_count -= preturn->mCLOTHINGcount;
	}
	Onsend((void*)preturn, preturn->mPacket_size);
}
 