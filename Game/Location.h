#pragma once

#include "Resource.h"

#define DEFAULT_X		10
#define DEFAULT_Y		10

class Location: public Resource
{
private:
	int	x;
	int	y;
public:
	Location();
	Location(int x, int y);
	~Location();

	int GetX();
	void SetX(int value);
	int GetY();
	void SetY(int value);
};