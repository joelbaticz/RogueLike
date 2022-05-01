#pragma once

#include "Node.h"
#include "LogEngine.h"
#include "ToolWindow.h"
#include <vector>
#include "ProgressBar.h"
#include "Label.h"

class LoadingScreen2 : public ShapeNode
{
private:
	//typedef Node	super;
	//Node*			scene;
	ToolWindow* toolWindowLoading;
	ProgressBar* progressBarLoading;
	SpriteNinePatch* testSprite1;
	Label* labelLoading;

	int screenWidth;
	int screenHeight;
	int windowWidth;
	int windowHeight;
	int windowPosX;
	int windowPosY;

	int itemIndexToLoad = 0;
	std::vector<std::string> resourcesToLoad;

	Node* sceneToLoad;

	void DrawChild(Node* node);
public:
	LoadingScreen2();
	~LoadingScreen2();

	void Update();
	//void Draw(GraphicsContext* g) override;
	//void ProcessMessage(Message* msg) override;
};
