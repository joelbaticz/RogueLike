#include "Configuration.h"
#include "IniFileParser.h"
#include <SDL.h>

std::string Configuration::configurationFileName = "config.ini";
std::string Configuration::configurationFileNamePath = "";
std::string Configuration::Version = "";
std::string Configuration::UIPath = "";
int Configuration::WindowX = 100;
int Configuration::WindowY = 100;
int Configuration::WindowWidth = 640;
int Configuration::WindowHeight = 480;
bool Configuration::IsRestart = false;

#ifdef _WIN32
	std::string Configuration::PathSeparator = "\\";
#else
	std::string Configuration::PathSeparator = "/";
#endif

////Specify path seperator based on which platform we are using
//#ifdef _WIN32
//std::string PATH_SEPARATOR = "\\";
//#else
//std::string PATH_SEPARATOR = "/";
//#endif


Configuration::Configuration() = default;
Configuration::~Configuration() = default;

int Configuration::Init()
{
	if (SetConfigurationPath() != 0)
	{
		// Error
		return 1;
	}
	
	IniFileParser* parser = new IniFileParser();
	parser->OpenFile(configurationFileNamePath);

	Version = parser->GetString("Version");
	UIPath = parser->GetString("UIPath");

	WindowX = parser->GetInt("WindowX");
	WindowY = parser->GetInt("WindowY");
	WindowWidth = parser->GetInt("WindowWidth");
	WindowHeight = parser->GetInt("WindowHeight");

	if (WindowX == -1) WindowX = 100;
	if (WindowY == -1) WindowY = 100;
	if (WindowWidth == -1) WindowWidth = 640;
	if (WindowHeight == -1) WindowHeight = 480;

	IsRestart = false;

	return 0;
}

int Configuration::SetConfigurationPath()
{
	static std::string basePath;

	if (basePath.empty())
	{
		basePath = SDL_GetBasePath();

		if (basePath.empty())
		{
			//Error("getResourcePath", SDL_GetError());
			return 1;
		}
		else
		{
			int pos = basePath.rfind("bin");
			basePath = basePath.substr(0, pos);
		}
	}

	configurationFileNamePath = basePath + PathSeparator + configurationFileName;

	return 0;
}

