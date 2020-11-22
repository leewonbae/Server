#pragma once
#include "Resource.h"
#include "cUser.h"
#include "cCriticalSection.h"
class cRoom
{
public:
	cRoom();
	~cRoom();
	int getUserCount() { return mUserCount; }

	bool getCondition() { return mGameCondition; }
	
	void AttackUsers(PACKET_ATTACK* _packet,cUser* _user);
	cUser* EnemyUsers(cUser* _user);
	void SendGameResult(PACKET_ATTACK* _packet, cUser* _user);

	void BroadMsg(void* _packet, int _packetsize);
	bool ReadyUser(cUser* _user);
	 
	void OutRoomUser(cUser* _user);
	void InputRoomUser(cUser* _user);
private:
	cCriticalSection mCS_ROOM;
	cUser* mUserArray[2] = { NULL, };
	bool mUserReadyCondition[2] = { false, };
	PACKET_ATTACK mTemp_packet;

	int mAttackReqCount = 0;
	int mReadycount = 0;
	int mUserCount;
	bool mGameCondition;

};

