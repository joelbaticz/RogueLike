#include "GameEngine.h"
#include "Label.h"
#include "ToolWindow.h"
#include "InfoPane.h"
#include "Configuration.h"
#include "RendererFront.h"

//Init static members
std::string			GameEngine::s_ComponentName;
Node*				GameEngine::s_RootNode;
CanvasNode*			GameEngine::s_RootScene;
Node*				GameEngine::s_WindowInfoPane;

bool				GameEngine::s_ShouldQuitLoop;
float				GameEngine::s_FrameCount;
float				GameEngine::s_LastFrameCount;
float				GameEngine::s_LastTime;
float				GameEngine::s_CurrentTime;
float				GameEngine::s_DeltaTime;
float				GameEngine::s_FrameTime;
float				GameEngine::s_FpsCount;

//Hidden constructor / destructor - Init should be used instead
GameEngine::GameEngine()
{
	LogEngine::Log(LOG_DEBUG, s_ComponentName, "Constructor called.");
}

//Hidden Desctructor
GameEngine::~GameEngine()
{
	LogEngine::Log(LOG_DEBUG, s_ComponentName, "Destructor called.");
}

int GameEngine::Init(int windowX, int windowY, int windowWidth, int windowHeight, bool isFullScreen, std::string windowTitle)
{
	//Log GameEngine Init without LogEngine
	std::cout << "[TRACE] - GameEngine: Init() called." << std::endl;

	//Initialize members
	s_ComponentName = "GameEngine";
	s_RootNode = nullptr;
	s_RootScene = nullptr;
	s_WindowInfoPane = nullptr;

	if (LogEngine::Init(LOG_TRACE | LOG_DEBUG | LOG_ERROR) != 0)
	{
		LogEngine::Log(LOG_ERROR, s_ComponentName, SDL_GetError());
		return 1;
	}

	if (Configuration::Init() != 0)
	{
		LogEngine::Log(LOG_ERROR, s_ComponentName, SDL_GetError());
		return 1;
	}

	//AssetManager (TTF is NEEDED) - Init
	if (AssetManager::Init("res") != 0)
	{
		LogEngine::Log(LOG_ERROR, s_ComponentName, SDL_GetError());
		return 1;
	}

	if (RendererFront::Init(windowX, windowY, windowWidth, windowHeight, isFullScreen, windowTitle) != 0)
	{
		LogEngine::Log(LOG_ERROR, s_ComponentName, "Error initializing Renderer");
		return 1;
	}

	if (EventManager::Init() != 0)
	{
		LogEngine::Log(LOG_ERROR, s_ComponentName, "Error init MessageBus");
		return 1;
	}

	s_RootNode = new Node("RootNode");

	//RootScene needs to be a drawable child (CanvasNode, ShapeNode, etc.) otherwise it won't draw children
	//s_RootScene = new ShapeNode();
	s_RootScene = new CanvasNode();
	s_RootScene->SetSize(windowWidth, windowHeight);
	//s_RootScene->SetFillColor(AssetManager::CreateColor(255, 121, 85, 64));
	//s_RootScene->SetStrokeColor(AssetManager::CreateColor(255, 160, 100, 80));
	
	//AddToRootNode(s_RootScene);
	
	//Log init was OK
	LogEngine::Log(LOG_DEBUG, s_ComponentName, "Init()...OK.");

	return 0;
}

void GameEngine::UnInit()
{
	LogEngine::Log(LOG_DEBUG, s_ComponentName, "UnInit() called.");
	
	EventManager::UnInit();

	RendererFront::UnInit();

	LogEngine::Log(LOG_DEBUG, s_ComponentName, "UnInit...OK.");
}

float GameEngine::GetFrameCount()
{
	return s_FrameCount;
}

float GameEngine::GetFPS()
{
	return s_FpsCount;
}

float GameEngine::GetFrameTime()
{
	return s_FrameTime;
}

float GameEngine::GetDeltaTime()
{
	//Gets ticks since last frame
	return s_DeltaTime;
}

