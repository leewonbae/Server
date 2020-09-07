#pragma once
#include "resource.h"
struct NODE {
	char mName[20];
	int mPassword;
	NODE* mNextnode;

};
class cUserDB
{
public:
	cUserDB();
	~cUserDB();
	void InputUserinfo(char* _name, int _password);
	bool CheckDB(char* _name, int _password);
private:
	int mDatacount;
	NODE* mHead;
	NODE* mTail;
};

