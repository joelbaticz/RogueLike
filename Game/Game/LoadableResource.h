#pragma once

#include "Resource.h"

class LoadableResource : public Resource
{
private:

protected:
	std::string resourceFileNamePath;	//Set by the AssetManager
	int			referenceCount;			//Set by the AssetManager
	int			lastUsedForFrameNumber;	//Set by the RenderingEngine

	void Init();
public:
	LoadableResource();
	LoadableResource(std::string resourceFileNamePath);
	~LoadableResource();

	std::string GetResourceFileNamePath();
	void SetResourceFileNamePath(std::string resourceFileNamePath);
	int GetReferenceCount();
	void SetReferenceCount(int value);
	int GetLastUsedForFrameNumber();
	void SetLastUsedForFrameNumber(int value);
};