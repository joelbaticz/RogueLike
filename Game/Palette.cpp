#include "Palette.h"

Palette::Palette()
{
	this->colorCount = 0;
	this->colors = nullptr;

	this->usedPalette = PaletteType::RGB685; // RGB685 was used before
}

Palette::~Palette()
{
	delete[] this->colors;
}

void Palette::CreateDefaultPalette()
{
	switch(usedPalette)
	{
	case PaletteType::GrayScale:
		CreateGrayScalePalette();

		break;
	case PaletteType::RGB666:
		CreateRGB666Palette();

		break;
	case PaletteType::RGB676:
		CreateRGB676Palette();

		break;
	case PaletteType::RGB685:
		CreateRGB685Palette();

		break;
	case PaletteType::RGB884:
		CreateRGB884Palette();

		break;
	case PaletteType::Experimental:
		CreateExperimentalPalette();

		break;

	default:
		CreateGrayScalePalette();

		break;
	}
}

void Palette::CreateGrayScalePalette()
{
	// Grayscale palette

	for (int i = 0; i < 256; i++)
	{
		Color* newColor = new Color(255, i, i, i);
		this->AddColor(newColor);
	}
}

void Palette::CreateRGB666Palette()
{
	// 6-6-6 levels RGB palette (216 total colors)

	uint8_t redvalues[]		= { 0x00, 0x33, 0x66, 0x99, 0xCC, 0xFF };
	uint8_t greenvalues[]	= { 0x00, 0x33, 0x66, 0x99, 0xCC, 0xFF };
	uint8_t bluevalues[]	= { 0x00, 0x33, 0x66, 0x99, 0xCC, 0xFF };

	size_t i = 0;
	for (uint8_t red : redvalues)
	{
		for (uint8_t green : greenvalues)
		{
			for (uint8_t blue : bluevalues)
			{
				Color* newColor = new Color(255, red, green, blue);
				this->AddColor(newColor);

				i++;
			}
		}
	}

	// Fill remaining 40 colors with grays
	int grayCount = 40;
	int grayStep = 256 / grayCount;
	for (uint8_t j = 0; j < grayCount; j++)
	{
		Color* newColor = new Color(255, j * grayStep, j * grayStep, j * grayStep);
		this->AddColor(newColor);
	}
}

void Palette::CreateRGB676Palette()
{
	// 6-7-6 levels RGB palette (252 total colors)

	uint8_t redvalues[]		= { 0x00, 0x33, 0x66, 0x99, 0xCC, 0xFF };
	uint8_t greenvalues[]	= { 0x00, 0x2A, 0x55, 0x80, 0xAA, 0xD4, 0xFF };
	uint8_t bluevalues[]	= { 0x00, 0x33, 0x66, 0x99, 0xCC, 0xFF };

	size_t i = 0;
	for (uint8_t red : redvalues)
	{
		for (uint8_t green : greenvalues)
		{
			for (uint8_t blue : bluevalues)
			{
				Color* newColor = new Color(255, red, green, blue);
				this->AddColor(newColor);

				i++;
			}
		}
	}

	// Fill remaining 4 colors with grays
	int grayCount = 4;
	int grayStep = 256 / grayCount;
	for (uint8_t j = 0; j < grayCount; j++)
	{
		Color* newColor = new Color(255, j * grayStep, j * grayStep, j * grayStep);
		this->AddColor(newColor);
	}
}

void Palette::CreateRGB685Palette()
{
	// 6-8-5 levels RGB palette (240 total colors)

	uint8_t redvalues[]		= { 0x00, 0x33, 0x66, 0x99, 0xCC, 0xFF };
	uint8_t greenvalues[]	= { 0x00, 0x24, 0x49, 0x6D, 0x92, 0xB6, 0xDB, 0xFF };
	uint8_t bluevalues[]	= { 0x00, 0x40, 0x80, 0xBF, 0xFF };

	size_t i = 0;
	for (uint8_t red : redvalues)
	{
		for (uint8_t green : greenvalues)
		{
			for (uint8_t blue : bluevalues)
			{
				Color* newColor = new Color(255, red, green, blue);
				this->AddColor(newColor);

				i++;
			}
		}
	}

	// Fill remaining 16 colors with grays
	int grayCount = 16;
	int grayStep = 256 / grayCount;
	for (uint8_t j = 0; j < grayCount; j++)
	{
		Color* newColor = new Color(255, j * grayStep, j * grayStep, j * grayStep);
		this->AddColor(newColor);
	}
}

