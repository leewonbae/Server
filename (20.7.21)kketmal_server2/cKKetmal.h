#pragma once

 
#include "cRoom.h"
#include "cIOCP.h"
class cKKetmal  : public cIOCP
{
public:
	cKKetmal();
	~cKKetmal();
	virtual void Switch_msg(int _msg_number, SOCKETINFO* _sinfo) ;
	void MSG_ROOMLIST_CALL(int _msg_number, SOCKETINFO* _sinfo);
	void MSG_READY_CALL(int _msg_number, SOCKETINFO* _sinfo);
	void MSG_WORD_CALL(int _msg_number, SOCKETINFO* _sinfo);
	void MSG_END_CALL(int _msg_number, SOCKETINFO* _sinfo);
	void MSG_INROOM_CALL(int _msg_number, SOCKETINFO* _sinfo);
	void MSG_MAKE_ROOM(int _msg_number, SOCKETINFO* _sinfo);
	void MSG_TURNCHECK_CALL(int _msg_number, SOCKETINFO* _sinfo);
	
private:
	START_ROOM_INFO* start_roomlist[10];
	cRoom* m_cRoom[10];
 
	char TEMP_MSG[20];
	int m_RoomCount;
	CRITICAL_SECTION kk;
};

