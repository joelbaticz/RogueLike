#include "MainMenu.h"
#include "LoadingBar.h"
#include "AssetManager.h"
#include "RogueLike.h"
#include "MessageBox.h"
#include "SettingsWindow.h"
#include "InfoPane.h"
#include "RendererFront.h"

MainMenu::MainMenu()
{
	LogEngine::Log(LOG_DEBUG, "MainMenu", "Constructor called.");

	int screenWidth = RendererFront::GetWindowWidth() + 1;
	int screenHeight = RendererFront::GetWindowHeight() + 1;
	int buttonWidth = 200;
	int buttonHeight = 30;
	int buttonX = (screenWidth - buttonWidth) / 2;
	int buttonY = screenHeight / 2 - 140;
	int buttonPaddingY = 20;

	this->SetName("MainMenu");
	this->SetIsVisible(true);
	this->SetX(0);
	this->SetY(0);
	this->SetSize(new Size(screenWidth, screenHeight));
	//this->SetFillColor(AssetManager::CreateColor(255, 0, 0, 0));
	//this->SetStrokeColor(AssetManager::CreateColor(255, 0, 0, 0));

	backgroundShape = new ShapeNode();
	backgroundShape->SetName("ShapeNode");
	backgroundShape->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	backgroundShape->SetX(0);
	backgroundShape->SetY(0);
	backgroundShape->SetSize(new Size(screenWidth, screenHeight));
	backgroundShape->SetFillColor(AssetManager::CreateColor(255, 0, 0, 0));
	backgroundShape->SetStrokeColor(AssetManager::CreateColor(255, 0, 0, 0));
	this->AddChild(backgroundShape);

	//TextureAtlas* backgroundTextureAtlas = AssetManager::CreateTextureAtlas("BackgroundAnimation.png");
	//backgroundTextureAtlas->SetHorizontalCount(20);
	//backgroundTextureAtlas->SetVerticalCount(1);

	TextureAtlas* backgroundTextureAtlas = AssetManager::CreateTextureAtlas("MenuScreen.png");
	backgroundTextureAtlas->SetHorizontalCount(1);
	backgroundTextureAtlas->SetVerticalCount(1);

	backgroundSprite = new SpriteNode();
	backgroundSprite->SetName("LoadingScreenSprite");
	backgroundSprite->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	backgroundSprite->SetX(0);
	backgroundSprite->SetY(0);
	backgroundSprite->SetSize(new Size(screenWidth, screenHeight));
	backgroundSprite->SetTextureAtlas(backgroundTextureAtlas);
	backgroundSprite->SetTextureIndex(0);
	this->AddChild(backgroundSprite);

	LoadingBar* myLoadingBar = new LoadingBar();
	myLoadingBar->SetX(0);
	myLoadingBar->SetY(screenHeight - 20);
	myLoadingBar->SetSize(new Size(screenWidth, 20));
	//this->AddChild(myLoadingBar);

	buttonNewGame = new Button(this, "buttonNewGame", "New Game", buttonX, buttonY, buttonWidth, buttonHeight);

	buttonY += buttonHeight + buttonPaddingY;
	buttonLoadGame = new Button(this, "buttonLoadGame", "Load Game", buttonX, buttonY, buttonWidth, buttonHeight);

	buttonY += buttonHeight + buttonPaddingY;
	buttonSettings = new Button(this, "buttonSettings", "Settings", buttonX, buttonY, buttonWidth, buttonHeight);

	buttonY += buttonHeight + buttonPaddingY;
	buttonCredits = new Button(this, "buttonCredits", "Credits", buttonX, buttonY, buttonWidth, buttonHeight);

	buttonY += buttonHeight + buttonPaddingY;
	buttonExit = new Button(this, "buttonExit", "Exit", buttonX, buttonY, buttonWidth, buttonHeight);

	labelVersionInfo = new Label(this, "labelVersionInfo", "Version: " + Configuration::Version, this->GetWidth() - 313, this->GetHeight() - 53, 300, 23);
	labelVersionInfo->SetIsBackgroundVisible(false);
	labelVersionInfo->SetTextAlign(Align::AlignRightCenter);

	//labelFPS = new Label(this, "labelFPS", "", 10, 10, 300, 23);
	//labelFPS->SetIsBackgroundVisible(false);

	InfoPane* infoPane = new InfoPane();
	infoPane->SetLocation(5, 5);

	this->AddChild(buttonNewGame);
	this->AddChild(buttonLoadGame);
	this->AddChild(buttonSettings);
	this->AddChild(buttonCredits);
	this->AddChild(buttonExit);
	this->AddChild(labelVersionInfo);
	//this->AddChild(labelFPS);

	this->AddChild(infoPane);
	//GameEngine::AddToRootScene(infoPane);
	//infoPane->BringToFront();

	EventManager::Subscribe(this); // To receive Update messages
}

