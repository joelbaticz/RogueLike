#include "Resource.h"

Resource::Resource()
{
	this->resourceId = 0;
	this->resourceName = "Resource";
}

Resource::Resource(std::string resourceName)
{
	this->resourceId = 0;
	this->resourceName = resourceName;
}

Resource::~Resource()
{

}

int Resource::GetResourceId()
{
	return this->resourceId;
}

void Resource::SetResourceId(int resourceId)
{
	this->resourceId = resourceId;
}

std::string Resource::GetResourceName()
{
	return this->resourceName;
}

void Resource::SetResourceName(std::string resourceName)
{
	this->resourceName = resourceName;
}