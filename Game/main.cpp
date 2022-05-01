#include <iostream>
#include <string>

#include "main.h"
#include "GameEngine.h"
#include "LoadingScreen.h"
#include "LoadingScreen2.h"
#include "LevelEditor.h"
#include "RogueLike.h"
#include "MainMenu.h"

#define _ITERATOR_DEBUG_LEVEL 0
#define _HAS_ITERATOR_DEBUGGING 0

int main(int, char**)
{
	std::cout << "[TRACE] - Main: Startup..." << std::endl;

	int windowX = 0;
	int windowY = 0;
	int windowWidth = 1280;
	int windowHeight = 720; 
	bool isFullScreen = false;
	std::string windowTitle = "Game";

Start:

	if (GameEngine::Init(windowX, windowY, windowWidth, windowHeight, isFullScreen, windowTitle) != 0)
	{
		GameEngine::UnInit();

		std::cout << "[TRACE] - Main: Exited with error: 1." << std::endl;
		return 1;
	};

	LogEngine::SetFilterFlags(LOG_TRACE | LOG_ERROR);
	LogEngine::Log(LOG_TRACE, "Main", "GameEngine has been initalized.");

	Node* startScene = new LoadingScreen2();
	//Node* startScene = new MainMenu();
	//Node* startScene = new LoadingScreen();
	//Node* startScene = new LevelEditor();
	//Node* startScene = new RogueLike();
	LogEngine::Log(LOG_TRACE, "Main", "Start scene name: " + startScene->GetName());

	GameEngine::StartLoop(startScene);
	delete startScene;
	GameEngine::UnInit();
	AssetManager::UnInit();

	if (Configuration::IsRestart)
	{
		windowX = Configuration::WindowX;
		windowY = Configuration::WindowY;
		windowWidth = Configuration::WindowWidth;
		windowHeight = Configuration::WindowHeight;

		goto Start;
	}

	std::cout << "[TRACE] - Main: Exited without errors." << std::endl;
	return 0;
}


