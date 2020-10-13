#pragma once
#include "cSession.h"

class cUser : public cSession
{
public:
	cUser();
	~cUser();
	int getSaveIndex();
	int getHavePoint();
	int getWaiting();
	cUser* getPartner();
	void SetInfo(char* _id, int _password, int _havePoint, int _msaveindex);
	void SetChangePoint(int _havePoint);
	void SetWaiting(bool _check);
	void SetMatchingPartner(cUser* _user);

	typedef void (cUser:: *fp)(PACKET_HEAD* _phead);
	void Parsing(PACKET_HEAD* _phead);


private:
	map<int, fp> mMap;
	map<int, fp>::iterator mIter;

	cUser* Partner;
	void PTC_GAMEINFO(PACKET_HEAD* _phead);
	void PTC_LOGIN(PACKET_HEAD* _phead);
	void PTC_MATCHING(PACKET_HEAD* _phead);
	void PTC_RESULT_SAVE(PACKET_HEAD* _phead);

	bool mWaiting_Mode;
	char ID[20];
	int Password;
	int mHavePoint;
	int mSaveindex;
	
};

