#include "TextureAtlas.h"

//TextureAtlas can only be created by the AssetManager

TextureAtlas::TextureAtlas()
{
	this->horizontalCount = 1;
	this->verticalCount = 1;
}

TextureAtlas::~TextureAtlas()
{
}

int TextureAtlas::GetHorizontalCount()
{
	return this->horizontalCount;
}

void TextureAtlas::SetHorizontalCount(int count)
{
	this->horizontalCount = count;
}

int TextureAtlas::GetVerticalCount()
{
	return this->verticalCount;
}

void TextureAtlas::SetVerticalCount(int count)
{
	this->verticalCount = count;
}

void TextureAtlas::GetTextureRectangle(int textureIndex, Rectangle* targetRect)
{
	int unitWidth = this->GetWidth() / this->horizontalCount;
	int unitHeight = this->GetHeight() / this->verticalCount;

	int verticalCount = textureIndex / this->horizontalCount;
	int horizontalCount = textureIndex % this->horizontalCount;

	targetRect->SetX(unitWidth * horizontalCount);
	targetRect->SetY(unitHeight * verticalCount);
	targetRect->SetWidth(unitWidth);
	targetRect->SetHeight(unitHeight);
}
