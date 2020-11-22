#include "cUser.h"
cUser::cUser()
{
	mPacketMap.insert(make_pair(PTC_NEWUSER, &cUser::Newuser_Req));
	mPacketMap.insert(make_pair(PTC_LOGIN, &cUser::Login_Req));
	mPacketMap.insert(make_pair(PTC_MAKEROOM_REQ, &cUser::MAKEROOM_REQ));
	mPacketMap.insert(make_pair(PTC_INOUT_ROOM_REQ, &cUser::INOUT_ROOM_REQ));
	mPacketMap.insert(make_pair(PTC_ROOMLIST_REQ, &cUser::ROOMLIST_REQ));
	mPacketMap.insert(make_pair(PTC_READY_REQ, &cUser::READY_REQ));
}

cUser::~cUser()
{

}
void cUser::SetGameResult(int _result)
{
	switch (_result)
	{
	case GAME_RESULT_DRAW:
		mUserinfo.mGame_info.mDrawCount++;
		break;
	case GAME_RESULT_WIN:
		mUserinfo.mGame_info.mWinCount++;
		break;
	case GAME_RESULT_LOSE:
		mUserinfo.mGame_info.mLoseCount++;
		break;
	}
}
void cUser::Parsing(PACKET_HEAD* _phead)
{
	cout << "parsing" << endl;
	fp	Temp;
	mPacketIter = mPacketMap.find(_phead->mCmd);

	if (mPacketIter != mPacketMap.end())
	{
		Temp = mPacketIter->second;
		(this->*Temp)(_phead);
	}
}
void cUser::Newuser_Req(PACKET_HEAD* _phead)
{
	cout << "Newuser_Req" << endl;
	PACKET_NEWUSER* recvpacket = (PACKET_NEWUSER*)_phead;
	
	OnSend(recvpacket, recvpacket->mPacket_size);
}
void cUser::Login_Req(PACKET_HEAD* _phead)
{
	cout << "Login_Req" << endl;
	PACKET_LOGIN* recvpacket = (PACKET_LOGIN*)_phead;
	
	cout << "show item info" << endl;
	for (int i = 0;i < MAX_ITEM_LIST;i++)
	{
		cout << mUserinfo.mItem_info.mItemArray[i] << endl;
	}


	OnSend(recvpacket, recvpacket->mPacket_size);
}
void cUser::MAKEROOM_REQ(PACKET_HEAD* _phead)
{
	 
}
void cUser::INOUT_ROOM_REQ(PACKET_HEAD* _phead)
{
	 
}
void cUser::ROOMLIST_REQ(PACKET_HEAD* _phead)
{
	 
}
void cUser::READY_REQ(PACKET_HEAD* _phead)
{
	 
}
