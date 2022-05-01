#pragma once

#include "Texture.h"

class TextureImage: public Texture
{
public:
	int		columnCount;
	int		rowCount;

	TextureImage();
	~TextureImage();

	void GetTextureRectangle(int textureIndex, SDL_Rect* targetRect);
};