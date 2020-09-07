#include "cLoanDB.h"
cLoanDB::cLoanDB()
{
	mLoanCount = 0;
}
cLoanDB::~cLoanDB()
{

}
void cLoanDB::AddLoan(PACKET_ADDLOAN* _addloan)
{
	mLoanCount += 1;
	for (int i = 0;i < mLoanCount;i++)
	{
		if (mLoanCheck[i] == false)
		{
			cout << _addloan->mTitle << endl;
			strcpy(mLoansort[i].mTitle, _addloan->mTitle);
			
			mLoansort[i].mCount = _addloan->mAddCount;
			mLoanCheck[i] = true;
			
			break;
		}
	}
}
void cLoanDB::BuyLoan(PACKET_BUYLOAN _buyloan)
{
	mLoansort[_buyloan.mSortNum].mCount -= _buyloan.mBuyCount;
	if (mLoansort[_buyloan.mSortNum].mCount <= 0)
	{
		mLoanCheck[_buyloan.mSortNum] = false;
		memset(&mLoansort[_buyloan.mSortNum], 0, sizeof(LOAN));
		mLoanCount-=1;
	}
}

int cLoanDB::getLoancount()
{
	return mLoanCount;
}
LOAN* cLoanDB::getLoanArray()
{
	return mLoansort;
}