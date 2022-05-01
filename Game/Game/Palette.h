#pragma once
#include "Color.h"

class Palette
{
private:
	int colorCount;
	Color** colors;

public:
	Palette();
	~Palette();

	void CreateDefaultPalette();
	void AddColor(Color* color);
	Color* CreateCompatibleColor(Color* color);
};