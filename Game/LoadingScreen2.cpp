#include "LoadingScreen2.h"
#include "GameEngine.h"
#include "ToolWindow.h"
#include "ShapeNode.h"
#include "AssetManager.h"
#include "ProgressBar.h"
#include "LoadingBar.h";

#include <vector>
#include "RogueLike.h"
#include "MainMenu.h"
#include "MessageBox.h"
#include "RendererFront.h"

LoadingScreen2::LoadingScreen2()
{
	screenWidth = RendererFront::GetWindowWidth();
	screenHeight = RendererFront::GetWindowHeight();

	windowWidth = 350;
	windowHeight = 100;
	windowPosX = (screenWidth - windowWidth) / 2;
	//windowPosY = (screenHeight - windowHeight) / 2;
	windowPosY = screenHeight - windowHeight - 50;

	LogEngine::Log(LOG_DEBUG, "LoadingScreen2", "Constructor called.");

	this->SetName("LoadingScreen2");
	this->SetX(0);
	this->SetY(0);
	this->SetSize(new Size(screenWidth, screenHeight));
	this->SetFillColor(AssetManager::CreateColor(255, 0, 0, 0));
	this->SetStrokeColor(AssetManager::CreateColor(255, 0, 0, 0));

	//TextureAtlas* backgroundTextureAtlas = AssetManager::CreateTextureAtlas("LoadingScreenBackground.png");
	TextureAtlas* backgroundTextureAtlas = AssetManager::CreateTextureAtlas("LoadingScreenBackground.png");

	SpriteNode* backgroundShape = new SpriteNode();
	backgroundShape->SetName("LoadingScreenSprite");
	backgroundShape->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	backgroundShape->SetX(0);
	backgroundShape->SetY(0);
	backgroundShape->SetSize(this->GetWidth(), this->GetHeight());
	backgroundShape->SetTextureAtlas(backgroundTextureAtlas);
	this->AddChild(backgroundShape);

	LoadingBar* myLoadingBar = new LoadingBar();
	myLoadingBar->SetX(0);
	myLoadingBar->SetY(screenHeight - 20);
	myLoadingBar->SetSize(new Size(screenWidth, 20));
	this->AddChild(myLoadingBar);

	EventManager::Subscribe(this); // To receive Update messages


	for (int i = 0; i < 30; i++)
	{
		// UI Components
		resourcesToLoad.push_back(Configuration::UIPath + "WindowBackground.png");
		resourcesToLoad.push_back(Configuration::UIPath + "WindowFrame.png");
		resourcesToLoad.push_back(Configuration::UIPath + "WindowTitle.png");
		resourcesToLoad.push_back(Configuration::UIPath + "ToolWindowBackground.png");
		resourcesToLoad.push_back(Configuration::UIPath + "ToolWindowFrame.png");
		resourcesToLoad.push_back(Configuration::UIPath + "ToolWindowTitle.png");
		resourcesToLoad.push_back(Configuration::UIPath + "Button.png");
		resourcesToLoad.push_back(Configuration::UIPath + "Checkbox.png");
		resourcesToLoad.push_back(Configuration::UIPath + "ProgressBar.png");
		resourcesToLoad.push_back(Configuration::UIPath + "LoadingBar.png");

		// Fonts
		resourcesToLoad.push_back(Configuration::UIPath + "Arial10p.png");
		resourcesToLoad.push_back(Configuration::UIPath + "Arial16p.png");
		resourcesToLoad.push_back(Configuration::UIPath + "Unispace10p.png");

		// Other
		resourcesToLoad.push_back("Akara-Idle.png");
		resourcesToLoad.push_back("Deckard-Idle.png");
		resourcesToLoad.push_back("Griswold-Idle.png");
		resourcesToLoad.push_back("Mage-Fire.png");
		resourcesToLoad.push_back("Mage-FireBall.png");
		resourcesToLoad.push_back("Mage-IdleTown.png");
		resourcesToLoad.push_back("Mage-Walk.png");
		resourcesToLoad.push_back("Pepin-Idle.png");

		resourcesToLoad.push_back("caco.png");
		resourcesToLoad.push_back("DefaultTexture.png");
		resourcesToLoad.push_back("DefaultTextureSet.png");
		resourcesToLoad.push_back("goldenaxe1.png");
		resourcesToLoad.push_back("MarioTileSet1.png");
		resourcesToLoad.push_back("MarioTileSet2.png");
		resourcesToLoad.push_back("SpriteSheetTemplate.png");
		resourcesToLoad.push_back("TestTexture0.png");
		resourcesToLoad.push_back("TestTexture1.png");
		resourcesToLoad.push_back("TestTexture2.png");
		resourcesToLoad.push_back("TestTexture3.png");
		resourcesToLoad.push_back("TestTexture4.png");
		resourcesToLoad.push_back("TestTexture5.png");
		resourcesToLoad.push_back("TestTexture6.png");
		resourcesToLoad.push_back("TestTexture7.png");
		resourcesToLoad.push_back("TestTexture8.png");
		resourcesToLoad.push_back("TestTexture9.png");

		// Stress Test
		resourcesToLoad.push_back("TestTextures\\Test01.png");
		resourcesToLoad.push_back("TestTextures\\Test02.png");
		resourcesToLoad.push_back("TestTextures\\Test03.png");
		resourcesToLoad.push_back("TestTextures\\Test04.png");
		resourcesToLoad.push_back("TestTextures\\Test05.png");
		resourcesToLoad.push_back("TestTextures\\Test06.png");
		resourcesToLoad.push_back("TestTextures\\Test07.png");
		resourcesToLoad.push_back("TestTextures\\Test08.png");
		resourcesToLoad.push_back("TestTextures\\Test09.png");
		resourcesToLoad.push_back("TestTextures\\Test10.png");
		resourcesToLoad.push_back("TestTextures\\Test11.png");
		resourcesToLoad.push_back("TestTextures\\Test12.png");
		resourcesToLoad.push_back("TestTextures\\Test13.png");
		resourcesToLoad.push_back("TestTextures\\Test14.png");
		resourcesToLoad.push_back("TestTextures\\Test15.png");
		resourcesToLoad.push_back("TestTextures\\Test16.png");
		resourcesToLoad.push_back("TestTextures\\Test17.png");
		resourcesToLoad.push_back("TestTextures\\Test18.png");
		resourcesToLoad.push_back("TestTextures\\Test19.png");
		resourcesToLoad.push_back("TestTextures\\Test20.png");
	}
}