void Palette::CreateRGB884Palette()
{
	// 8-8-4 levels RGB palette (256 total colors)

	uint8_t redvalues[]		= { 0x00, 0x24, 0x49, 0x6D, 0x92, 0xB6, 0xDB, 0xFF };
	uint8_t greenvalues[]	= { 0x00, 0x24, 0x49, 0x6D, 0x92, 0xB6, 0xDB, 0xFF };
	uint8_t bluevalues[]	= { 0x00, 0x55, 0xAA, 0xFF };

	size_t i = 0;
	for (uint8_t red : redvalues)
	{
		for (uint8_t green : greenvalues)
		{
			for (uint8_t blue : bluevalues)
			{
				Color* newColor = new Color(255, red, green, blue);
				this->AddColor(newColor);

				i++;
			}
		}
	}
}

void Palette::CreateExperimentalPalette()
{
	// Highly experimental palette 6-10-4

	uint8_t redvalues[] = { 0x00, 0x33, 0x66, 0x99, 0xCC, 0xFF };
	uint8_t greenvalues[] = { 0x00, 30, 60, 90, 120, 150, 180, 210, 240, 255 };
	uint8_t bluevalues[] = { 0x00, 0x66, 0xCC, 0xFF };

	//uint8_t redvalues[] = { 0x00, 85, 170, 255 };
	//uint8_t greenvalues[] = { 0x00, 30, 60, 75, 90, 105, 120, 135, 150, 165, 180, 195, 210, 225, 240, 255 };
	//uint8_t bluevalues[] = { 0x00, 85, 170, 255 };


	size_t i = 0;
	for (uint8_t red : redvalues)
	{
		for (uint8_t green : greenvalues)
		{
			for (uint8_t blue : bluevalues)
			{
				Color* newColor = new Color(255, red, green, blue);
				this->AddColor(newColor);

				i++;
			}
		}
	}

	// Fill remaining 16 colors with grays
	int grayCount = 16;

	int grayStep = 256 / grayCount;
	for (uint8_t j = 0; j < grayCount; j++)
	{
		Color* newColor = new Color(255, j * grayStep, j * grayStep, j * grayStep);
		this->AddColor(newColor);
	}
}

void Palette::AddColor(Color* color)
{
	if (this->colors == nullptr)
	{
		this->colors = new Color*[256];
		this->colorCount = 0;
	}

	if (colorCount < 256)
	{
		Color* newColor = new Color(color);
		newColor->SetIndex(colorCount);

		this->colors[colorCount] = newColor;
		this->colorCount++;
	}
}

int Palette::GetColorIndex(Color* color)
{
	switch (usedPalette)
	{
	case PaletteType::GrayScale:
		return GetColorIndexPaletteGrayscale(color);

		break;
	case PaletteType::RGB666:
		return GetColorIndexPaletteRGB666(color);

		break;
	case PaletteType::RGB676:
		return GetColorIndexPaletteRGB676(color);

		break;
	case PaletteType::RGB685:
		return GetColorIndexPaletteRGB685(color);

		break;
	case PaletteType::RGB884:
		return GetColorIndexPaletteRGB884(color);

		break;

	default:
		return GetColorIndexPaletteGrayscale(color);

		break;
	}
}

int Palette::GetColorIndexPaletteGrayscale(Color* color)
{
	int index;

	index = color->GetRed() + color->GetGreen() + color->GetBlue();
	index /= 3;

	return index;
}

