#include "GameEngine.h"
#include "LoadingScreen.h"
#include "ToolWindow.h"
#include "ShapeNode.h"
#include "SpriteNode.h"
#include "SpriteNinePatch.h"
#include "AssetManager.h"
#include "Button.h"
#include "Checkbox.h"
#include "ToolWindow.h"
#include "ProgressBar.h"
#include "LoadingBar.h"
#include "TestWindow.h"
#include "LevelEditor.h"

float scale = 0;
float currentFireIndex = 0;

Button* myButton1;
Button* myButton2;
Button* myButton3;
Checkbox* myCheckbox;
ToolWindow* myToolWindow1;
ToolWindow* myToolWindow2;
ProgressBar* myProgressBar;
SpriteNode* myTextureSprite;
SpriteNode* myFireSprite;
TestWindow* myTestWindow;

TextureAtlas* myLoadingBarTextureAtlas;
SpriteNinePatch* myLoadingBarSprite;

LoadingScreen::LoadingScreen()
{
	LogEngine::Log(LOG_TRACE, "LoadingScreen", "Constructor called.");

	this->SetName("LoadingScreen");
	this->SetTitle("Scene1 - LoadingScreen");
	this->SetIsVisible(true);
	this->SetLocation(new Location(50, 50));
	this->SetSize(new Size(600, 480));

	//ShapeNode* background = new ShapeNode();
	//background->SetLocation(new Location(0, 0));
	//background->SetSize(new Size(1000, 1000));
	//background->SetFillColor(AssetManager::CreateColor(255, 0, 192, 192));
	//background->SetStrokeColor(AssetManager::CreateColor(255, 192, 0, 192));
	//this->AddChild(background);

	//TextNode* text = new TextNode();
	//text->SetText("Background");
	//text->SetTextColor(AssetManager::CreateColor(255, 255, 255, 255));
	//background->AddChild(text);

	TextureAtlas* myTextureAtlas = AssetManager::CreateTextureAtlas("caco.png");// ("Checkbox.png");
	myTextureAtlas->SetHorizontalCount(1);
	myTextureAtlas->SetVerticalCount(1);

	TextureAtlas* myFireTextureAtlas = AssetManager::CreateTextureAtlas("goldenaxe1.png");
	myFireTextureAtlas->SetHorizontalCount(4);
	myFireTextureAtlas->SetVerticalCount(4);


	LoadingBar* myLoadingBar = new LoadingBar();
	myLoadingBar->SetLocation(new Location(0, 0));
	myLoadingBar->SetSize(new Size(1000, 20));

	myButton1 = new Button(nullptr, "ButtonShowWindow", "Show window", 10, 10, 80, 30);
	myButton2 = new Button(nullptr, "ButtonExit", "Exit App", 10, 50, 80, 30);
	myButton3 = new Button(nullptr, "ButtonLoadLevelEditor", "Level Editor", 10, 90, 150, 30);

	myCheckbox = new Checkbox(nullptr, "CheckboxVSync", "Enable VSync", 10, 130, 160, 30);
	myToolWindow1 = new ToolWindow(nullptr, "SampleWindow1", "Sample window 1", 70, 170, 300, 300);
	myToolWindow2 = new ToolWindow(nullptr, "SampleWindow2", "Sample window 2", 20, 120, 300, 300);
	myProgressBar = new ProgressBar(nullptr, "ProgressBar", 480, 10, 160, 30);
	myProgressBar->SetMaxValue(1000);

	myTextureSprite = new SpriteNode();
	myTextureSprite->SetLocation(new Location(320, 236));
	myTextureSprite->SetSize(new Size(768, 768));
	myTextureSprite->SetTextureAtlas(myTextureAtlas);
	myTextureSprite->SetTextureIndex(0);
	//myTextureSprite->SetIsVisible(false);

	myFireSprite = new SpriteNode();
	myFireSprite->SetLocation(new Location(400, 50));
	myFireSprite->SetSize(new Size(96, 96));
	myFireSprite->SetTextureAtlas(myFireTextureAtlas);
	myFireSprite->SetTextureIndex(0);
	//myFireSprite->SetIsVisible(false);

	myTestWindow = new TestWindow();



	EventManager::Subscribe(this); // To receive Update messages

	this->AddChild(myButton1);
	this->AddChild(myButton2);
	this->AddChild(myButton3);
	this->AddChild(myCheckbox);
	this->AddChild(myToolWindow1);
	this->AddChild(myToolWindow2);
	this->AddChild(myProgressBar);
	this->AddChild(myFireSprite);
	this->AddChild(myTextureSprite);
	this->AddChild(myLoadingBar);
	this->AddChild(myTestWindow);
	//this->SetLocation(new Location(300, 100));
}

