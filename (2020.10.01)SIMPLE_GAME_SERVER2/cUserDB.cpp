#include "cUserDB.h"
cUserDB::cUserDB()
{
	mUserDBCount = 0;
}
cUserDB::~cUserDB()
{

}
void cUserDB::DB_Parsing(PACKET_HEAD* _phead, cSession* _session)
{
	cLog::Print_log("DB_PARSING");
	PACKET_LOGIN* plog = (PACKET_LOGIN*)_phead;
	if (plog->NewUser == true)
	{
		NewUserDB(_phead);
	}
	else
	{
		CheckUserDB(_phead, _session);
	}
}
void cUserDB::NewUserDB(PACKET_HEAD* phead)
{
	PACKET_LOGIN pnew;
	memcpy(&pnew, phead, pnew.mPacket_size);
	cout << pnew.ID << endl;
	cout << pnew.Password << endl;
	bool check = false;
	for (int i = 0; i < mUserList.size();i++)
	{
		if (strcmp(pnew.ID ,  mUserList[i].first.ID)==0)
		{
			check = true;
			break;
		}
	}
	if (check == true)
	{
		 
		phead->mPacket_msg = MSG_NEWUSER_FAIL;
	}
	else
	{
		mDB_CS.LockCs();
		mUserList.push_back(make_pair(pnew, mUserDBCount));
		mScoreVector.push_back(0);
		mUserDBCount++;
		mDB_CS.UnLock();
	 
		phead->mPacket_msg = MSG_NEWUSER_OK;
	}
		 
		 
	 
	
}
void cUserDB::CheckUserDB(PACKET_HEAD* phead, cSession* _session)
{
	PACKET_LOGIN* plogin = (PACKET_LOGIN*)phead;
	bool checklogin = false;
	cout << plogin->ID << endl;
	cout << plogin->Password << endl;
	for (int i = 0;i < mUserList.size();i++)
	{
		if (strcmp(plogin->ID, mUserList[i].first.ID) == 0 &&
			plogin->Password == mUserList[i].first.Password)
		{

			cUser* user = (cUser*)_session;
			mDB_CS.LockCs();
			user->SetInfo(plogin->ID, plogin->Password, mScoreVector[mUserList[i].second], mUserList[i].second);
			mDB_CS.UnLock();
			
			
			ShowData(mUserList[i].first, mScoreVector[mUserList[i].second]);
			 
			phead->mPacket_msg = MSG_LOGIN_OK;
			checklogin = true;
			break;
		}
	}
	if (checklogin == false)
	{
		 
		phead->mPacket_msg = MSG_LOGIN_FAIL;
	}
	
}
void cUserDB::ChangeScroe(PACKET_HEAD* phead, cSession* _session)
{
	mDB_CS.LockCs();
	PACKET_RESULT* presult = (PACKET_RESULT*)phead;
	cUser* user = (cUser*)_session;
	int index = user->getSaveIndex();
	if (presult->result == true)
	{
		mScoreVector[index] += 100;
		user->SetChangePoint(mScoreVector[index]);
		
	}
	else
	{
		mScoreVector[index] -= 100;
		user->SetChangePoint(mScoreVector[index]);
	}
	mDB_CS.UnLock();
	phead->mPacket_msg = MSG_RESULT_OK;

}
void cUserDB::ShowData(PACKET_LOGIN plog,int _havescore)
{
	cout << "[ID] =" << plog.ID << " , [PASSWORD] = " << plog.Password ;
	cout << "[HaveScore] =" << _havescore << endl;
}