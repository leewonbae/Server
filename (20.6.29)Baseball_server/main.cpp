#include "cBaseball.h"
#include "cIOCP.h"
int main()
{
	cBaseball cb;
	
	if (cb.Init_server())
	{
		cout << "���� �ʱ�ȭ ok" << endl;
	}
	if (!cb.MakeThread())
	{
		cout << "thread ���� ����" << endl;
	}
	while (1)
	{
		cb.IOCP_controller();
	}

	return 0;
}