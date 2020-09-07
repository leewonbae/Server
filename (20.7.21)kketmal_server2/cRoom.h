#pragma once
 
#include "resource.h"
 
class cRoom  
{
public:
	cRoom();
	~cRoom();
	void SetUserReady(SOCKETINFO* _sinfo);
	void InputUser(SOCKETINFO* _sinfo);
	bool GetStartflag();
	bool StartCheck();
	void ShowRoomInfo();
	int GetUserCount();
	void SetUserReadylistinit();
	SOCKETINFO** GetUSER();

private:
	SOCKETINFO* m_UserList[6];
	int m_PlayCount;
	bool m_UserReadyList[6];
	int m_Usercount;
	bool bm_StartFlag;
	CRITICAL_SECTION cs;

};

