#include "Palette.h"
#include <vector>

Palette::Palette()
{
	this->colorCount = 0;
	this->colors = nullptr;
}

Palette::~Palette()
{
	delete[] this->colors;
}

void Palette::CreateDefaultPalette()
{
	//for (int i = 0; i < 256; i++)
	//{
	//	Color* newColor = new Color(255, i, i, i);
	//	this->AddColor(newColor);
	//}


	uint8_t redvalues[] = { 0x00, 0x24, 0x49, 0x6D, 0x92, 0xB6, 0xDB, 0xFF };
	uint8_t greenvalues[] = { 0x00, 0x24, 0x49, 0x6D, 0x92, 0xB6, 0xDB, 0xFF };
	uint8_t bluevalues[] = { 0x00, 0x55, 0xAA, 0xFF };

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

		//colors[i].r = colors[i].g = colors[i].b = (Uint8)i;
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

Color* Palette::CreateCompatibleColor(Color* color)
{
	//int bestFittingIndex = 255;
	//int minDiff = 256 * 256 * 256;

	//for (int i = 0; i < this->colorCount; i++)
	//{
	//	Color* compareColor = colors[i];

	//	int diff = abs(compareColor->GetRed() - color->GetRed()) +
	//		abs(compareColor->GetGreen() - color->GetGreen()) +
	//		abs(compareColor->GetBlue() - color->GetBlue());

	//	if (diff < minDiff)
	//	{
	//		minDiff = diff;
	//		bestFittingIndex = i;
	//	}
	//}

	//RED: 3 bits (0-7)
	//GREEN: 3 bits (0-7)
	//BLUE: 2 bits (0-3)
	
	int bestFittingIndex = (color->GetRed() / 32 * 32) + (color->GetGreen() / 32 * 4) + (color->GetBlue() / 64);
	if (bestFittingIndex > 255)
	{
		bestFittingIndex = 255;
	}

	Color* newColor = new Color(colors[bestFittingIndex]);
	
	return newColor;
}