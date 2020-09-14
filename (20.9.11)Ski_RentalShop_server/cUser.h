#pragma once
#include "Resource.h"
#include "Packet.h"
#include "cSession.h"
#include "cCriticalSection.h"
class cUser : public cSession
{
public:
	cUser();
	~cUser();

	void SetUserinfo(USERINFO _userinfo);
	void SetReservation(RESERVATION _reserv);

	USERINFO getUserinfo();
	RESERVATION getReserv();


	typedef void (cUser::* fp)(PACKET_HEAD* _recvpacket);
	void Paring(PACKET_HEAD* _recvpacket);
	
private:
	void PTC_LOGIN(PACKET_HEAD* _recvpacket);
	void PTC_NEWUSER(PACKET_HEAD* _recvpacket);
	void PTC_EQUIPMENT_LIST(PACKET_HEAD* _recvpacket);
	void PTC_RETAL(PACKET_HEAD* _recvpacket);
	void PTC_RETURN(PACKET_HEAD* _recvpacket);


	
	USERINFO mUserinfo;
	RESERVATION mReserv;
	map<int, fp> mMap;
	map<int, fp>::iterator mIter;


};