MainMenu::~MainMenu() = default;

void MainMenu::Update()
{
	//magnifyFactor += magnifyDelta;
	//if (magnifyFactor > 1.02) magnifyDelta = -magnifyDelta;
	//if (magnifyFactor < 0.98) magnifyDelta = -magnifyDelta;

	//int width = 640.0f * magnifyFactor;
	//int height = 480.0f * magnifyFactor;
	//int x = 50;//640 - width / 2;
	//int y = 50;//480 - height / 2;

	//Location* location = backgroundShape->GetLocation();
	//location->SetX(x);
	//location->SetY(y);

	//Size* size = backgroundShape->GetSize();
	//size->SetWidth(width);
	//size->SetHeight(height);

	//backgroundShape->SetLocation(location);
	//backgroundShape->SetSize(size);

	float fElapsedTime = GameEngine::GetDeltaTime();

	animationIndex += fElapsedTime / 150 * animationDelta;
	if (animationIndex > 9)
	{
		animationDelta = -1;
		animationIndex = 9;
	}

	if (animationIndex < 0)
	{
		animationDelta = 1;
		animationIndex = 0;
	}

	//backgroundSprite->SetTextureIndex((int)animationIndex);

//	float fps = GameEngine::GetFPS();

	//labelFPS->SetText("FPS: " + std::to_string(fps));
	//labelFPS->SetIsBackgroundVisible(false);
}


void MainMenu::ProcessMessage(Message* msg)
{
	if (msg->type == MSG_BUTTON_CLICKED)
	{
		if (msg->sender == buttonNewGame)
		{
			if (buttonNewGame->GetCaption() == "New Game")
			{
				// Select scene to load
				sceneToLoad = new RogueLike();
				sceneToLoad->SetMainMenu(this);
				GameEngine::AddToRootScene(sceneToLoad);

				// Hide Main Menu
				this->SetIsVisible(false);

				// Rename NewGame button
				buttonNewGame->SetCaption("Resume Game");

				// Disable Settings
				//buttonSettings->SetIsEnabled(false);

				// Move all buttons to the side
				int screenWidth = RendererFront::GetWindowWidth();
				int buttonWidth = 200;
				int buttonX = (screenWidth - buttonWidth) - 80;

				backgroundSprite->SetX(40);

				buttonNewGame->SetX(buttonX);
				buttonLoadGame->SetX(buttonX);
				buttonSettings->SetX(buttonX);
				buttonCredits->SetX(buttonX);
				buttonExit->SetX(buttonX);
			}
			else
			{
				sceneToLoad->SetIsVisible(true);
				
				// Hide Main Menu
				this->SetIsVisible(false);
			}
		}

		if (msg->sender == buttonLoadGame)
		{
			//MessageBox::ShowMessage("Not implemented yet!", (MessageBoxButton)(MessageBoxButton::Ok | MessageBoxButton::Cancel));
			MessageBox::ShowMessage("Error","Not implemented yet!", Ok);
		}

		if (msg->sender == buttonSettings)
		{
			SettingsWindow* sceneToLoad = new SettingsWindow();
			GameEngine::AddToRootScene(sceneToLoad);
		}

		if (msg->sender == buttonCredits)
		{
		}

		if (msg->sender == buttonExit)
		{
			GameEngine::StopLoop();
		}

		//if (msg->sender == this->GetCloseButton())
		//{
		//	GameEngine::StopLoop();
		//}
	}
}

