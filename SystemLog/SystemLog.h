#ifndef __SYSTEMLOG__H__
#define __SYSTEMLOG__H__

namespace a
{
	class CSystemLog
	{
	private :
		enum e_LEVEL{
			e_LEVEL_DEBUG,
			e_LEVEL_WARING,
			e_LEVEL_ERROR,
			e_LEVEL_SYSTEM
		};

	public :
		CSystemLog();
		virtual ~CSystemLog();

		bool SetLog();
		bool SetLogDirectory();

		bool Log();

		void PrintToHex();
		void PrintToSessionKey64();

	private :
		BYTE _byLogLevel;
		WCHAR* _wcLogDir;

		WCHAR wLogBuffer[256];
	};
}

#endif