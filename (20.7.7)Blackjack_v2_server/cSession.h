#pragma once
#include "resouce.h"

class cSession 
{
public:
	cSession();
	~cSession();
	void SetSOCK(SOCKET _sock);
	void SetAddr(SOCKADDR_IN _sockaddr);
	void SetmStartRoomNumber(int _startnum);
	void SetUser(USERDATA* _userdata);
	void SetRoomNum(int _roomnum);
	void InputMoney(int _inputmoney);
	void OutputMoney(int _outputmoney);
	void OnRecv();
	void OnSend(char* _inputdata);
	int getFleg();
	int getStartRoomNumber();
	int getRoomNumber();
	
private:
	OVERDATA mOverdata;
	int mRoomNumber;
	int mStartRoomNumber;
	USERDATA* mUser;
	SOCKET mMYsock;
	SOCKADDR_IN mMYaddr;
	
	
	

};

