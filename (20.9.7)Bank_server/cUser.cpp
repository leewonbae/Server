#include "cUser.h"
cUser::cUser()
{
	mMap.insert(std::map<int, fp>::value_type(PTC_LOGIN_REQ, &cUser::PTC_LOGIN));
	mMap.insert(std::map<int, fp>::value_type(PTC_NEWUSER_REQ, &cUser::PTC_NEWUSER));
	mMap.insert(std::map<int, fp>::value_type(PTC_INPUT_MONEY_REQ, &cUser::PTC_INPUT_MONEY));
	mMap.insert(std::map<int, fp>::value_type(PTC_OUTPUT_MONEY_REQ, &cUser::PTC_OUTPUT_MONEY));
	mMap.insert(std::map<int, fp>::value_type(PTC_TRANSFER_MONEY_REQ, &cUser::PTC_TRANSFER_MONEY));

}
cUser::~cUser()
{


}
void cUser::SetUserINFO(USER_INFO* _userinfo)
{
	mUserInfo = _userinfo;
}

void cUser::ActiveCange()
{
	mUserInfo->mActiveCheck = false;
}
void cUser::Paring(PACKET_HEAD* _recvpacket)
{
	fp	Temp;

	mIter = mMap.find(_recvpacket->mCmd);

	if (mIter != mMap.end())
	{
		Temp = mIter->second;
		(this->*Temp)(_recvpacket);
	}
}

void cUser::PTC_LOGIN(PACKET_HEAD* _recvpacket)
{
	cout << "PTC_LOGIN" << endl;
	
	 

	PACKET_LOGIN* plogin = (PACKET_LOGIN*)_recvpacket;

	Onsend((void*)plogin, plogin->mPacket_size);

	 
}
void cUser::PTC_NEWUSER(PACKET_HEAD* _recvpacket)
{
	cout << "PTC_NEWUSER" << endl;
	 
	 

	PACKET_NEWUSER* pnew = (PACKET_NEWUSER*)_recvpacket;
	Onsend((void*)pnew, pnew->mPacket_size);
	 
}
void cUser::PTC_INPUT_MONEY(PACKET_HEAD* _recvpacket)
{
	cout << "PTC_INPUT_MONEY" << endl;
	 
	 

	PACKET_INPUT* pinput = (PACKET_INPUT*)_recvpacket;
	mUserInfo->mMoney += pinput->mInputMoney;
	cout << "현재 금액 = " << mUserInfo->mMoney << endl;
	Onsend((void*)pinput, pinput->mPacket_size);
	 
}
void cUser::PTC_OUTPUT_MONEY(PACKET_HEAD* _recvpacket)
{
	cout << "PTC_OUTPUT_MONEY" << endl;
	 
	 

	PACKET_OUTPUT* poutput = (PACKET_OUTPUT*)_recvpacket;
	mUserInfo->mMoney -= poutput->mOutputMoney;
	cout << "현재 금액 = " << mUserInfo->mMoney << endl;
	Onsend((void*)poutput, poutput->mPacket_size);

 
}
void cUser::PTC_TRANSFER_MONEY(PACKET_HEAD* _recvpacket)
{
	cout << "PTC_TRANSFER_MONEY" << endl;
	 
	 

	PACKET_TRANSFER* ptrans = (PACKET_TRANSFER*)_recvpacket;
	
	Onsend((void*)ptrans, ptrans->mPacket_size);
	 
}