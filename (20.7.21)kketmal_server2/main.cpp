#include "cKKetmal.h"

int main()
{
	 


	cKKetmal kk;
	kk.InitServer();
	kk.MakeThread();
	while (1)
	{
		kk.ServerAccept();
	}
	return 0;
}