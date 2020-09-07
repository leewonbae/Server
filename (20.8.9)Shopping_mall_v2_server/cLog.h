#pragma once
#include <stdarg.h>
class cLog
{
public:
	static void Print_log(const char* funcname,int usernum,const char* fmf,...)
	{
		SYSTEMTIME SystemTime;
	 
		va_list va;
		va_start(va, fmf);
		GetLocalTime(&SystemTime);
		//언제
		printf("[ %d-%d-%d %d시 %d분 %d초 ] ",
			SystemTime.wYear,
			SystemTime.wMonth,
			SystemTime.wDay,
			SystemTime.wHour,
			SystemTime.wMinute,
			SystemTime.wSecond);
		// 어디서
		printf("[FUNCTION] : %s", funcname);
		// 누가
		printf("\t [Userkey Num] = %d", usernum);
		// 무엇을 
		printf("\t [msg] = ");
		vprintf(fmf, va);
		
		printf("\n");
		va_end(va);
	}
};