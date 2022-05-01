
#include <SDL.h>
//#include "logging.h"
#include "screen.h"
#include "main.h"

/*
SDL_Renderer* gameRendi = nullptr;

void processMessage(SDL_Event e)
{
	if (e.type == SDL_MOUSEMOTION)
	{
		SpriteSheet* newSS = createSpriteSheetFromImageFile("Button.png");
		Sprite* newS = createSpriteFromSpriteSheet(newSS, 0, 0, 100, 50);

		if (gameRendi == nullptr)
		{
			//Error("damn", "damn");
		}

		//SDL_RenderCopy(GameRenderer, newS->texture, NULL, NULL);
		SDL_RenderCopy(gameRendi, newS->texture, NULL, NULL);
	}
}

//UiObject* createScreen(int w, int h, void(*processMessage)(SDL_Event e))
UiObject* createScreen(int w, int h, SDL_Renderer* gameRendy)
{
	gameRendi = gameRendy;

	UiObject* newScreen = new UiObject();
	newScreen->caption = "screen";
	newScreen->parent = nullptr;
	newScreen->children = nullptr;
	newScreen->x = 0;
	newScreen->y = 0;
	newScreen->w = w;
	newScreen->h = h;
	newScreen->cornerSize = 0;
	newScreen->hasKeyboardFocus = false;
	newScreen->isDefault = true;
	newScreen->isEnabled = true;
	newScreen->isMouseHover = false;
	newScreen->isMousePress = false;
	newScreen->sprites = nullptr;
	newScreen->stateCount = 0;
	newScreen->processMessage = processMessage;


	return newScreen;
}
*/