void GameEngine::UpdateTickers()
{
	std::string strFrameInfo = "";

	s_FrameCount++;
	s_DeltaTime = SDL_GetTicks() - s_CurrentTime;
	s_CurrentTime = SDL_GetTicks();
	if (s_CurrentTime > s_LastTime + 1000)
	{
		s_FpsCount = s_FrameCount - s_LastFrameCount;
		s_FrameTime = (s_CurrentTime - s_LastTime) / s_FpsCount;

		strFrameInfo = "FrameNo.: " + std::to_string(s_FrameCount);
		strFrameInfo += ", FPS: " + std::to_string(s_FpsCount);
		strFrameInfo += ", FrameTime: " + std::to_string(s_FrameTime) + "[ms]";

		std::cout << strFrameInfo << std::endl;
		LogEngine::Log(LOG_TRACE, "GameEngine", strFrameInfo);

		s_LastFrameCount = s_FrameCount;
		s_LastTime = s_CurrentTime;
	}
}

int GameEngine::StartLoop(Node* scene)
{
	LogEngine::Log(LOG_TRACE, s_ComponentName, "StartLoop() called.");

	//AddToRootScene(scene);
	AddToRootNode(scene);

	SDL_Event e;
	Message msg = Message();
	Message* pMsg = &msg;	

	s_ShouldQuitLoop = false;
	while (!s_ShouldQuitLoop)
	{
		RendererFront::BeginFrame();

		UpdateTickers();

		//HANDLE INPUTS
		//SEND INPUT MESSAGES TO SCENE -> THAT DUDE WILL BUBBLE IT DOWN TO IT'S CHILDREN

		//Query event queue - Process all events
		//SDL_PollEvent(&e); // Not sure if it's a good idea to process all the SDL events until we run out of them
		while (SDL_PollEvent(&e))
		{
			//Hande system wide events
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.scancode == SDL_SCANCODE_F9)
				{
					//Toggle visibility of InfoPane
					//((InfoPane*)s_WindowInfoPane)->SetIsVisible(!((InfoPane*)s_WindowInfoPane)->GetIsVisible());
				}
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					//Quit GameLoop
					s_ShouldQuitLoop = true;
				}
			}

			//Create message
			pMsg->sdlEvent = &e;
			
			switch (e.type)
			{
			case SDL_MOUSEMOTION:
				pMsg->type = MSG_MOUSEMOTION;
				break;
			case SDL_MOUSEBUTTONDOWN:
				pMsg->type = MSG_MOUSEBUTTONDOWN;
				break;
			case SDL_MOUSEBUTTONUP:
				pMsg->type = MSG_MOUSEBUTTONUP;
				break;
			case SDL_MOUSEWHEEL:
				pMsg->type = MSG_MOUSEWHEEL;
				break;
			//case SDL_KEYDOWN:
			//	pMsg->type = MSG_KEYDOWN;
			//	break;
			case SDL_KEYUP:
				pMsg->type = MSG_KEYUP;
				break;
			default:
				pMsg->type = MSG_UNDEFINED;
			}

			EventManager::Broadcast(pMsg);
		}

		//PRODUCE FAKE KEYDOWN EVENTS TO OVERCOME KEYBOARD DELAY
		const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

		for (int i = 0; i < 255; i++)
		{
			if (keyboardState[i])   //SDL_SCANCODE_PAGEDOWN
			{
				pMsg->type = MSG_KEYDOWN;

				pMsg->sdlEvent = new SDL_Event();
				pMsg->sdlEvent->key = SDL_KeyboardEvent();
				pMsg->sdlEvent->key.keysym.scancode = (SDL_Scancode)i; //SDL_SCANCODE_PAGEDOWN;
				pMsg->sdlEvent->key.keysym.sym = SDL_GetKeyFromScancode((SDL_Scancode)i); //SDLK_PAGEDOWN

				EventManager::Broadcast(pMsg);

				delete pMsg->sdlEvent;
			}
		}


		//SEND UPDATE TO SCENE
		pMsg->type = MSG_UPDATE;
		EventManager::Broadcast(pMsg);

		//SEND DRAW TO SCENE
		pMsg->type = MSG_DRAW;
		EventManager::Broadcast(pMsg);

		RendererFront::PresentFrame();
	}

	LogEngine::SetFilterFlags(LOG_ALL);

	return 0;
}

void GameEngine::StopLoop()
{
	s_ShouldQuitLoop = true;
}

void GameEngine::AddToRootScene(Node* node)
{
	//s_RootScene->AddChild(node);
	s_RootNode->AddChild(node);
}

Node* GameEngine::GetRootNode()
{
	return s_RootNode;
}

bool GameEngine::IsRootNode(Node* node)
{
	if (node == s_RootNode) return true;
	return false;
}

void GameEngine::AddToRootNode(Node* node)
{
	s_RootNode->AddChild(node);
}

CanvasNode* GameEngine::GetRootScene()
{
	return s_RootScene;
}