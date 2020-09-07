#pragma once
#include "Resource.h"
#include "Packet.h"
#include "cUser.h"
#include "cCriticalSection.h"

struct NODE {
	USER_INFO mUserInfo;
	NODE* mNextNode;

};

class cDataBase
{
public:
	cDataBase();
	~cDataBase();
	void PasingDB(cUser* _user, PACKET_HEAD* _recvpacket);
	void InputData(PACKET_HEAD* _recvpacket);//데이터 삽입
	void CheckData(cUser* _user, PACKET_HEAD* _recvpacket);
	void ShowDataCount();
	void TransferMoney(PACKET_HEAD* _recvpacket);
	 
private:
	NODE* mHead;
	NODE* mTail;

	int mDBcount;

};

