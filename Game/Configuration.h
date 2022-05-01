#pragma once
#include <string>

class Configuration
{
private:
	static std::string configurationFileName;
	static std::string configurationFileNamePath;

	static int Configuration::SetConfigurationPath();

	Configuration();
	~Configuration();
public:
	static int Init();

	static std::string PathSeparator;
	static std::string Version;
	static std::string UIPath;
	static int WindowX;
	static int WindowY;
	static int WindowWidth;
	static int WindowHeight;
	static bool IsRestart;
};
