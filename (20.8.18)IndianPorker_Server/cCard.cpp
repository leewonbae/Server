#include "cCard.h"
cCard::cCard()
{
	Initcard();
	mPopcount = 0;
	srand(time(NULL));
	
}
cCard::~cCard()
{

}
void cCard::Initcard()
{
	int cardnum = 1;
	for (int i = 0;i < 20;i++)
	{
		mCardDumy[i] = cardnum;
		cardnum++;
		if (cardnum == 11)
		{
			cardnum = 1;
		}
	}
	
}
int cCard::Popcard()
{
	while (1)
	{
		int randnum = rand() % 20;
		cout <<"check rand num = "<< randnum << endl;
		if (mCheckUse[randnum] == false)
		{
			mCheckUse[randnum] = true;
			mPopcount++;
			if (mPopcount > 20)
			{
				return -1;
			}
			else
			{
				return mCardDumy[randnum];
			}
			
		}
	}	
}