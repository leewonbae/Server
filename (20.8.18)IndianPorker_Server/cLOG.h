#pragma once
#include "resource.h"
class cLOG
{
public:
	static void Print_log(const char* _func,int _userkey ,const char* fmf, ...)
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		printf("[%d-%d-%d , %d . %d. %d]", st.wYear, st.wMonth, st.wDay,
			st.wHour,
			st.wMinute,
			st.wSecond

		);
		printf("  [user key] = %d", _userkey);
		printf("[__function__] = %s , ", _func);
		va_list vl;
		va_start(vl, fmf);
		printf("[MSG] = %s , ", fmf);
		va_end(vl);
		printf("\n");
	}
};

