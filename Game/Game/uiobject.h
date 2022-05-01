#pragma once

#include "spritesheet.h"
#include "sprite.h"
#include "SDL.h"

//Lehetne inkabb Node


typedef struct _UiObject
{
	std::string caption;
	int x;
	int y;
	int w;
	int h;
	bool isVisible;
	bool isEnabled;
	bool isDefault;	
	bool hasKeyboardFocus;
	bool isMouseHover;
	bool isMousePress;
	int stateCount; //Max number of states --> needed for creating the sprites list
	_UiObject* parent;
	_UiObject* children;

	Sprite** sprites; //It points to list of sprite pointers
	int cornerSize;

	void(*processMessage)(SDL_Event e);

	//void* ProcessMessage();




	//Sprite* currentRenderedSprite; //The current rendered look of the button with caption
	//Animation when statechange?
	
} UiObject;