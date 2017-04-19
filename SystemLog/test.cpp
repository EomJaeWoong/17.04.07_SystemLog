// SystemLog.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	LOG_SET(LOG::FILE | LOG::CONSOLE, LOG::LEVEL_DEBUG);

	for (int iCnt = 0; iCnt < 100; iCnt++)
	{
		LOG(L"Battle", LOG::LEVEL_DEBUG, L"%d %s", iCnt, L"debug");
		LOG(L"Battle", LOG::LEVEL_WARNING, L"%d %s", iCnt, L"warning");
		LOG(L"Battle", LOG::LEVEL_ERROR, L"%d %s", iCnt, L"error");
	}
	return 0;
}

