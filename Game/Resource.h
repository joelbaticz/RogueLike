#pragma once

#include <string>

class Resource
{
private:

protected:
	int			resourceId;		// Set by AssetManager
	std::string resourceName;	// Set by AssetManager

public:
	Resource();
	Resource(std::string resourceName);
	~Resource();

	int GetResourceId();
	void SetResourceId(int resourceId);
	std::string GetResourceName();
	void SetResourceName(std::string resourceName);
};