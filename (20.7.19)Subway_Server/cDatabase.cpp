#include "cDatabase.h"


cDatabase::cDatabase()
{
	m_Head = NULL;
	m_Tail = NULL;
}


cDatabase::~cDatabase()
{

}



void cDatabase::InsertNode(Node* _ptr)
{
	if (m_Head == NULL)
	{
		m_Head = _ptr;
		m_Tail = _ptr;
	}
	else
	{
		m_Tail->m_Nextnode = _ptr;
		_ptr->m_Prevnode = m_Tail;
		m_Tail = _ptr;
	}
}


int cDatabase::FindDataBase(PACKET_USERINFO* _ptr)
{
	Node* cur = m_Head;
	
	if (m_Head == NULL)
	{
		return FIND_DATABASE_ERROR;
	}
	if (strcmp(cur->m_Userinfo.mName, _ptr->mName) == 0 && cur->m_Userinfo.mPassword == _ptr->mPassword)
	{
		return cur->m_Userinfo.mMoney;

	}
	else
	{
		return FIND_PASSWORD_ERROR;
	}
	
	while (cur->m_Nextnode != NULL)
	{
		cur = cur->m_Nextnode;
		if (strcmp(cur->m_Userinfo.mName, _ptr->mName) == 0 && cur->m_Userinfo.mPassword == _ptr->mPassword)
		{
			return cur->m_Userinfo.mMoney;
		}
		else
			return FIND_PASSWORD_ERROR;


	}
	return FIND_DATABASE_ERROR;

}
int cDatabase::PaymentMoney(PACKET_USERINFO* _ptr)
{
	Node* recur = m_Head;


	if (strcmp(recur->m_Userinfo.mName, _ptr->mName) == 0)
	{
		recur->m_Userinfo.mMoney -= _ptr->mMoney;
		if (recur->m_Userinfo.mMoney < 0)
		{
			return -1;
		}
	}

	while (recur->m_Nextnode != NULL)
	{
		recur = recur->m_Nextnode;

		if (strcmp(recur->m_Userinfo.mName, _ptr->mName) == 0)
		{
			recur->m_Userinfo.mMoney -= _ptr->mMoney;
			if (recur->m_Userinfo.mMoney < 0)
			{
				return -1;
			}
		}

	}
	return recur->m_Userinfo.mMoney;
}
void cDatabase::RechargeMoney(PACKET_USERINFO* _ptr)
{
	Node* recur = m_Head;
	
	
	if (strcmp(recur->m_Userinfo.mName, _ptr->mName) == 0)
	{
		recur->m_Userinfo.mMoney += _ptr->mMoney;
	}
	
	while (recur->m_Nextnode!=NULL)
	{
		recur = recur->m_Nextnode;
		
		if (strcmp(recur->m_Userinfo.mName, _ptr->mName) == 0)
		{
			recur->m_Userinfo.mMoney += _ptr->mMoney;
		}

	}

}
void cDatabase::ShowData()
{
	Node* cur = m_Head;

	cout << cur->m_Userinfo.mName << endl;
	while (cur->m_Nextnode != NULL)
	{
		cur = cur->m_Nextnode;
		
		cout << cur->m_Userinfo.mName << endl;


	}
}

