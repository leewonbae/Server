#include "cAdmin.h"
cAdmin::cAdmin()
{

}
cAdmin::~cAdmin()
{

}
void cAdmin::SetDatabase(cDatabase* _database)
{
	mDatabase = _database;
}
void cAdmin::AdminMenu()
{
	int choice;
	int usercount;
	while (1)
	{
		cout << "1. ȸ�� ��ü ���� ���" << endl;
		cout << "2. ȸ�� ī��Ʈ ���" << endl;
		cout << "3. ���� ������ �Է�" << endl;
		cout << "4. ���� ���� �ø���" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:
			mDatabase->ShowUserData();
			break;
		case 2:
			usercount = mDatabase->getUserCount();
			cout <<"���� ȸ�� ���� = " <<usercount <<" �Դϴ�."<< endl;
			break;
		case 3:
			InputData();
			break;
		case 4:
			MakeNotice();
			break;

		}
	}
}
void cAdmin::InputData()
{
	PAKCET_NOTICE pnotice;
	cout << "������ �Է��� �ֽÿ�" << endl;
	cin >> pnotice.mTitle;
	cout << "������ �Է��� �ֽÿ�" << endl;
	cin >> pnotice.mData;
	mDatabase->InputData(&pnotice);
}
void cAdmin::MakeNotice()
{
	PAKCET_NOTICE pnotice;
	cout << "������ �Է��� �ֽÿ�" << endl;
	cin >> pnotice.mTitle;
	cout << "������ �Է��� �ֽÿ�" << endl;
	cin >> pnotice.mData;
	mDatabase->InputNotice(&pnotice);
}