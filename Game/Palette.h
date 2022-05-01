#pragma once
#include "Color.h"
#include <unordered_map>

enum PaletteType
{
	GrayScale = 1,
	RGB666 = 2,
	RGB676 = 3,
	RGB685 = 4,
	RGB884 = 5,
	Experimental = 6
};

class Palette
{
private:
	int colorCount;
	Color** colors;

	PaletteType usedPalette;

	std::unordered_map<int, int> matchedColors;

	void CreateGrayScalePalette();
	void CreateRGB884Palette();
	void CreateRGB685Palette();
	void CreateRGB666Palette();
	void CreateRGB676Palette();
	void CreateExperimentalPalette();

	int GetColorIndex(Color* color);
	int GetColorIndexPaletteGrayscale(Color* color);
	int GetColorIndexPaletteRGB666(Color* color);
	int GetColorIndexPaletteRGB676(Color* color);
	int GetColorIndexPaletteRGB685(Color* color);
	int GetColorIndexPaletteRGB884(Color* color);

	int GetColorIndexPrecise(Color* color);

	bool IsColorCached(int colorKey);
public:
	Palette();
	~Palette();

	void CreateDefaultPalette();
	void AddColor(Color* color);
	void CreateCompatibleColor(Color* color, Color* newColor);
	Color* GetColorAtIndex(int index);
};