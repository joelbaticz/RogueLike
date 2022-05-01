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
	uint16_t mColorRGB555;

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
	uint16_t GetRGB555();
	void SetRGB555(uint16_t color16bit);
};