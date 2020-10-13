#include "cUser.h"
cUser::cUser()
{
	Partner = NULL;
	mWaiting_Mode = false;
	mMap.insert(std::map<int, fp>::value_type(PTC_LOGIN_REQ, &cUser::PTC_LOGIN));
	mMap.insert(std::map<int, fp>::value_type(PTC_MATCHING_REQ, &cUser::PTC_MATCHING));
	mMap.insert(std::map<int, fp>::value_type(PTC_GAMEINFO_REQ, &cUser::PTC_GAMEINFO));
	mMap.insert(std::map<int, fp>::value_type(PTC_RESULT_SAVE_REQ, &cUser::PTC_RESULT_SAVE));
}
cUser::~cUser()
{
	
}
int cUser::getSaveIndex()
{
	return mSaveindex;
}
int cUser::getHavePoint()
{
	return mHavePoint;
}
int cUser::getWaiting()
{
	return mWaiting_Mode;
}
cUser* cUser::getPartner()
{
	return Partner;
}
void cUser::SetWaiting(bool _check)
{
	mWaiting_Mode = _check;
}
void cUser::SetMatchingPartner(cUser* _user)
{
	
	Partner = _user;
	
}
void cUser::SetInfo(char* _id, int _password, int _havePoint, int _msaveindex)
{
	strcpy(ID, _id);
	Password = _password;
	mHavePoint = _havePoint;
	mSaveindex = _msaveindex;
}

void cUser::SetChangePoint(int _havePoint)
{
	
	mHavePoint = _havePoint;
}
void cUser::Parsing(PACKET_HEAD* _phead)
{
	 
	PACKET_HEAD* m_Packet = _phead;

	fp	Temp;

	mIter = mMap.find(_phead->mCmd);

	if (mIter != mMap.end())
	{
		Temp = mIter->second;
		(this->*Temp)(_phead);
	}
}
 
void cUser::PTC_LOGIN(PACKET_HEAD* _phead)
{
	PACKET_LOGIN* plognin = (PACKET_LOGIN*)_phead;
	OnSend(plognin, plognin->mPacket_size);
}
void cUser::PTC_MATCHING(PACKET_HEAD* _phead)
{
	PACKET_MATCHING* pmatch = (PACKET_MATCHING*)_phead;
	OnSend(pmatch, pmatch->mPacket_size);
}
 
void cUser::PTC_RESULT_SAVE(PACKET_HEAD* _phead)
{
	PACKET_RESULT* presult = (PACKET_RESULT*)_phead;
	OnSend(presult, presult->mPacket_size);
}
void cUser::PTC_GAMEINFO(PACKET_HEAD* _phead)
{
	PACKET_GAMEINFO* pgame = (PACKET_GAMEINFO*)_phead;
	if (this->getPartner() == NULL)
	{
		pgame->mPacket_msg = MSG_GAMEINFO_FAIL;
		
		OnSend(pgame, pgame->mPacket_size);
	}
	else
	{
		pgame->mPacket_msg = MSG_GAMEINFO_OK;
		OnSend(pgame, pgame->mPacket_size);
		cUser* partner = this->getPartner();
		partner->OnSend(pgame, pgame->mPacket_size);

	}
}