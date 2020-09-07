#pragma once
#include "Resource.h"
#include "Log.h"
 
class cInitserver
{
public:
	cInitserver();
	~cInitserver();
	void Init();
	SOCKET Acceptor();
	SOCKET getSock();
	
	
private:
	SOCKET mInitnsock;
	
};

