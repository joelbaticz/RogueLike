#include "LoadableResource.h"
#include "TextureAtlas.h"

LoadableResource::LoadableResource()
{
	this->resourceFileNamePath = "";

	Init();
}

LoadableResource::LoadableResource(std::string resourceFileNamePath)
{
	this->resourceFileNamePath = resourceFileNamePath;

	Init();
}

LoadableResource::~LoadableResource()
{
}

void LoadableResource::Init()
{
	this->resourceName = "LoadableResource";
	this->referenceCount = 0;
	this->lastUsedForFrameNumber = 0;
}

std::string LoadableResource::GetResourceFileNamePath()
{
	return this->resourceFileNamePath;
}

void LoadableResource::SetResourceFileNamePath(std::string resourceFileNamePath)
{
	this->resourceFileNamePath = resourceFileNamePath;
}

int LoadableResource::GetReferenceCount()
{
	return this->referenceCount;
}

void LoadableResource::SetReferenceCount(int value)
{
	this->referenceCount = value;
}

int LoadableResource::GetLastUsedForFrameNumber()
{
	return this->lastUsedForFrameNumber;
}

void LoadableResource::SetLastUsedForFrameNumber(int value)
{
	this->lastUsedForFrameNumber = value;
}