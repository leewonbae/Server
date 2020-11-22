#pragma once
#include "Resource.h"
#include "Protocol.h"

class cSession
{
public:
	cSession();
	~cSession();

	void OnRecv();
	void OnSend(void* _packet, int _packet_size);
	
	void Upsize(int _size) { mTotalsize += _size; }
	void Downsize(int _size) { mTotalsize -= _size; }
	int getSize() { return mTotalsize; }

	void setMysqlConnection(int _index) { mMysqlConnection = _index; }
	int getMysqlConnection() { return mMysqlConnection; }

	void setAuthority(bool _auth) { mAuthority = _auth; }
	bool getAuth() { return mAuthority; }
	
	void setKey(int _index) { mKey = _index; }
	int getKey() { return mKey; }
	void setSOCK(SOCKET _sock) { mSock = _sock; }

	 
	virtual void Parsing(PACKET_HEAD* _phead) = 0;
private:
	OVERDATA mRecv_Overdata, mSend_Overdata;
	SOCKET mSock;
	char mRecvBuf[BUFFER_SIZE];
	char mSendBuf[BUFFER_SIZE];
	int mKey;
	int mMysqlConnection=0;
	bool mAuthority = false;
	int mTotalsize = 0;
};

