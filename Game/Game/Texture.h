#pragma once

#include <string>
#include "SDL.h"
#include <SDL_image.h>
#include "LoadableResource.h"

class Texture: public LoadableResource
{
private:
	int		width;
	int		height;
	int		widthInBytes;	// Stride
	void*	pixelData;		// The size of this pointer will be determined if it is an 8bit or a 32bit texture
public:
	Texture();
	~Texture();

	int GetWidth();
	void SetWidth(int width);

	int GetHeight();
	void SetHeight(int height);

	int GetWidthInBytes();
	void SetWidthInBytes(int widthInBytes);

	void* GetPixelData();
	void SetPixelData(void* pixelData);
};