int Palette::GetColorIndexPaletteRGB666(Color* color)
{
	int index;
	int valueR;
	int valueG;
	int valueB;

	//RED:   (0-5) -> 6 distinctive values
	//GREEN: (0-5) -> 6 distinctive values
	//BLUE:  (0-5) -> 6 distinctive values

	valueR = color->GetRed()	/ 42; // 256 / 6
	valueG = color->GetGreen()	/ 42; // 256 / 6
	valueB = color->GetBlue()	/ 42; // 256 / 6

	index = ((valueR * 6) + valueG) * 6 + valueB;

	if (index > 216)
	{
		index = 216;
	}
	
	return index;
}

int Palette::GetColorIndexPaletteRGB676(Color* color)
{
	int index;
	int valueR;
	int valueG;
	int valueB;

	//RED:   (0-5) -> 6 distinctive values
	//GREEN: (0-6) -> 7 distinctive values
	//BLUE:  (0-5) -> 6 distinctive values

	valueR = color->GetRed()	/ 42; // 256 / 6
	valueG = color->GetGreen()	/ 36; // 256 / 7
	valueB = color->GetBlue()	/ 42; // 256 / 6

	index = ((valueR * 6) + valueG) * 7 + valueB;

	if (index > 252)
	{
		index = 252;
	}

	return index;
}

int Palette::GetColorIndexPaletteRGB685(Color* color)
{
	int index;
	int valueR;
	int valueG;
	int valueB;

	//RED:   (0-5) -> 6 distinctive values
	//GREEN: (0-7) -> 8 distinctive values
	//BLUE:  (0-4) -> 5 distinctive values

	valueR = color->GetRed()	/ 42; // 256 / 6
	valueG = color->GetGreen()	/ 32; // 256 / 8
	valueB = color->GetBlue()	/ 51; // 256 / 5

	index = ((valueR * 6) + valueG) * 8 + valueB;

	if (index > 240)
	{
		index = 240;
	}

	return index;
}

int Palette::GetColorIndexPaletteRGB884(Color* color)
{
	int index;
	int valueR;
	int valueG;
	int valueB;

	//RED: 3 bits (0-7) -> 8 distinctive gradients
	//GREEN: 3 bits (0-7) -> 8 distinctive gradients
	//BLUE: 2 bits (0-3) -> 4 distinctive gradients

	valueR = color->GetRed() * 8 / 256;
	valueG = color->GetGreen() * 8 / 256;
	valueB = color->GetBlue() * 4 / 256;

	index = valueR;
	index <<= 3;
	index += valueG;
	index <<= 2;
	index += valueB;

	return index;
}

int Palette::GetColorIndexPrecise(Color* color)
{
	int bestFittingIndex = 255;
	int minDiff = 3 * 256^2;

	for (int i = 0; i < this->colorCount; i++)
	{
		Color* compareColor = colors[i];

		int diff = abs(compareColor->GetRed() - color->GetRed()) +
			abs(compareColor->GetGreen() - color->GetGreen()) +
			abs(compareColor->GetBlue() - color->GetBlue());

		if (diff < minDiff)
		{
			minDiff = diff;
			bestFittingIndex = i;
		}
	}

	if (bestFittingIndex > 255)
	{
		bestFittingIndex = 255;
	}

	return bestFittingIndex;
}

bool Palette::IsColorCached(int colorKey)
{
	std::unordered_map<int, int>::const_iterator mapIterator = matchedColors.find(colorKey);

	return mapIterator != matchedColors.end();
}

void Palette::CreateCompatibleColor(Color* color, Color* newColor)
{
	int bestFittingIndex;

	int colorKey = (color->GetRed() * 256 + color->GetGreen()) * 256 + color->GetBlue();

	if (IsColorCached(colorKey))
	{
		bestFittingIndex = matchedColors[colorKey];
	}
	else
	{
		//bestFittingIndex = GetColorIndex(color);
		bestFittingIndex = GetColorIndexPrecise(color);

		matchedColors[colorKey] = bestFittingIndex;
	}

	newColor->SetIndex(bestFittingIndex);
	newColor->SetColor(255, colors[bestFittingIndex]->GetRed(), colors[bestFittingIndex]->GetGreen(), colors[bestFittingIndex]->GetBlue());
}

Color* Palette::GetColorAtIndex(int index)
{
	return colors[index];
}