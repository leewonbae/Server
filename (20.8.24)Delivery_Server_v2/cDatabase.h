#pragma once
#include "Packet.h"
#include "Resource.h"
#include "cUser.h"
#include "Log.h"
struct NODE {
	PACKET_NEWUSER mUserInfo;
	NODE* mNextNode;
};
class cDatabase
{
public:
	cDatabase();
	~cDatabase();
	
	void Db_Parsing(cUser* _user, PACKET_HEAD* _recvdata);
	void InputNewUserData(PACKET_HEAD* _recvdata);
	void InputMenuData(cUser* _user,char* _recvmenu);
	void MenuListreq(PACKET_HEAD* _recvdata);
	void DeleteMenu(int _userkey);
	void CheckUserinfo(cUser* _user,PACKET_HEAD* _recvdata);
	void ShowMenulist();
	void OrderSet(PACKET_HEAD* _recvdata);

private:
	NODE* mHead;
	NODE* mTail;

	int mUsercount;
	int mMastercount;
	char mMenuList[20][20] = {0,};
	bool mMenuChecklist[20] = { false, };
	int mMasterkeyArray[20];
	int mMenucount;


};

