#include "LogEngine.h"

std::string	LogEngine::s_ComponentName;
int	LogEngine::s_FilterFlags;

//Hidden Constructor - won't be called - since it's static (no instantiation)
LogEngine::LogEngine()
{
	Log(LOG_TRACE, s_ComponentName, "Constructor called.");
}

//Hidden Desctructor - won't be called - since it's static (no instantiation)
LogEngine::~LogEngine()
{
	Log(LOG_TRACE, s_ComponentName, "Destructor called.");
}

int LogEngine::Init(int flags)
{
	//Log GameEngine Init without LogEngine
	s_ComponentName = "LogEngine";
	s_FilterFlags = flags;

	Log(LOG_TRACE, s_ComponentName, "Init() called.");
	
	//Log init was OK;
	LogEngine::Log(LOG_TRACE, s_ComponentName, "Init()...OK.");

	return 0;
}

void LogEngine::UnInit()
{
	LogEngine::Log(LOG_TRACE, s_ComponentName, "UnInit...OK.");
}

void LogEngine::Log(int flagsLogType, std::string strSystemName, std::string strMessage)
{
	if (s_FilterFlags & flagsLogType)
	{
		if (flagsLogType == LOG_TRACE) std::cout << "[TRACE] - ";
		if (flagsLogType == LOG_DEBUG) std::cout << "[DEBUG] - ";
		if (flagsLogType == LOG_ERROR) std::cout << "[ERROR] - ";
		
		if (strSystemName != "") std::cout << strSystemName << ": ";
		std::cout << strMessage << std::endl;
	}
}

void LogEngine::SetFilterFlags(int flags)
{
	s_FilterFlags = flags;
}