#include "cUserDBA.h"
cUserDBA::cUserDBA()
{

}
cUserDBA::~cUserDBA()
{

}
// ȸ������
void cUserDBA::InputUserInfo(PACKET_HEAD* _phead, cSession* _session)
{
	mCS_userDba.lock();
	bool check = cMySQL::InputUserData((PACKET_LOGIN*)_phead);
	mCS_userDba.Unlock();
	if (check==true)
	{
		_phead->mMsg = MSG_NEWUSER_OK;
		
	}
	else/// �ߺ��� �����Ͱ� �ִٴ� ��
	{
		_phead->mMsg = MSG_NEWUSER_FAIL;

	}

	

}



// �α���

void cUserDBA::CheckUserLogin(PACKET_HEAD* _phead, cSession* _session)
{
	 


	if (cMySQL::CheckUserInfo((PACKET_LOGIN*)_phead ,(cUser*)_session))
	{
		_phead->mMsg = MSG_LOGIN_OK;

	}
	else// ���̵� ����� �ٸ����
	{
		_phead->mMsg = MSG_LOGIN_FAIL;

	}

	 
	 
}