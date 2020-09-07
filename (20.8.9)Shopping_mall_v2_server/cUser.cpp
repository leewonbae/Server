#include "cUser.h"
cUser::cUser()
{
	mMap.insert(map<int, fp>::value_type(PRO_LOGIN_REQ, &cUser::PRO_LOGIN));
	mMap.insert(map<int, fp>::value_type(PRO_NEWUSER_REQ, &cUser::PRO_NEWUSER));
	mMap.insert(map<int, fp>::value_type(PRO_LOAN_LIST_REQ, &cUser::PRO_LOAN_LIST));
	mMap.insert(map<int, fp>::value_type(PRO_ADD_LOAN_REQ, &cUser::PRO_ADD_LOAN));
	mMap.insert(map<int, fp>::value_type(PRO_BUY_LOAN_REQ, &cUser::PRO_BUY_LOAN));
}
cUser::~cUser()
{

}

void cUser::Parsing(OVERLAPPED_DATA* _over)
{
	PACKET_HEAD phead;
	memset(&phead, 0, sizeof(PACKET_HEAD));
	memcpy(&phead, _over->mDatabuf, sizeof(PACKET_HEAD));


	fp	Temp;
	mIter = mMap.find(phead.mHeadCmd);


	Temp = mIter->second;
	(this->*Temp)(_over);



}
void cUser::SetKey(int _keynum)
{
	mKey = _keynum;
}
void cUser::SetUserDb(cUserDB* _userdb)
{
	mUserDB = _userdb;
}
void cUser::SetLoanDb(cLoanDB* _loandb)
{
	mLoanDB = _loandb;
}
void cUser::PRO_LOGIN(OVERLAPPED_DATA* _over)
{
	cLog::Print_log(__FUNCTION__,mKey ,"PRO_LOGIN");
	PACKET_LOGIN plogin;
	memset(&plogin, 0, sizeof(PACKET_LOGIN));
	memcpy(&plogin, _over->mDatabuf + sizeof(PACKET_HEAD), sizeof(PACKET_LOGIN));
	
	if (mUserDB->ChecktUserDB(plogin))
	{
		 
		OnSend(MSG_LOGIN_TRUE, mSendbuf);	 
	}
	else 
	{
	 
		OnSend(MSG_LOGIN_FALSE, mSendbuf);
	}
}


void		cUser::PRO_NEWUSER(OVERLAPPED_DATA* _over)
{
	cLog::Print_log(__FUNCTION__, mKey, "PRO_NEWUSER");
	PACKET_NEWUSER pnew;
	memset(&pnew, 0, sizeof(PACKET_NEWUSER));
	memcpy(&pnew, _over->mDatabuf+sizeof(PACKET_HEAD), sizeof(PACKET_NEWUSER));
	mUserDB->InputUserDB(pnew);
	OnSend(MSG_NEWUSER_OK, mSendbuf);
}


void		cUser::PRO_LOAN_LIST(OVERLAPPED_DATA* _over)
{
	cLog::Print_log(__FUNCTION__, mKey, "PRO_LOAN_LIST");
	LOAN* loanarray = mLoanDB->getLoanArray();
	PACKET_LOANLIST ploan;
	memset(&ploan, 0, sizeof(PACKET_LOANLIST));
	memcpy(&ploan.mLoansort, loanarray, sizeof(ploan.mLoansort));
	ploan.mLoancount = mLoanDB->getLoancount();
	memcpy(mSendbuf + sizeof(PACKET_HEAD), &ploan, sizeof(PACKET_LOANLIST));
	
	OnSend(PRO_LOAN_LIST_REQ, mSendbuf);
}


void		cUser::PRO_ADD_LOAN(OVERLAPPED_DATA* _over)
{
	cLog::Print_log(__FUNCTION__, mKey, "PRO_ADD_LOAN");
	PACKET_ADDLOAN padd;
	memset(&padd, 0, sizeof(PACKET_ADDLOAN));
	memcpy(&padd, _over->mDatabuf + sizeof(PACKET_HEAD), sizeof(PACKET_ADDLOAN));

	mLoanDB->AddLoan(&padd);
	OnSend(MSG_ADD_OK, mSendbuf);
}


void		 cUser::PRO_BUY_LOAN(OVERLAPPED_DATA* _over)
{
	cLog::Print_log(__FUNCTION__, mKey, "PRO_BUY_LOAN");
	PACKET_BUYLOAN pbuy;
	memset(&pbuy, 0, sizeof(PACKET_BUYLOAN));
	memcpy(&pbuy, _over->mDatabuf + sizeof(PACKET_HEAD), sizeof(PACKET_BUYLOAN));
	mLoanDB->BuyLoan(pbuy);
	
	OnSend(MSG_BUY_OK, mSendbuf);
}

