#pragma once
#include "cIOCP.h"
class cBaseball : public cIOCP
{
public:
	cBaseball();
	~cBaseball();
	virtual void Parsing(SOCKETINFO* _ptr);
	void MSG_TARGET_CALL(PACKET_HEAD* _phead,SOCKETINFO* _ptr);
	void MSG_RESULT_CALL(PACKET_HEAD* _phead,SOCKETINFO* _ptr);



private:

};

