#include "cBaseball.h"
#include "cIOCP.h"
int main()
{
	cBaseball cb;
	
	if (cb.Init_server())
	{
		cout << "서버 초기화 ok" << endl;
	}
	if (!cb.MakeThread())
	{
		cout << "thread 생성 실패" << endl;
	}
	while (1)
	{
		cb.IOCP_controller();
	}

	return 0;
}