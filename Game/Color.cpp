#include "Color.h"

Color::Color()
{
	this->mIndex = 0;
	this->mAlpha = 0;
	this->mRed = 0;
	this->mGreen = 0;
	this->mBlue = 0;
	this->mColorRGB555 = 0;
}

Color::Color(int a, int r, int g, int b)
{
	this->mIndex = 0;
	this->mAlpha = a;
	this->mRed = r;
	this->mGreen = g;
	this->mBlue = b;
	this->mColorRGB555 = 0;
}

Color::Color(Color* color)
{
	this->mIndex = color->mIndex;
	this->mAlpha = color->mAlpha;
	this->mRed = color->mRed;
	this->mGreen = color->mGreen;
	this->mBlue = color->mBlue;
	this->mColorRGB555 = color->mColorRGB555;
}

Color::~Color()
{

}

void Color::SetColor(int a, int r, int g, int b)
{
	//GameEngine::QueryPalette
	//Should query the palette and come up with the closest color component
	//Furthermore it should set the index to an appropiate value too
	//Alpha channel would be set the supplied one

	this->mAlpha = a;
	this->mRed = r;
	this->mGreen = g;
	this->mBlue = b;
}

int Color::GetIndex()
{
	return this->mIndex;
}

void Color::SetIndex(int index)
{
	this->mIndex = index;
}

int Color::GetAlpha()
{
	return this->mAlpha;
}

int Color::GetRed()
{
	return this->mRed;
}

int Color::GetGreen()
{
	return this->mGreen;
}

int Color::GetBlue()
{
	return this->mBlue;
}

uint16_t Color::GetRGB555()
{
	return mColorRGB555;
}

void Color::SetRGB555(uint16_t color16bit)
{
	mColorRGB555 = color16bit;
}



