#pragma once

#include <string>
#include <SDL.h>

typedef struct _SpriteSheet
{
	std::string title;
	std::string fileName;
	SDL_Texture* texture;
	int* spriteList;

} SpriteSheet;