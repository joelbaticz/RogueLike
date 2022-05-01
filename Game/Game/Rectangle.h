#pragma once

#include "Resource.h"
#include "Location.h"
#include "Size.h"

class Rectangle : public Resource
{
private:
	Location*	location;
	Size*		size;

public:
	Rectangle();
	Rectangle(int x, int y, int width, int height);
	Rectangle(Rectangle*);
	~Rectangle();

	int GetX();
	void SetX(int value);
	int GetY();
	void SetY(int value);
	int GetWidth();
	void SetWidth(int value);
	int GetHeight();
	void SetHeight(int value);
	bool IsEmpty();
};