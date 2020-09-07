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
		//����
		printf("[ %d-%d-%d %d�� %d�� %d�� ] ",
			SystemTime.wYear,
			SystemTime.wMonth,
			SystemTime.wDay,
			SystemTime.wHour,
			SystemTime.wMinute,
			SystemTime.wSecond);
		// ���
		printf("[FUNCTION] : %s", funcname);
		// ����
		printf("\t [Userkey Num] = %d", usernum);
		// ������ 
		printf("\t [msg] = ");
		vprintf(fmf, va);
		
		printf("\n");
		va_end(va);
	}
};