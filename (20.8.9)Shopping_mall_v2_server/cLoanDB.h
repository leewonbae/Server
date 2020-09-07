#pragma once
#include "resource.h"

class cLoanDB
{
public:
	cLoanDB();
	~cLoanDB();
	void AddLoan(PACKET_ADDLOAN* _addloan);
	void BuyLoan(PACKET_BUYLOAN _buyloan);
	
	int getLoancount();
	LOAN* getLoanArray();
private:
	LOAN mLoansort[20];
	bool mLoanCheck[20] = { false, };
	int mLoanCount;
};

