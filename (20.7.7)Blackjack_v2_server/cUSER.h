#pragma once

#include "resouce.h"
#include "cDATABASE.h"
#include "cSession.h"
#include "cROOM.h"
#include "cCARD.h"
#include "cIOCP.h"
struct PLAYROOM {
	int mUserCount;
	cSession** mUserArray;
	cCARD mCardDumy;
	PACKET_CARD mServerCard;
	int mStandCount = 0;
	int mNoRestartCount = 0;
};
class cUSER : public cIOCP

{

public:
	cUSER();
	~cUSER();
	typedef void (cUSER:: *fp)(OVERDATA* _over);
	virtual void Parsing(int _packetCmd, OVERDATA* _over);

private:
	
	void	MSG_LOGIN(OVERDATA* _over);
	void	MSG_NEWUSER(OVERDATA* _over);
	void	MSG_ROOMLIST(OVERDATA* _over);
	void	MSG_MAKEROOM(OVERDATA* _over);
	void	MSG_ENTERROOM(OVERDATA* _over);
	void	MSG_OUTROOM(OVERDATA* _over);
	void	MSG_PLAER_READY(OVERDATA* _over);
	void	MSG_HIT(OVERDATA* _over);
	void	MSG_STAND(OVERDATA* _over);
	void	MSG_RESULT(OVERDATA* _over);
	void	MSG_REGAME(OVERDATA* _over);

	 
	PACKET_HEAD phead;
	char mSendBuf[BUFFER_SIZE];
	PLAYROOM* mPlayRoomLIst[10];
	int mPlayRoomNumber;
	int mRoomNumber;
	cRoom* mRoomArray[6];
	bool mRoomStartFleg[6] = {false,};
	cSession** mUserArray;
	//cSession* mCsession;
	cDATABASE mCdatabase;
	map<int, fp> mFmap;
	map<int, fp>::iterator iter;
};

