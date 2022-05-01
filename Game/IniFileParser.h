#pragma once

#include <string>
#include <unordered_map>

class IniFileParser
{
private:
	std::unordered_map<std::string, std::string> m_PropertyValues;

public:
	IniFileParser();
	~IniFileParser();

	void OpenFile(std::string);

	bool IsPropertyExist(std::string propertyName);
	std::string GetString(std::string propertyName);
	int GetInt(std::string propertyName);
};