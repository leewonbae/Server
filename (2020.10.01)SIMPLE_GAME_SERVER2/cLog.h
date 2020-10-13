#pragma once
#include "Resource.h"

class cLog
{
public:
	static void Print_time()
	{
		SYSTEMTIME SystemTime;

		
		GetLocalTime(&SystemTime);
		//언제
		printf("[ %d-%d-%d %d시 %d분 %d초 ] ",
			SystemTime.wYear,
			SystemTime.wMonth,
			SystemTime.wDay,
			SystemTime.wHour,
			SystemTime.wMinute,
			SystemTime.wSecond);
	}
	static void Print_log(const char* fmf, ...)
	{
		Print_time();
		va_list va;
		va_start(va, fmf);
		
		 
		printf("\t [msg] = ");
		vprintf(fmf, va);

		printf("\n");
		va_end(va);
	}
	static void Print_SessionCount(int count)
	{
		Print_time();
		printf("\t [Session Count] = %d\n",count);
	}
	static void Print_UserCount(int count)
	{
		Print_time();
		printf("\t [User Count] = %d\n", count);
	}
};

