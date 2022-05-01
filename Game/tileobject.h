#pragma once

#include "spritesheet.h"
#include "sprite.h"
#include "SDL.h"

typedef struct _TileObject
{
	SpriteSheet* spriteSheet;
	int tilePosX;
	int tilePosY;
	SDL_Rect* rectSource; //Same as sprite->rectSource ???
	Sprite* sprite; //Default look
	Sprite* currentSprite; //The animator sets this one for the current frame???
	bool isAnimated = false;
	int startAnimFrame = 0;
	int endAnimFrame = 8;
	int currentAnimFrame = 0;

	//PANIMATOR pAnimator = nullptr;

} TileObject;