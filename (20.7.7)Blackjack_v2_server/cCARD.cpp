#include "cCARD.h"
cCARD::cCARD()
{
	mUseCount = 0;
	srand(time(NULL));
	 
	MakeCard();
}
cCARD::~cCARD()
{

}
void cCARD::MakeCard()
{
	int num = 2;
	int discount = 36;
	int temp ;
	for (int i = 0; i < 52;i++)
	{
		temp = i-discount;
		if (i < 36)
		{
			mIntCard[i] = num;
			num++;
			if (num == 11)
			{
				num = 2;
			}
		}
		else
		{
			if (i < 40)
			{
				mCharCard[temp] = 'A';
			}
			else if (i >= 40 && i < 44)
			{
				mCharCard[temp] = 'J';
			}
			else if (i >= 44 && i < 48)
			{
				mCharCard[temp] = 'Q';
			}
			else
			{
				mCharCard[temp] = 'K';
			}
		}

	}
}

void cCARD::ShowCard()
{
	int num = 2;
	int discount = 36;
	int temp;
	
	for (int i = 0;i < 52;i++)
	{ 
		mRandomNum = rand() % 52;
		temp = i-discount;
		cout << mRandomNum << endl;
		if (i < 36)
		{
			cout << mIntCard[i] << endl;
		}
		else
		{
			cout << mCharCard[temp] << endl;
		}
	}
}
PACKET_CARD cCARD::PopCard(int _cardcount)
{
	PACKET_CARD pcard;
	memset(&pcard, 0, sizeof(PACKET_CARD));
	int i = 0;
	int randomNum;
	int discount = 36;
	int temp;
	while (i < _cardcount)
	{
		randomNum = rand() % 52;
		if (mCardCheck[randomNum] == 0)
		{
			cout << "rand = " << randomNum << endl;
			mUseCount++;
			mCardCheck[randomNum] = 1;
			
			if (randomNum < 36)
			{

				pcard.mINTCardArray[pcard.mIntCardCount] = mIntCard[randomNum];
				cout <<"int"<< mIntCard[randomNum] << endl;
				pcard.mIntCardCount++;
			}
			else
			{
				temp = randomNum - discount;
				pcard.mCHARCardArray[pcard.mCharCardCount] = mCharCard[temp];
				cout << "char" << mCharCard[temp] << endl;

				pcard.mCharCardCount++;
			}
			i++;
		}
		else
		{
			continue;
			
		}
	}

	return pcard;
}