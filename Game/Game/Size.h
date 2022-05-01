#pragma once

#include "Resource.h"

#define DEFAULT_WIDTH	200
#define DEFAULT_HEIGHT	200

class Size: public Resource
{
private:
	int		width;
	int		height;
public:
	Size();
	Size(int width, int height);
	~Size();

	int GetWidth();
	void SetWidth(int value);
	int GetHeight();
	void SetHeight(int value);

};