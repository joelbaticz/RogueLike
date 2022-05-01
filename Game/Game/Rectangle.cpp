#include "Rectangle.h"

Rectangle::Rectangle()
{
	this->location = new Location();
	this->size = new Size();
}

Rectangle::Rectangle(int x, int y, int width, int height)
{
	this->location = new Location(x, y);
	this->size = new Size(width, height);
}

Rectangle::Rectangle(Rectangle* rectOther)
{
	this->location = new Location(rectOther->GetX(), rectOther->GetHeight());
	this->size = new Size(rectOther->GetWidth(), rectOther->GetHeight());
}

Rectangle::~Rectangle()
{
	delete this->location;
	delete this->size;
}

int Rectangle::GetX()
{
	return this->location->GetX();
}

void Rectangle::SetX(int value)
{
	this->location->SetX(value);
}

int Rectangle::GetY()
{
	return this->location->GetY();
}

void Rectangle::SetY(int value)
{
	this->location->SetY(value);
}

int Rectangle::GetWidth()
{
	return this->size->GetWidth();
}

void Rectangle::SetWidth(int value)
{
	this->size->SetWidth(value);
}


int Rectangle::GetHeight()
{
	return this->size->GetHeight();
}

void Rectangle::SetHeight(int value)
{
	this->size->SetHeight(value);
}

bool Rectangle::IsEmpty()
{
	if (this->size->GetWidth() <= 0 ||
		this->size->GetHeight() <= 0)
	{
		return true;
	}

	return false;
}
