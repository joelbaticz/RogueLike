#pragma once

#include <iostream>
#include <string>

#define LOG_NONE	0
#define LOG_TRACE	1
#define LOG_DEBUG	2
#define LOG_ERROR	4
#define LOG_ALL		LOG_TRACE | LOG_DEBUG | LOG_ERROR

//Static LogEngine class
class LogEngine
{
private:
	static std::string	s_ComponentName;
	static int			s_FilterFlags;
	
	//Hidden constructor / destructor
	LogEngine();
	~LogEngine();
public:
	static int Init(int filterFlags);
	static void UnInit();
	static void Log(int flagsLogType, std::string strSystemName, std::string strMessage);

	static void SetFilterFlags(int flags);
};


