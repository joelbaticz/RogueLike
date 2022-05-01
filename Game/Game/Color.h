#pragma once

#include "SDL.h"
#include "Resource.h"

class Color: public Resource
{
private:
	int mIndex;
	int mAlpha;
	int mRed;
	int mGreen;
	int mBlue;

public:
	Color();
	Color(int a, int r, int g, int b);
	Color(Color* color);
	~Color();

	void SetColor(int a, int r, int g, int b);
	int GetIndex();
	void SetIndex(int index);
	int GetAlpha();
	int GetRed();
	int GetGreen();
	int GetBlue();
};