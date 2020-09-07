#pragma once
#include "resource.h"


class cDatabase
{
public:
	cDatabase();
	
	~cDatabase();

	 
	void InsertNode(Node* _ptr);
	void ShowData();
	int FindDataBase(PACKET_USERINFO* _ptr);
	void RechargeMoney(PACKET_USERINFO* _ptr);
	int PaymentMoney(PACKET_USERINFO* _ptr);
private:
	Node* m_Head;
	Node* m_Tail;
};

