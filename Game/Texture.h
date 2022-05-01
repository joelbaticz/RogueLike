#pragma once

#include <string>
#include "SDL.h"
#include <SDL_image.h>
#include "LoadableResource.h"

class Texture: public LoadableResource
{
private:
	int				width;
	int				height;
	int				widthInBytes;	// Stride
	void*			pixelData;		// The size of this pointer will be determined if it is an 8bit or a 32bit texture
	SDL_Texture*	texture;		// Used for hardware accelerated drawing operations
public:
	Texture();
	~Texture() override;

	int GetWidth();
	void SetWidth(int width);

	int GetHeight();
	void SetHeight(int height);

	int GetWidthInBytes();
	void SetWidthInBytes(int widthInBytes);

	void* GetPixelData();
	void SetPixelData(void* pixelData);

	SDL_Texture* GetTexture();
	void SetTexture(SDL_Texture* texture);
};