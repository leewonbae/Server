#include "cUser.h"

cUser::cUser() 
{
	mFmap.insert(map<int, fp>::value_type(MSG_NEW_USER_REQ, &cUser::MSG_NEW_USER));
	mFmap.insert(map<int, fp>::value_type(MSG_CHECK_USER_REQ, &cUser::MSG_CHECK_USER));
	mFmap.insert(map<int, fp>::value_type(MSG_CHECK_VERSION_REQ, &cUser::MSG_CHECK_VERSION));
	mFmap.insert(map<int, fp>::value_type(MSG_NEW_VERSION_REQ, &cUser::MSG_NEW_VERSION));
	mFmap.insert(map<int, fp>::value_type(MSG_PAYMENT_REQ, &cUser::MSG_PAYMENT));
	mFmap.insert(map<int, fp>::value_type(MSG_RECHARGE_REQ, &cUser::MSG_RECHARGE));
}
 
cUser::~cUser()
{

}

void cUser::Parsing(SOCKETINFO* _ptr)
{
	 
	cout << "parsing" << endl;
	PACKET_HEAD phead;
	memcpy(&phead, _ptr->mDatabuf, sizeof(phead));
	cout << "head  = " << phead.mCmd << endl;
	fp	Temp;
	iter = mFmap.find(phead.mCmd);

	 
	Temp = iter->second;
	(this->*Temp)(_ptr);
 
	
}
void cUser::MSG_NEW_USER(SOCKETINFO* _ptr)
{
	cout << "ȸ�� ����" << endl;
	
	PACKET_USERINFO puser;
	memcpy(&puser, _ptr->mDatabuf + sizeof(PACKET_HEAD), sizeof(PACKET_USERINFO));
	cout << puser.mName << endl;
	cout << puser.mPassword << endl;


	Node* newnode = new Node;
	memcpy(newnode->m_Userinfo.mName, puser.mName, sizeof(puser.mName));
	newnode->m_Userinfo.mPassword = puser.mPassword;
	newnode->m_Userinfo.mMoney = 0;
	newnode->m_Nextnode = NULL;

	m_cData.InsertNode(newnode);
	ZeroMemory(&_ptr->mOver, sizeof(_ptr->mOver));
	ZeroMemory(&_ptr->mWbuf, sizeof(_ptr->mWbuf));
 
	OnSend(_ptr);
}
void cUser::MSG_CHECK_USER(SOCKETINFO* _ptr)
{
	int temp;
	cout << "���� Ȯ��" << endl;
	
	PACKET_USERINFO puser;
	memcpy(&puser, _ptr->mDatabuf + sizeof(PACKET_HEAD), sizeof(PACKET_USERINFO));
	temp=m_cData.FindDataBase(&puser);
	cout << "test - -  temp" << temp << endl;
	
	PACKET_USER_CHECK pusercheck;
	switch (temp)
	{
	case FIND_PASSWORD_ERROR:
	case FIND_DATABASE_ERROR:
		pusercheck.mCheck = -1;
		
		break;
	 
	default:
		pusercheck.mCheck = temp;
		break;
	}
	memcpy(_ptr->mDatabuf + sizeof(PACKET_HEAD), &pusercheck, sizeof(PACKET_USER_CHECK));
	OnSend(_ptr);
	 
}
void cUser::MSG_CHECK_VERSION(SOCKETINFO* _ptr)
{
	cout << "���� üũ ��û" << endl;
	mTextfile = fopen("textfile.txt", "r");
	PACKET_VERSION pver;
	
	int idata;
	fscanf(mTextfile, "%d", &idata);
	cout << idata << endl;
	pver.mVersion = idata;

	
	fclose(mTextfile);
	memcpy(_ptr->mDatabuf + sizeof(PACKET_HEAD), &pver, sizeof(PACKET_VERSION));
	OnSend(_ptr);
	 
}
void cUser::MSG_NEW_VERSION(SOCKETINFO* _ptr)
{
	PACKET_FILE pfile;
	cout << "���ο� ���� ���� ��û" << endl;
	mTextfile = fopen("textfile.txt", "rb");
	fseek(mTextfile, 0L, SEEK_END);
	pfile.Fbytes = ftell(mTextfile);
	fseek(mTextfile, 0L, SEEK_SET);
	fread(pfile.Fdata, 1, pfile.Fbytes, mTextfile);
	cout << "���� ����Ʈ" << pfile.Fbytes << endl;
	fclose(mTextfile);



	memcpy(_ptr->mDatabuf + sizeof(PACKET_HEAD), &pfile, sizeof(PACKET_FILE));
	OnSend(_ptr);
}
void cUser::MSG_PAYMENT(SOCKETINFO* _ptr)
{
	int result;
	cout << "���� ��û " << endl;
	PACKET_USERINFO puser;
	memset(&puser, 0, sizeof(PACKET_USERINFO));
	memcpy(&puser, _ptr->mDatabuf + sizeof(PACKET_HEAD), sizeof(PACKET_USERINFO));
	result=m_cData.PaymentMoney(&puser);
	cout << "���� �ϰ� ���� �ݾ� = = " << result << endl;
	puser.mMoney = result;
	memcpy(_ptr->mDatabuf + sizeof(PACKET_HEAD) , &puser, sizeof(PACKET_USERINFO));
	OnSend(_ptr);
	// ���� ���̵� Ȯ���� �� ������ �Ӵ� ���� 
}
void cUser::MSG_RECHARGE(SOCKETINFO* _ptr)
{
	
	cout << "���� ��� ���� " << endl;

	PACKET_USERINFO puser;
	memset(&puser, 0, sizeof(PACKET_USERINFO));
	memcpy(&puser, _ptr->mDatabuf + sizeof(PACKET_HEAD), sizeof(PACKET_USERINFO));
	m_cData.RechargeMoney(&puser);
	
	cout << "���� ��� ����" << endl;
	OnSend(_ptr);
}