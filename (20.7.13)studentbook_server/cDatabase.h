#pragma once
#include "resource.h"
class cDatabase
{
public:
	cDatabase();
	~cDatabase();
	void SaveFile(PACKET_STUDENTBOOK _pbook);
	// �����͸� ��������� 
	PACKET_STUDENTBOOK getFileData(char* _filename);
	void ShowFileList();
private:
	int mDataCount;
	char* mSaveDataName[10];
	FILE* mFp;
};

