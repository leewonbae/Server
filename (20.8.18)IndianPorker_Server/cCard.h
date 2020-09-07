#pragma once
#include "resource.h"
class cCard
{
public :
	cCard();
	~cCard();
	void Initcard();
	int Popcard();
private:
	int mCardDumy[20];
	bool mCheckUse[20] = { false, };
	int mPopcount;
};

