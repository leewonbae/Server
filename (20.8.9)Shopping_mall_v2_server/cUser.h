#pragma once
#include "resource.h"
#include "cSession.h"
#include "cUserDB.h"
#include "cLoanDB.h"

class cUser : public cSession
{
public:
	cUser();
	~cUser();

	typedef void (cUser:: *fp)(OVERLAPPED_DATA* _over);

	void	SetKey(int _keynum);
	void	SetUserDb(cUserDB* _userdb);
	void	SetLoanDb(cLoanDB* _loandb);
	void	Parsing(OVERLAPPED_DATA* _over);
private:
	void	PRO_LOGIN(OVERLAPPED_DATA* _over);
	void	PRO_NEWUSER(OVERLAPPED_DATA* _over);
	void	PRO_LOAN_LIST(OVERLAPPED_DATA* _over);
	void	PRO_ADD_LOAN(OVERLAPPED_DATA* _over);
	void	PRO_BUY_LOAN(OVERLAPPED_DATA* _over);
	 
	cUserDB* mUserDB;
	cLoanDB* mLoanDB;

	char mSendbuf[BUFFER_SIZE];
	int mKey;
	map<int, fp> mMap;
	map<int, fp>::iterator mIter;
};

