#include "cKKetmal.h"

cKKetmal::cKKetmal() :cIOCP()
{
	InitializeCriticalSection(&kk);
	m_RoomCount = 0;
}
cKKetmal::~cKKetmal()
{
	DeleteCriticalSection(&kk);
	cout << "kketmal exit" << endl;
}
 
 
void cKKetmal::Switch_msg(int _msg_number, SOCKETINFO* _sinfo)
{
 
	 
	switch (_msg_number)
	{
 
	case act_room:
		MSG_ROOMLIST_CALL(_msg_number,_sinfo);
		break;
	case act_inRoom:
		MSG_INROOM_CALL(_msg_number, _sinfo);
		break;
	case act_ready:
		MSG_READY_CALL(_msg_number, _sinfo);
		break;
	case act_makeRoom:
		MSG_MAKE_ROOM(_msg_number, _sinfo);
		break;
	case act_turncheck:
		MSG_TURNCHECK_CALL(_msg_number, _sinfo);
		break;
    case act_end:
		MSG_END_CALL(_msg_number, _sinfo);
		break;
	default:
		cout << "지정된 행동 리스트에 없음" << endl;
		break;
	}
}
 
void cKKetmal::MSG_MAKE_ROOM(int _msg_number, SOCKETINFO* _sinfo)
{
	EnterCriticalSection(&kk);
	cout << "방을 만듭니다." << endl;

	cRoom* newobject = new cRoom;
	newobject->InputUser(_sinfo);
	
	m_cRoom[m_RoomCount] = newobject;
	_sinfo->_roomNumber = m_RoomCount;

	m_RoomCount++;
	strcpy(TEMP_MSG, "방을 만들었습니다.");
	MSG_SEND(_sinfo, TEMP_MSG);
	LeaveCriticalSection(&kk);
}
void cKKetmal::MSG_INROOM_CALL(int _msg_number, SOCKETINFO* _sinfo)
{
	EnterCriticalSection(&kk);
	cout << "방에 들어가길 희망합니다.." << endl;
	int temp;
	temp = (int)_sinfo->_d_info._data[0];
	
	cout << "입력된 요청 방 번호는		" << temp << "입니다." << endl;
	if (m_cRoom[temp]->GetUserCount() == 0)
	{
		strcpy(TEMP_MSG, "현재 방이 존재 하지 않습니다.");
	}
	else
	{
		m_cRoom[temp]->InputUser(_sinfo);
		_sinfo->_roomNumber = temp;
		strcpy(TEMP_MSG, "방에 입장합니다.");
	}
	LeaveCriticalSection(&kk);
	MSG_SEND(_sinfo, TEMP_MSG);
}
void cKKetmal::MSG_ROOMLIST_CALL(int _msg_number, SOCKETINFO* _sinfo)
{
	SEND_ROOMINFO sendroom;
	sendroom.roomcount = m_RoomCount;
	
	cout << "방 목록을 요청합니다." << endl;
	cout << "현재 방 카운트 = "<< m_RoomCount << endl;
	
	
	sendroom.roomcount = m_RoomCount;
	for (int i = 0;i < m_RoomCount;i++)
	{
		cout <<"유저 카운트=="<< m_cRoom[i]->GetUserCount() << endl;
		sendroom.roomlist[i] = m_cRoom[i]->GetUserCount();
	}
	MSG_SEND(_sinfo, (char*)&sendroom);
	
	
}
void cKKetmal::MSG_READY_CALL(int _msg_number, SOCKETINFO* _sinfo)
{
	EnterCriticalSection(&kk);
	cout << "플레이어 준비 오케이" << endl;
	m_cRoom[_sinfo->_roomNumber]->SetUserReady(_sinfo);
	if (m_cRoom[_sinfo->_roomNumber]->GetUserCount() >= 2)
	{
		if (m_cRoom[_sinfo->_roomNumber]->StartCheck())
		{
			START_ROOM_INFO* newobject = new START_ROOM_INFO;
			newobject->User_list= m_cRoom[_sinfo->_roomNumber]->GetUSER();
			newobject->s_user_count = m_cRoom[_sinfo->_roomNumber]->GetUserCount();
			newobject->STSD.Playflag = true;
			newobject->s_play_user = 0;
			strcpy(newobject->STSD.startword, "이원배");
			 
			newobject->STSD.user_count = m_cRoom[_sinfo->_roomNumber]->GetUserCount();
			start_roomlist[_sinfo->_roomNumber] = newobject;

			cout << "전원 준비 완료" << endl;
			 
			for (int i = 0;i < m_cRoom[_sinfo->_roomNumber]->GetUserCount();i++)
			{
				MSG_SEND(start_roomlist[_sinfo->_roomNumber]->User_list[i],(char*)&newobject->STSD);
				newobject->STSD.Playflag = false;
			}
			 
			
		}
	}
	LeaveCriticalSection(&kk);
}
void cKKetmal::MSG_TURNCHECK_CALL(int _msg_number, SOCKETINFO* _sinfo)
{


	cout << "턴 체크" << endl;
	EnterCriticalSection(&kk);
	strcpy(start_roomlist[_sinfo->_roomNumber]->STSD.startword , _sinfo->_d_info._data);
	int pivot = ++start_roomlist[_sinfo->_roomNumber]->s_play_user;
	if (pivot >= start_roomlist[_sinfo->_roomNumber]->s_user_count)
	{
		start_roomlist[_sinfo->_roomNumber]->s_play_user = 0;
		pivot = 0;
	}

	for (int i = 0;i < start_roomlist[_sinfo->_roomNumber]->s_user_count;i++)
	{
		if (pivot == i)
		{
			start_roomlist[_sinfo->_roomNumber]->STSD.Playflag = true;
		}
		else
		{
			start_roomlist[_sinfo->_roomNumber]->STSD.Playflag = false;
		}
		 
		MSG_SEND(start_roomlist[_sinfo->_roomNumber]->User_list[i], (char*)&start_roomlist[_sinfo->_roomNumber]->STSD);
	
	}


	 
	LeaveCriticalSection(&kk);
}
 
void cKKetmal::MSG_END_CALL(int _msg_number, SOCKETINFO* _sinfo)
{
	int pivot = start_roomlist[_sinfo->_roomNumber]->s_play_user;
	 

	for (int i = 0;i < start_roomlist[_sinfo->_roomNumber]->s_user_count;i++)
	{
		if (pivot == i)
		{
			start_roomlist[_sinfo->_roomNumber]->STSD.Playflag = true;
		}
		else
		{
			start_roomlist[_sinfo->_roomNumber]->User_list[i]->_d_info._msg_number = act_end;
			start_roomlist[_sinfo->_roomNumber]->STSD.Playflag = false;
		}

		MSG_SEND(start_roomlist[_sinfo->_roomNumber]->User_list[i], (char*)&start_roomlist[_sinfo->_roomNumber]->STSD);
		
	}
}