#include "Size.h"

Size::Size()
{
	this->width = 0;
	this->height = 0;
}

Size::Size(int width, int height)
{
	this->width = width;
	this->height = height;
}

Size::~Size()
{}

int Size::GetWidth()
{
	return this->width;
}

void Size::SetWidth(int value)
{
	this->width = value;
}

int Size::GetHeight()
{
	return this->height;
}

void Size::SetHeight(int value)
{
	this->height = value;
}

