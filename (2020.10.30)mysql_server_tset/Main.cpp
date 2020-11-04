#include "Resource.h"
#include "cThread.h"
#include "cServer.h"
#include "cMySQL.h"
int main()
{
	cMySQL mysql;
	cThread thread;

	mysql.DB_connect();
	thread.MakeThread();
	thread.PlayAccept();
	return 0;
}