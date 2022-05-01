#pragma once

#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include <SDL_ttf.h>

#include "LogEngine.h"
#include "AssetManager.h"
#include "RenderingEngine.h"
#include "EventManager.h"

#include "Node.h"
#include "CanvasNode.h"
#include "ShapeNode.h"
#include "ControlNode.h" //Remove these after I moved infoPane and Editor to different classes

#include "Color.h"
#include "Texture.h"
#include "Font.h"

#include "Location.h"
#include "Size.h"
#include "Rectangle.h"

#include "Message.h"


//Static class, because we just want to use the namespace and there can need not to be any objects
class GameEngine
{
private:
	static std::string			s_ComponentName;
	static Node*				s_RootNode;
	static ShapeNode*			s_RootScene;
	static Node*				s_WindowInfoPane;

	static bool					s_ShouldQuitLoop;

	//Performance Indicators
	static float				s_FrameCount;
	static float				s_LastFrameCount;
	static float				s_LastTime;
	static float				s_CurrentTime;
	static float				s_DeltaTime;
	static float				s_FrameTime;
	static float				s_FpsCount;
	
	//Hidden constructor / destructor - Init should be used instead
	GameEngine();
	~GameEngine();

	static void UpdateTickers();
public:
	static int Init(int windowX, int windowY, int windowWidth, int windowHeight);
	static void UnInit();
	static int StartLoop(Node* node);
	static void StopLoop();
	static void AddToRootScene(Node* node);
	
	static Node* GetRootNode();
	static bool IsRootNode(Node* node);
	static void AddToRootNode(Node* node);
	static CanvasNode* GetRootScene();

	static float GetFPS();
	static float GetFrameCount();
	static float GetFrameTime();
	static float GetDeltaTime();
};