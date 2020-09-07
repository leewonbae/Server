#include "cBaseball.h"
cBaseball::cBaseball() :cIOCP()
{
	
}
cBaseball::~cBaseball()
{

}
void cBaseball::Parsing(SOCKETINFO* _ptr)
{
	PACKET_HEAD p_head;
	memset(&p_head, 0, sizeof(PACKET_HEAD));
	memcpy(&p_head, _ptr->_databuf, sizeof(PACKET_HEAD));
	switch (p_head.p_cmd)
	{
	case PROTOCOL::pro_ready:
		cout << "ready" << endl;
		break;
	case PROTOCOL::pro_start:
		cout << "start" << endl;
		break;
	case PROTOCOL::pro_target:
		MSG_TARGET_CALL(&p_head,_ptr);
		break;
	case PROTOCOL::pro_result:
		MSG_RESULT_CALL(&p_head,_ptr);
		break;

	default:
		cout << "지정된 프로토콜이 아닙니다." << endl;
		break;
	}
}
void cBaseball::MSG_TARGET_CALL(PACKET_HEAD* _phead,SOCKETINFO* _ptr)
{
	cout << "target call" << endl;
	sTarget st;
	memset(&st, 0, sizeof(sTarget));
	st._targetNum = 256;
	char* p = _ptr->_databuf;
	memcpy(p, _phead, sizeof(PACKET_HEAD));
	memcpy(p + sizeof(PACKET_HEAD), &st, sizeof(sTarget));
	
	PacketSend(_ptr);
}
void cBaseball::MSG_RESULT_CALL(PACKET_HEAD* _phead,SOCKETINFO* _ptr)
{
	cout << "result" << endl;
}