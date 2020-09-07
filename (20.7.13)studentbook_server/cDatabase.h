#pragma once
#include "resource.h"
class cDatabase
{
public:
	cDatabase();
	~cDatabase();
	void SaveFile(PACKET_STUDENTBOOK _pbook);
	// 데이터를 저장행야지 
	PACKET_STUDENTBOOK getFileData(char* _filename);
	void ShowFileList();
private:
	int mDataCount;
	char* mSaveDataName[10];
	FILE* mFp;
};

