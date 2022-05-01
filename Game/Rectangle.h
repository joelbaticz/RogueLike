#pragma once

#include "Resource.h"

class Rectangle : public Resource
{
private:
	int x;
	int y;
	int width;
	int height;

public:
	Rectangle();
	Rectangle(int x, int y, int width, int height);
	Rectangle(Rectangle*);
	~Rectangle();

	int GetX();
	void SetX(int x);
	int GetY();
	void SetY(int y);
	int GetWidth();
	void SetWidth(int width);
	int GetHeight();
	void SetHeight(int height);
	bool IsEmpty();
};