LoadingScreen::~LoadingScreen()
{
	LogEngine::Log(LOG_TRACE, "LoadingScreen", "Destructor called.");

	//Will the super Node's destructor be called???
}

void LoadingScreen::Update()
{
	int value = myProgressBar->GetValue() + 1;

	if (value > 1000)
	{
		value = 0;
	}

	myProgressBar->SetValue(value);

	float frameTime = GameEngine::GetDeltaTime();
	currentFireIndex += (frameTime / 25);
	//if (currentFireIndex > 15.0f) currentFireIndex = 0.0f;
	
	myFireSprite->SetTextureIndex((int)currentFireIndex % 16);
}

void LoadingScreen::Draw(GraphicsContext* g)
{
	CanvasNode* cn = (CanvasNode*)myTextureSprite;

	if (cn != nullptr)
	{
		scale += 0.1f;
		cn->SetSize(new Size((int)scale, (int)scale));
	}
}
 
void LoadingScreen::ProcessMessage(Message* msg)
{
	if (msg->type == MSG_BUTTON_CLICKED)
	{
		if (msg->sender == myButton1)
		{
			myToolWindow1->SetIsVisible(!myToolWindow1->GetIsVisible());

			int value = myProgressBar->GetValue() + 100;

			if (value > 1000)
			{
				value = 0;
			}

			myProgressBar->SetValue(value);
		}

		if (msg->sender == myButton2)
		{
			GameEngine::StopLoop();
		}

		if (msg->sender == myButton3)
		{
			LevelEditor* levelEditor = new LevelEditor();
			//this->AddChild((Node*)levelEditor);
			GameEngine::AddToRootScene((Node*)levelEditor);
			this->SetIsVisible(false);
		}

		if (msg->sender == this->GetCloseButton())
		{
			GameEngine::StopLoop();
		}

		if (msg->sender == this->GetMaximizeButton())
		{
			RenderingEngine::SetWindowFullScreen();
		}

		ToolWindow::ProcessMessage(msg);
	}

	if (msg->type == MSG_CHECKBOX_CLICKED)
	{
		if (msg->sender == myCheckbox)
		{
			int result;
			if (myCheckbox->GetIsChecked())
			{
				//Enable VSYNC

				int swapInterval = SDL_GL_GetSwapInterval();

				if (swapInterval == 0)
				{
					result = SDL_GL_SetSwapInterval(-1);
					//SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1
					//SDL_SetHintWithPriority(SDL_HINT_RENDER_VSYNC, "1", SDL_HINT_OVERRIDE);

					LogEngine::SetFilterFlags(LOG_DEBUG);
					LogEngine::Log(LOG_DEBUG, "LoadingScreen", "SwapInterval=" + std::to_string(result));
					LogEngine::SetFilterFlags(LOG_NONE);

				}
			}
			else
			{
				//Disable VSYNC

				int swapInterval = SDL_GL_GetSwapInterval();

				//if (swapInterval != 0)
				{

					result = SDL_GL_SetSwapInterval(0);
					//SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");
					//SDL_SetHintWithPriority(SDL_HINT_RENDER_VSYNC, "0", SDL_HINT_OVERRIDE);

					LogEngine::SetFilterFlags(LOG_DEBUG);
					LogEngine::Log(LOG_DEBUG, "LoadingScreen", "SwapInterval=" + std::to_string(result));
					LogEngine::SetFilterFlags(LOG_NONE);
				}
			}

			
		}
	}
}
