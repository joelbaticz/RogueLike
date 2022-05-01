#include "Texture.h"

Texture::Texture()
{
	this->SetResourceName("Texture");
	this->SetResourceFileNamePath("\\");
	this->width = 0;
	this->height = 0;
	this->widthInBytes = 0;
	this->pixelData = nullptr;
}

Texture::~Texture()
{
}

int Texture::GetWidth()
{
	return this->width;
}

void Texture::SetWidth(int width)
{
	this->width = width;
}

int Texture::GetHeight()
{
	return this->height;
}

void Texture::SetHeight(int height)
{
	this->height = height;
}

int Texture::GetWidthInBytes()
{
	return this->widthInBytes;
}

void Texture::SetWidthInBytes(int widthInBytes)
{
	this->widthInBytes = widthInBytes;
}

void* Texture::GetPixelData()
{
	return this->pixelData;
}

void Texture::SetPixelData(void* pixelData)
{
	this->pixelData = pixelData;
}

