// SystemLog.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.

#include "stdafx.h"

CSystemLog *CSystemLog::_pSystemLog = NULL;
__int64 CSystemLog::_iLogCnt = 0;
char CSystemLog::_byLogMode = CONSOLE;
char CSystemLog::_wLogBuffer[256] = { 0, };

CSystemLog *SystemLog = CSystemLog::GetInstance();

int _tmain(int argc, _TCHAR* argv[])
{
	for (int iCnt = 0; iCnt < 100; iCnt++)
	{
		LOG("Battle", LEVEL_ERROR, "adsflkdsfajlkdsf");
		LOG("Battle", LEVEL_DEBUG, "asdfadsf");
		//Sleep(rand() % 2000);
	}

	return 0;
}

