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
	// �Ӱ迵���� �������� ���� ������ 
	// �ڽ��� num �� �̿��Ͽ� �������� ���ڸ� ���� �ϱ� ������ 
	// �׸��� up�� get �� ���ÿ� �Ͼ� ���� ���� ������ ���� ���� ���� ����


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