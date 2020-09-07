#include "cThread.h"
DWORD WINAPI Switchthread(LPVOID arg)
{
	cThread* temp = (cThread*)arg;
	temp->Workerthread();
	return 0;
}
cThread::cThread()
{
	cout << "thread »ı¼ºÀÚ" << endl;
	GetSystemInfo(&mSI);
}
cThread::~cThread()
{

}

void cThread::MakeThread()
{
	

	for (int i = 0;i < (int)mSI.dwNumberOfProcessors;i++)
	{
		CreateThread(NULL, 0, Switchthread, this, 0, NULL);


	}
}