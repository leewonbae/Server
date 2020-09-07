#pragma once
#include "Resource.h"
#include "Packet.h"
#include "cSession.h"
#include "cCriticalSection.h"
class cUser : public cSession
{
public :
	cUser();
	~cUser();

	typedef void (cUser::* fp)(PACKET_HEAD* _recvpacket);
	void Paring(PACKET_HEAD* _recvpacket);
	void SetUserINFO(USER_INFO* _userinfo);
	void ActiveCange();
private:
	void PTC_LOGIN(PACKET_HEAD* _recvpacket);
	void PTC_NEWUSER(PACKET_HEAD* _recvpacket);
	void PTC_INPUT_MONEY(PACKET_HEAD* _recvpacket);
	void PTC_OUTPUT_MONEY(PACKET_HEAD* _recvpacket);
	void PTC_TRANSFER_MONEY(PACKET_HEAD* _recvpacket);
	map<int, fp> mMap;
	map<int, fp>::iterator mIter;
 
	USER_INFO* mUserInfo;

};

