#include "cDatabase.h"
cDatabase::cDatabase()
{
	mHead = NULL;
	mTail = NULL;

	mUsercount = 0;
	mMastercount = 0;
	mMenucount = 0;
}
cDatabase::~cDatabase()
{

}
void cDatabase::Db_Parsing(cUser* _user,PACKET_HEAD* _recvdata)
{
	cLog::Server_print(__FUNCTION__, " ");
	switch (_recvdata->mPacket_cmd)
	{
	case PROTO_LOGIN_REQ:
		CheckUserinfo(_user,_recvdata);
		break;
	case PROTO_NEWUSER_REQ:
		InputNewUserData(_recvdata);
		break;
	case PROTO_MENULIST_REQ:
		MenuListreq(_recvdata);
		break;
	case PROTO_USER_ORDER_REQ:
		OrderSet(_recvdata);
		break;
	}
}
void cDatabase::OrderSet(PACKET_HEAD* _recvdata)
{
	PACKET_ORDER* order = (PACKET_ORDER*)_recvdata;
	order->mMasterkey = mMasterkeyArray[order->mOrderMaster];
}
void cDatabase::InputNewUserData(PACKET_HEAD* _recvdata)
{
	cLog::Server_print(__FUNCTION__, " ");
	NODE* newuserinfo = new NODE;
	PACKET_NEWUSER* pnew = (PACKET_NEWUSER*)_recvdata;
	if (pnew->DB_TYPE == USER_TYPE_USER)
	{
		mUsercount++;
	}
	else
	{
		
		mMastercount++;
	}
	memcpy(&newuserinfo->mUserInfo, pnew, sizeof(PACKET_NEWUSER));
	newuserinfo->mNextNode = NULL;

	if (mHead == NULL)
	{
		mHead = newuserinfo;

	}
	else
	{
		mTail->mNextNode = newuserinfo;
	}
	mTail = newuserinfo;
}
void cDatabase::MenuListreq(PACKET_HEAD* _recvdata)
{
	cLog::Server_print(__FUNCTION__," ");
	PACKET_MENULIST* pmlist = (PACKET_MENULIST*)_recvdata;
	memcpy(pmlist->mMenulist, mMenuList, sizeof(pmlist->mMenulist));
	pmlist->mMenucount = mMenucount;
}
void cDatabase::InputMenuData(cUser* _user,char* _recvmenu)
{
	cLog::Server_print(__FUNCTION__, " ");
	for (int i = 0;i < 20;i++)
	{
		if (mMenuChecklist[i] == false)
		{
			strcpy(mMenuList[i], _recvmenu);
			mMenuChecklist[i] = true;
			mMasterkeyArray[i] = _user->getKey();
			break;
		}
	}

	mMenucount++;
	ShowMenulist();
}

void cDatabase::CheckUserinfo(cUser* _user,PACKET_HEAD* _recvdata)
{
	cLog::Server_print(__FUNCTION__, " ");
	NODE* cur = mHead;
	PACKET_LOGIN* plog = (PACKET_LOGIN*)_recvdata;
	while (cur != NULL)
	{
		if (strcmp(cur->mUserInfo.ID, plog->ID) == 0 && cur->mUserInfo.PASSWORD == plog->PASSWORD)
		{
			cLog::Server_print(__FUNCTION__, "LOGIN OK ");
			_recvdata->mPacket_msg = MSG_LOGIN_OK;
			_user->SetUserinfo(&cur->mUserInfo);
			 
			if (cur->mUserInfo.DB_TYPE == USER_TYPE_MASTER)
			{
				InputMenuData(_user ,cur->mUserInfo.MENU);
			}
			
		}
		
		cur = cur->mNextNode;

	}
	if (cur == NULL&&_recvdata->mPacket_msg!=MSG_LOGIN_OK)
	{
	 
		cLog::Server_print(__FUNCTION__, " LOGIN FAIL");
		_recvdata->mPacket_msg = MSG_LOGIN_FAIL;
 
	}

	
}
void cDatabase::ShowMenulist()
{
	cLog::Server_print(__FUNCTION__, " ");
	for (int i = 0;i < mMenucount;i++)
	{
		cout << "menu = " << mMenuList[i] << endl;
		
		
	}
}
void cDatabase::DeleteMenu(int _userkey)
{
	cLog::Server_print(__FUNCTION__, " ");
	for (int i = 0;i < 20;i++)
	{
		if (mMasterkeyArray[i] == _userkey)
		{
			mMenuChecklist[i] = false;
			strcpy(mMenuList[i] ,0);
			mMenucount--;
			break;
		}
	}
}