LoadingScreen2::~LoadingScreen2()
{
	LogEngine::Log(LOG_DEBUG, "LoadingScreen2", "Destructor called.");

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
		toolWindowLoading = new ToolWindow(this, "toolWindowLoading", "Loading", windowPosX, windowPosY, windowWidth, windowHeight);
		this->AddChild(toolWindowLoading);

		return;
	case 2:
		int const labelLeft = 20;
		int const labelTop = 15;
		int const labelWidth = windowWidth - (labelLeft * 2);
		int const labelHeight = 20;

		int const progressBarLeft = 20;
		int const progressBarTop = 40;
		int const progressBarWidth = windowWidth - (progressBarLeft * 2);
		int const Height = 30;

		labelLoading = new Label(toolWindowLoading, "labelLoading", "Loading asset", labelLeft, labelTop, labelWidth, labelHeight);
		toolWindowLoading->AddChild(labelLoading);

		progressBarLoading = new ProgressBar(toolWindowLoading, "progressBarLoading", progressBarLeft, progressBarTop, progressBarWidth, Height);
		progressBarLoading->SetMaxValue(resourcesToLoad.size());
		progressBarLoading->SetValue(0);
		toolWindowLoading->AddChild(progressBarLoading);

		LogEngine::Log(LOG_TRACE, "Loading", "Loading assets...");

		return;
	}

	if (!resourcesToLoad.empty())
	{
		std::string nextItem = resourcesToLoad.at(0);
		resourcesToLoad.erase(resourcesToLoad.begin()); //Erase 0th item 

		LogEngine::Log(LOG_TRACE, "Loading resource", nextItem);

		labelLoading->SetText("Loading asset '" + nextItem + "'.");

		TextureAtlas* textureAtlas = AssetManager::CreateTextureAtlas(nextItem);

		if (textureAtlas == nullptr)
		{
			LogEngine::Log(LOG_ERROR, "Loading resource", "Failed to load: " + nextItem);

			//MessageBox::ShowMessage("Error loading resource" + nextItem, Ok);
		}		

		if (progressBarLoading != nullptr)
		{
			progressBarLoading->SetValue(itemIndexToLoad - 3);
		}
	}
	else
	{
		if (sceneToLoad == nullptr)
		{
			//sceneToLoad = new RogueLike();
			sceneToLoad = new MainMenu();

			GameEngine::AddToRootScene(sceneToLoad);

			this->SetIsVisible(false);
			//toolWindowLoading->BringToFront();
		}
	}
}
