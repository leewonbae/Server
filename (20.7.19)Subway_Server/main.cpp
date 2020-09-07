#include "resource.h"
#include "cUser.h"
int main()
{
	cUser user;
	user.InitServer();
	user.MakeThread();
	user.AcceptClient();
	
	return 0;
}