#include "Location.h"

Location::Location()
{
	this->resourceName = "Location";
	this->x = 0;
	this->y = 0;
}

Location::Location(int x, int y)
{
	this->resourceName = "Location";
	this->x = x;
	this->y = y;
}

Location::~Location()
{}

int Location::GetX()
{
	return this->x;
}

void Location::SetX(int value)
{
	this->x = value;
}

int Location::GetY()
{
	return this->y;
}

void Location::SetY(int value)
{
	this->y = value;
}

