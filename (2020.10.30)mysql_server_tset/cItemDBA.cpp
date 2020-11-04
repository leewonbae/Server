#include "cItemDBA.h"
cItemDBA::cItemDBA()
{

}
cItemDBA::~cItemDBA()
{

}

void cItemDBA::ItemParsing(cUser* _user, PACKET_HEAD* _phead)
{
	cout << "ITEM PARSING START" << endl;
	PACKET_ITEM_UPLOAD* pup = (PACKET_ITEM_UPLOAD*)_phead;
	int DBnumOfuser = _user->getUserNum();
	// 임계영역을 지정하지 않은 이유는 
	// 자신의 num 를 이용하여 아이템의 숫자를 변경 하기 때문에 
	// 그리고 up과 get 이 동시에 일어 나지 않지 때문에 따로 정해 놓지 않음


	if (pup->mUSEandGET == false)// use
	{
		 
		if (cMySQL::Item_Use_Process(pup, DBnumOfuser) == true)
		{
			pup->mMsg = MSG_ITEM_USE_OK;
		}
		else
		{
			pup->mMsg = MSG_ITEM_USE_FAIL;
		}
		 
	}
	else // get
	{
		 
		if (cMySQL::Item_Get_Process(pup, DBnumOfuser) == true)
		{
			pup->mMsg = MSG_ITEM_UPDATE_OK;
		}
		else
		{
			pup->mMsg = MSG_ITEM_UPDATE_FAIL;
		}
		 
	}
 
}