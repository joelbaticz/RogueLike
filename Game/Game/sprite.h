#pragma once

#include <string>
#include <SDL.h>
#include "spritesheet.h"

typedef struct _Sprite
{
	std::string title;
	SpriteSheet* spriteSheet;
	SDL_Rect* rectSource;
	SDL_Texture* texture;
} Sprite;