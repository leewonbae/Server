#include "Resource.h"
#include "cThread.h"

int main()
{
	cThread thread;
	thread.MakeThread();
	thread.StartServer();

	return 0;
}