#include <iostream>
#include <string>

#include "main.h"
#include "GameEngine.h"
#include "LoadingScreen.h"
#include "LoadingScreen2.h"

int main(int, char**) {

	std::cout << "[TRACE] - Main: Startup..." << std::endl;

	if (GameEngine::Init(100, 100, 800, 600) != 0)
	{
		GameEngine::UnInit();

		std::cout << "[TRACE] - Main: Exited with error: 1." << std::endl;
		return 1;
	};

	LogEngine::Log(LOG_TRACE, "Main", "GameEngine has been initalized.");

	Node* startScene = new LoadingScreen();
	LogEngine::Log(LOG_TRACE, "Main", "Start scene name: " + startScene->GetName());
	
	GameEngine::StartLoop(startScene);
	delete startScene;
	GameEngine::UnInit();

	std::cout << "[TRACE] - Main: Exited without errors." << std::endl;
	return 0;
}


