#pragma once
#include "resource.h"
#include "cUser.h"
#include "cDatabase.h"
#include "cAdmin.h"
class cIOCP
{
public:
	cIOCP();
	~cIOCP();
	void InitServer();
	void MakeThread();
	void MakeHCP();
	void Acceptor();
	void WorkerThread();
	void MakeAdmin();
	void AdminThread();
private:
	cDatabase mDatabase;
	cAdmin mAdmin;
	SOCKET mListenSock;
	HANDLE mHcp;


};

