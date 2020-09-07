#pragma once
#include "resource.h"
#include "cDatabase.h"
class cAdmin
{
public:
	cAdmin();
	~cAdmin();
	void SetDatabase(cDatabase* _database);
	void AdminMenu();
	void InputData();
	void MakeNotice();
	
private:
	cDatabase* mDatabase;

};

