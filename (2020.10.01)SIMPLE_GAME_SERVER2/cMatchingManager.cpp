#include "cMatchingManager.h"
cMatchingManager::cMatchingManager()
{
	mWaitingUserCount = 0;
}
cMatchingManager::~cMatchingManager()
{
	
}
void cMatchingManager::Matching_Parsing(PACKET_HEAD* _packet, cUser* _user)
{
	PACKET_MATCHING* pmatch = (PACKET_MATCHING*)_packet;
	cLog::Print_log("Matching_Parsing");
	if (pmatch->CheckReq == true) // start matching
	{
		Matching(_packet,_user);
		
	}
	else// matching cancle
	{
		CancleMatching(_packet,_user);
	}
}
void cMatchingManager::Matching(PACKET_HEAD* _packet, cUser* _user)
{
	PACKET_MATCHING* pmatch = (PACKET_MATCHING*)_packet;
	if (mWaitList.empty())
	{
		mCS_Match.LockCs();
		mWaitList.push_back(_user);
		_user->SetWaiting(true);
		mWaitingUserCount++;
		pmatch->mPacket_msg = MSG_START_WAITING;
		mCS_Match.UnLock();
	}
	else
	{
		
		mCS_Match.LockCs();
		pmatch->mPacket_msg = MSG_MATCH_OK;
		cUser* temp = mWaitList.front();
		temp->SetWaiting(false);
		temp->SetMatchingPartner(_user);
		_user->SetMatchingPartner(temp);
		temp->OnSend((void*)pmatch, pmatch->mPacket_size);

		mWaitList.pop_front();
		mWaitingUserCount--;
		mCS_Match.UnLock();
		
	}
	ShowWaitingCount();
}
void cMatchingManager::CancleMatching(PACKET_HEAD* _packet, cUser* _user)
{

	if (!mWaitList.empty())
	{
		mCS_Match.LockCs();
		list<cUser*>::iterator iter;
		iter = find(mWaitList.begin(), mWaitList.end(), _user);
		mWaitList.erase(iter);
		_user->SetWaiting(false);
		_packet->mPacket_msg = MSG_CANCLE_OK;
		mCS_Match.UnLock();
	}
	ShowWaitingCount();
}

void cMatchingManager::ShowWaitingCount()
{
	cout << "[Waiting Count ] = " << mWaitingUserCount << endl;
}