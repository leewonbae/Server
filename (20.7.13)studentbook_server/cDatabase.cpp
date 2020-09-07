#include "cDatabase.h"
cDatabase::cDatabase()
{
	cout << "디비 생성자" << endl;
	mDataCount = 0;
}
cDatabase::~cDatabase()
{

}

void cDatabase::SaveFile(PACKET_STUDENTBOOK _pbook)
{
	char* newname = new char[20];
	memcpy(newname, _pbook.mFileName, sizeof(_pbook.mFileName));
	strcat(_pbook.mFileName, ".txt");
	mSaveDataName[mDataCount] = newname;
	mFp = fopen(_pbook.mFileName, "w");
	fwrite(_pbook.mFile, 1, _pbook.mFilesize, mFp);
	fclose(mFp);
	mDataCount++;
}
PACKET_STUDENTBOOK cDatabase::getFileData(char* _filename)
{
	PACKET_STUDENTBOOK pbook;
	strcat(_filename, ".txt");
	mFp = fopen(_filename, "r");
	fseek(mFp, 0L, SEEK_END);
	pbook.mFilesize= ftell(mFp);
	fseek(mFp, 0L, SEEK_SET);
	fread(pbook.mFile, 1, pbook.mFilesize, mFp);
	fclose(mFp);
	return pbook;
}
void cDatabase::ShowFileList()
{
	for (int i = 0;i < mDataCount;i++)
	{
		cout << mSaveDataName[i] << endl;
	}
}