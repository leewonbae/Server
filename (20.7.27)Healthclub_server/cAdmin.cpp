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
		cout << "1. 회원 전체 정보 출력" << endl;
		cout << "2. 회원 카운트 출력" << endl;
		cout << "3. 파일 데이터 입력" << endl;
		cout << "4. 공지 사항 올리기" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:
			mDatabase->ShowUserData();
			break;
		case 2:
			usercount = mDatabase->getUserCount();
			cout <<"현재 회원 수는 = " <<usercount <<" 입니다."<< endl;
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
	cout << "제목을 입력해 주시오" << endl;
	cin >> pnotice.mTitle;
	cout << "내용을 입력해 주시오" << endl;
	cin >> pnotice.mData;
	mDatabase->InputData(&pnotice);
}
void cAdmin::MakeNotice()
{
	PAKCET_NOTICE pnotice;
	cout << "제목을 입력해 주시오" << endl;
	cin >> pnotice.mTitle;
	cout << "내용을 입력해 주시오" << endl;
	cin >> pnotice.mData;
	mDatabase->InputNotice(&pnotice);
}