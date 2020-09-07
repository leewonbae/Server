#pragma once
#include "resouce.h"

class cCARD
{
public:
	cCARD();
	~cCARD();
	void MakeCard();
	void ShowCard();
	PACKET_CARD PopCard(int _cardcount);
private:
	int mRandomNum;
	bool mCardSort;
	char mCharCard[16];
	int mIntCard[36];
	int mCardCheck[52] = { 0, };
	int mUseCount;
};

