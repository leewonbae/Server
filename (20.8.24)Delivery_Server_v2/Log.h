#pragma once
#include "Resource.h"

class cLog
{
public:
	//데이터 흐름 용
	static void Server_print(const char* _func, const char* fmf,...)
	{
		SYSTEMTIME st;
		GetLocalTime(&st);

		printf("[TIME = %d_%d_%d, %d: %d: %d] ,",
			st.wYear,
			st.wMonth,
			st.wDay,
			st.wHour,
			st.wMinute,
			st.wSecond);
		printf("[FUNCTION = %s] ,", _func);

		 

		va_list vl;
		va_start(vl, fmf);

		printf("[MSG  = %s]", fmf);

		va_end(vl);
		cout << endl;

	}
	// 세션 용 
	static void Session_print(int _sessionkey)
	{
		 
		printf("[SessionKey = %d]", _sessionkey);
		cout << endl;
	}
};