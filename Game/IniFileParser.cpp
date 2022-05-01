#include "IniFileParser.h"
#include "LogEngine.h"
#include <string>
#include <fstream>


IniFileParser::IniFileParser()
{

}

IniFileParser::~IniFileParser()
{

}

void IniFileParser::OpenFile(std::string fileNamePath)
{
	int origFlags = LogEngine::GetFilterFlags();
	LogEngine::SetFilterFlags(origFlags | LOG_DEBUG);
	LogEngine::Log(LOG_DEBUG, "IniFileParser", "Opening: " + fileNamePath);
	LogEngine::SetFilterFlags(origFlags);

	std::ifstream input(fileNamePath);

	for (std::string line; std::getline(input, line); )
	{
		int equalSignPos = line.find("=");

		std::string propertyName = line.substr(0, equalSignPos);
		std::string propertyValue = line.substr(equalSignPos + 1, line.length() - equalSignPos - 1);

		m_PropertyValues[propertyName] = propertyValue;
	}
}

bool IniFileParser::IsPropertyExist(std::string propertyName)
{
	std::unordered_map<std::string, std::string>::const_iterator propertyIterator = m_PropertyValues.find(propertyName);

	if (propertyIterator == m_PropertyValues.end())
	{
		return false;
	}

	return true;
}

std::string IniFileParser::GetString(std::string propertyName)
{
	if (IsPropertyExist(propertyName))
	{
		return m_PropertyValues[propertyName];
	}

	return "";
}

int IniFileParser::GetInt(std::string propertyName)
{
	if (IsPropertyExist(propertyName))
	{
		return std::stoi(m_PropertyValues[propertyName]);
	}
	return -1;
}

