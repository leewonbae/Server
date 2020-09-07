#pragma once
#include "cSession.h"
#include "Packet.h"
#include "Log.h"
class cUser : public cSession
{
public:
	cUser();
	~cUser();
	void SetUserinfo(PACKET_NEWUSER* _userinfo);
	void SetMasterkey(int _key);


	int getMasterkey();
	typedef void (cUser::* fp)(PACKET_HEAD* _recvpacket);
	void Parsing(PACKET_HEAD* _phead);
private:
	void PROTO_LOGIN(PACKET_HEAD* _phead);
	void PROTO_NEWUSER(PACKET_HEAD* _phead);
	void PROTO_MENULIST(PACKET_HEAD* _phead);
	void PROTO_USER_ORDER(PACKET_HEAD* _phead);


	map<int, fp> mMap;
	map<int, fp>::iterator mIter;
	PACKET_NEWUSER mUserinfo;
	int mMasterkey;
};

  