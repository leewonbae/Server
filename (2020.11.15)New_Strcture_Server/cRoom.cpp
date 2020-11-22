#include "cRoom.h"
cRoom::cRoom()
{
	mReadycount = 0;
	mUserCount = 0;
	mGameCondition = false;
}
cRoom::~cRoom()
{

}

cUser*  cRoom::EnemyUsers(cUser* _user)
{
	if (mUserArray[0] == _user)
	{
		return mUserArray[1];
	}
	else
	{
		return mUserArray[0];
	}
}
void  cRoom::SendGameResult(PACKET_ATTACK* _packet,cUser* _user)
{
	cUser* enemy = EnemyUsers(_user);
	PACKET_GAMESTATE pgame;
	pgame.mGameState = GAMESTATE_END;
	pgame.mGameRoomNum = _user->getRoomNum();
	if (_packet->mRemainHp == 0 && mTemp_packet.mRemainHp == 0)
	{
		pgame.mResult = GAME_RESULT_DRAW;
		enemy->SetGameResult(GAME_RESULT_DRAW);
		BroadMsg(&pgame, pgame.mPacket_size);
	}
	else if (_packet->mRemainHp == 0)
	{
		pgame.mResult = GAME_RESULT_LOSE;
		_user->OnSend(&pgame, pgame.mPacket_size);
		pgame.mResult = GAME_RESULT_WIN;
		enemy->OnSend(&pgame, pgame.mPacket_size);
		_user->SetGameResult(GAME_RESULT_LOSE);
		enemy->SetGameResult(GAME_RESULT_WIN);
	}
	else
	{
		pgame.mResult = GAME_RESULT_WIN;
		_user->OnSend(&pgame, pgame.mPacket_size);
		pgame.mResult = GAME_RESULT_LOSE;
		enemy->OnSend(&pgame, pgame.mPacket_size);
		_user->SetGameResult(GAME_RESULT_WIN);
		enemy->SetGameResult(GAME_RESULT_LOSE);
	}

}
void  cRoom::AttackUsers(PACKET_ATTACK* _packet, cUser* _user)
{
	mCS_ROOM.LOCK();
	mAttackReqCount++;
	
	if (mAttackReqCount ==1)
	{
		memcpy(&mTemp_packet, _packet, sizeof(mTemp_packet.mPacket_size));
	}
	else
	{
		cUser* enemy = EnemyUsers(_user);
		if (_packet->mRemainHp == 0 || mTemp_packet.mRemainHp == 0)
		{
			SendGameResult(_packet, _user);
		}
		else
		{
			_user->OnSend(&mTemp_packet, mTemp_packet.mPacket_size);
			enemy->OnSend(_packet, _packet->mPacket_size);
		}
		
	}

	mCS_ROOM.UN_LOCK();
}
void cRoom::BroadMsg(void* _packet, int _packetsize)
{
	for (int i = 0;i < 2;i++)
	{
		mUserArray[i]->OnSend(_packet, _packetsize);
	}
}
bool cRoom::ReadyUser(cUser* _user)
{
	mCS_ROOM.LOCK();
	mReadycount++;
	if (mUserArray[0] == _user)
	{
		mUserReadyCondition[0] = true;
	}
	else
	{
		mUserReadyCondition[1] = true;
	}
	mCS_ROOM.UN_LOCK();
	if (mReadycount >= 2)
	{
		mUserArray[0]->ClearHp();
		mUserArray[1]->ClearHp();
		mGameCondition = true;
		return true;
	}
	else
	{
		return false;
	}

	

}
void cRoom::OutRoomUser(cUser* _user)
{
	for (int i = 0;i < 2;i++)
	{
		if (mUserArray[i] == _user)
		{
			mCS_ROOM.LOCK();
			if (mUserReadyCondition[i] == true)
			{
				mUserReadyCondition[i] = false;
				mReadycount--;
			}
			mUserArray[i] = NULL;
			mUserCount--;

			mCS_ROOM.UN_LOCK();
		}
	}
}
void cRoom::InputRoomUser(cUser* _user)
{
	for (int i = 0;i < 2;i++)
	{
		if (mUserArray[i] == NULL)
		{
			mCS_ROOM.LOCK();
			mUserArray[i] = _user;
			mUserCount++;
			mCS_ROOM.UN_LOCK();
		}
	}
}