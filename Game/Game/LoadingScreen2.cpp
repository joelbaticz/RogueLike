#include "LoadingScreen2.h"
#include "GameEngine.h"
#include "ToolWindow.h"
#include "ShapeNode.h"
#include "SpriteNinePatch.h"
#include "AssetManager.h"
#include "Button.h"
#include "Checkbox.h"
#include "ToolWindow.h"
#include "ProgressBar.h"
#include "LoadingBar.h";

#include <vector>

ToolWindow* toolWindowLoading;
ProgressBar* progressBarLoading;
SpriteNinePatch* testSprite1;

int itemIndexToLoad = 0;
std::vector<std::string> resourcesToLoad;

LoadingScreen2::LoadingScreen2()
{
	LogEngine::Log(LOG_TRACE, "LoadingScreen2", "Constructor called.");

	this->SetName("LoadingScreen2");
	this->SetIsVisible(true);
	this->SetLocation(new Location(0, 0));
	this->SetSize(new Size(800, 600));
	this->SetFillColor(AssetManager::CreateColor(255, 10, 20, 60));
	this->SetStrokeColor(AssetManager::CreateColor(255, 10, 20, 60));

	LoadingBar* myLoadingBar = new LoadingBar();
	myLoadingBar->SetLocation(new Location(0, 580));
	myLoadingBar->SetSize(new Size(1000, 20));
	this->AddChild(myLoadingBar);

	for (int i = 0; i < 5; i++)
	{
		resourcesToLoad.push_back("button.png");
		resourcesToLoad.push_back("progressbar.png");
		resourcesToLoad.push_back("fire.png");
		resourcesToLoad.push_back("caco.png");
	}

	EventManager::Subscribe(this); // To receive Update messages
}

LoadingScreen2::~LoadingScreen2()
{
	LogEngine::Log(LOG_TRACE, "LoadingScreen2", "Destructor called.");

	//Will the super Node's destructor be called???

}

void LoadingScreen2::Update()
{
	itemIndexToLoad++;

	switch (itemIndexToLoad)
	{
	case 0:
		return;
	case 1:
		toolWindowLoading = new ToolWindow(this, "toolWindowLoading", "toolWindowLoading", 70, 170, 300, 100);
		toolWindowLoading->SetIsVisible(true);
		//toolWindowLoading->SetParent(this);
		this->AddChild(toolWindowLoading);
		return;
	case 2:
		progressBarLoading = new ProgressBar(toolWindowLoading, "progressBarLoading", 20, 40, 260, 30);
		progressBarLoading->SetIsVisible(true);
		progressBarLoading->SetMaxValue(resourcesToLoad.size());
		toolWindowLoading->AddChild(progressBarLoading);
		return;
	}

	if (!resourcesToLoad.empty())
	{
		std::string nextItem = resourcesToLoad.at(0);
		resourcesToLoad.erase(resourcesToLoad.begin()); //Erase 0th item 

		TextureAtlas* textureAtlas = AssetManager::CreateTextureAtlas(nextItem);

		if (progressBarLoading != nullptr)
		{
			progressBarLoading->SetValue(itemIndexToLoad - 3);
		}
	}
}

//void LoadingScreen2::Draw(GraphicsContext* g)
//{
//	int width = this->GetSize()->GetWidth();
//	int height = this->GetSize()->GetHeight();
//
//	g->BeginDraw();
//
//	g->SetFillColor(AssetManager::CreateColor(255, 30, 40, 80));
//	g->DrawFilledRectangle(0, 0, width, height);
//	
//	g->EndDraw();
//}

void LoadingScreen2::ProcessMessage(Message* msg)
{
	//if (msg->type == MSG_BUTTON_CLICKED)
	//{
	//	if (msg->sender == myButton1)
	//	{
	//		myToolWindow1->SetIsVisible(!myToolWindow1->GetIsVisible());

	//		int value = myProgressBar->GetValue() + 100;

	//		if (value > 1000)
	//		{
	//			value = 0;
	//		}

	//		myProgressBar->SetValue(value);
	//	}

	//	if (msg->sender == myButton2)
	//	{
	//		GameEngine::StopLoop();
	//	}
	//}
}
