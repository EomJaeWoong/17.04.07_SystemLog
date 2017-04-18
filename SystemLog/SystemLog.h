#ifndef __SYSTEMLOG__H__
#define __SYSTEMLOG__H__

#include <time.h>

class CSystemLog
{
public:
	static enum MODE{
		FILE,
		CONSOLE
	};

	static enum LEVEL{
		LEVEL_DEBUG,
		LEVEL_WARNING,
		LEVEL_ERROR,
		LEVEL_SYSTEM
	};

private:
	static CSystemLog *_pSystemLog;

	CSystemLog()
	{
		_iLogCnt = 0;
		_wcLogDir = "/";
		_byLogMode = CONSOLE;

	}
	virtual ~CSystemLog(){}

public:
	static CSystemLog *GetInstance()
	{
		if (NULL == _pSystemLog)
		{
			_pSystemLog = new CSystemLog();
			atexit(Destroy);
		}

		return _pSystemLog;
	}

	static void Destroy()
	{
		delete _pSystemLog;
	}

	bool SetLog(char byLogMode, BYTE byLogLevel){
		_byLogMode = byLogMode;
		_byLogLevel = byLogLevel;
		return true;
	}
	bool SetLogDirectory(char *wLogDirectory){ _wcLogDir = wLogDirectory; }

	static bool Log(char *wCategory, char chLogLevel, char *chLogStr)
	{
		char *wLogLevel = NULL;

		time_t timer;
		tm today;

		time(&timer);

		localtime_s(&today, &timer); // 초 단위의 시간을 분리하여 구조체에 넣기

		switch (chLogLevel)
		{
		case LEVEL_DEBUG:
			wLogLevel = "DEBUG";
			break;
		case LEVEL_WARNING:
			wLogLevel = "WARNG";
			break;
		case LEVEL_ERROR:
			wLogLevel = "ERROR";
			break;
		case LEVEL_SYSTEM:
			wLogLevel = "SYSTM";
			break;
		}

		InterlockedIncrement64((LONG64 *)&_iLogCnt);
		sprintf_s(_wLogBuffer, "[%s] [%04d-%02d-%02d %02d:%02d:%02d / %s] [%08I64d] %s\n",
			wCategory,
			today.tm_year + 1900,
			today.tm_mon + 1,
			today.tm_mday,
			today.tm_hour,
			today.tm_min,
			today.tm_sec,
			wLogLevel,
			_iLogCnt,
			chLogStr);

		switch (_byLogMode)
		{
		case CONSOLE:
			printf("%s", _wLogBuffer);
			break;

		case FILE:
			char fileName[256];
			sprintf_s(fileName, "%d%02d_%s.txt", today.tm_year + 1900, today.tm_mon + 1, wCategory);

			//FILE *fp;
			//fopen_s(&fp, fileName, "a");

			//fwrite(_wLogBuffer, strlen(_wLogBuffer), 1, fp);

			//fclose(fp);
			break;
		}

		return true;
	}

	/*
	void PrintToHex();
	void PrintToSessionKey64();
	*/

private:
	static __int64 _iLogCnt;

	static char _byLogMode;

	char _byLogLevel;
	char* _wcLogDir;

	static char _wLogBuffer[256];
};

#define LOG(chCategory, chLogLevel, chLogStr)		CSystemLog::Log(chCategory, chLogLevel, chLogStr)
#define LOG_SET(chLogLevel)						CSystemLog::SetLog(chLogLevel)

#define CONSOLE									CSystemLog::CONSOLE
#define FILE										CSystemLog::FILE

#define LEVEL_ERROR								CSystemLog::LEVEL_ERROR
#define LEVEL_WARNING								CSystemLog::LEVEL_WARNING
#define LEVEL_DEBUG										CSystemLog::LEVEL_DEBUG

#endif