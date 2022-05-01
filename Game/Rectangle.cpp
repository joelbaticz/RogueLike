#include "Rectangle.h"

Rectangle::Rectangle()
{
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}

Rectangle::Rectangle(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Rectangle::Rectangle(Rectangle* rectOther)
{
	this->x = rectOther->GetX();
	this->y = rectOther->GetY();
	this->width = rectOther->GetWidth();
	this->height = rectOther->GetHeight();
}

Rectangle::~Rectangle() = default;

int Rectangle::GetX()
{
	return x;
}

void Rectangle::SetX(int x)
{
	this->x = x;
}

int Rectangle::GetY()
{
	return y;
}

void Rectangle::SetY(int y)
{
	this->y = y;
}

int Rectangle::GetWidth()
{
	return width;
}

void Rectangle::SetWidth(int width)
{
	this->width = width;
}

int Rectangle::GetHeight()
{
	return height;
}

void Rectangle::SetHeight(int height)
{
	this->height = height;
}

bool Rectangle::IsEmpty()
{
	if (this->width <= 0 ||
		this->height <= 0)
	{
		return true;
	}

	return false;
}
