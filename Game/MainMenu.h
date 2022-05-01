#pragma once
#include "ShapeNode.h"
#include "Button.h"
#include "ToolWindow.h"
#include "RogueLike.h"
#include "Label.h"

class MainMenu: public CanvasNode
{
private:
	ShapeNode* backgroundShape;
	SpriteNode* backgroundSprite;
	Button* buttonNewGame;
	Button* buttonLoadGame;
	Button* buttonSettings;
	Button* buttonCredits;
	Button* buttonExit;
	Label* labelVersionInfo;
	Label* labelFPS;

	double magnifyFactor = 1.0;
	double magnifyDelta = 0.00002;

	float animationIndex = 0;
	float animationDelta = 1;

	RogueLike* sceneToLoad;
public:
	MainMenu();
	~MainMenu();

	void Update() override;
	void ProcessMessage(Message* msg) override;
};
