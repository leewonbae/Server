#include "cUserDBA.h"
cUserDBA::cUserDBA()
{

}
cUserDBA::~cUserDBA()
{

}
// 회원가입
void cUserDBA::InputUserInfo(PACKET_HEAD* _phead, cSession* _session)
{
	mCS_userDba.lock();
	bool check = cMySQL::InputUserData((PACKET_LOGIN*)_phead);
	mCS_userDba.Unlock();
	if (check==true)
	{
		_phead->mMsg = MSG_NEWUSER_OK;
		
	}
	else/// 중복된 데이터가 있다는 뜻
	{
		_phead->mMsg = MSG_NEWUSER_FAIL;

	}

	

}



// 로그인

void cUserDBA::CheckUserLogin(PACKET_HEAD* _phead, cSession* _session)
{
	 


	if (cMySQL::CheckUserInfo((PACKET_LOGIN*)_phead ,(cUser*)_session))
	{
		_phead->mMsg = MSG_LOGIN_OK;

	}
	else// 아이디나 비번이 다를경우
	{
		_phead->mMsg = MSG_LOGIN_FAIL;

	}

	 
	 
}