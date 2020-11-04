#pragma once
#include "Resource.h"
#include "Packet.h"
#include "cMySQL.h"
#include "cCriticalSection.h"
#include "cUser.h"
class cItemDBA
{
public:
	cItemDBA();
	~cItemDBA();

	void ItemParsing(cUser* _user, PACKET_HEAD* _phead);


private:
	cCriticalSection mCS_ItemDba;
};

