#pragma once

#include <SDL.h>
#include "uiobject.h"

//UiObject* createScreen(int w, int h, void(*processMessage)(SDL_Event e));
UiObject* createScreen(int w, int h, SDL_Renderer* gameRendy);
