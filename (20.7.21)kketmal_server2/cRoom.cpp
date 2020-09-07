#include "cRoom.h"
cRoom::cRoom()
{
	bm_StartFlag = false;
	m_Usercount = 0;
	m_PlayCount = 0;
}
cRoom::~cRoom()
{
	
}
int cRoom::GetUserCount()
{
	return m_Usercount;
}
bool cRoom::GetStartflag()
{
	return bm_StartFlag;
}
void cRoom::ShowRoomInfo()
{
	cout << "m_Usercount	=	" << m_Usercount << endl;
}
void cRoom::InputUser(SOCKETINFO* _sinfo)
{
	m_UserList[m_Usercount] = _sinfo;
	 
	m_UserReadyList[m_Usercount] = false;
	m_Usercount++;
}
SOCKETINFO** cRoom::GetUSER()
{
		return m_UserList;
}
void cRoom::SetUserReady(SOCKETINFO* _sinfo)
{
	for (int i = 0;i < m_Usercount;i++)
	{
		if (_sinfo == m_UserList[i])
		{
			m_UserReadyList[i] = true;
			cout << "i ¤©¤§ ¿ÀÄÉÀÌ" << i << endl;
		}
	}
}
void cRoom::SetUserReadylistinit( )
{
	for (int i = 0;i < m_Usercount;i++)
	{
		 
		 m_UserReadyList[i] = true;
	 
	}
}
bool cRoom::StartCheck()
{
	 
	for (int i = 0;i < m_Usercount;i++)
	{
		if (m_UserReadyList[i] == false)
		{
			return false;
		}
	}
	return true;
	 
	
}