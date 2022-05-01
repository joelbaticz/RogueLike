#pragma once

#include "Texture.h"
#include "Rectangle.h"

class TextureAtlas : public Texture
{
private:
	int			horizontalCount;
	int			verticalCount;

public:
	TextureAtlas();
	~TextureAtlas();

	int GetHorizontalCount();
	void SetHorizontalCount(int count);
	int GetVerticalCount();
	void SetVerticalCount(int count);

	void GetTextureRectangle(int textureIndex, Rectangle* targetRect);
};