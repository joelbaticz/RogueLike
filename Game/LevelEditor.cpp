#include "LevelEditor.h"
#include "AssetManager.h"
#include "RendererFront.h"

LevelEditor::LevelEditor()
{
	LogEngine::Log(LOG_DEBUG, "LevelEditor", "Constructor called.");

	this->SetName("LevelEditor");
	this->SetTitle("Level Editor");
	this->SetIsVisible(true);
	this->SetX(0);
	this->SetY(0);
	this->SetSize(new Size(RendererFront::GetWindowWidth(), RendererFront::GetWindowHeight()));
	//this->SetFillColor(AssetManager::CreateColor(255, 54, 73, 106));
	//this->SetFillColor(AssetManager::CreateColor(255, 36, 36, 85));
	//this->SetStrokeColor(AssetManager::CreateColor(255, 207, 214, 230));

	loadingLabel = new Label(loadingWindow, "LevelEditorLabelLoading", "Loading, please wait...", 20, 20, 200, 20);
	loadingLabel->SetTextColor(AssetManager::CreateColor(255, 255, 0, 0));

	loadingWindow = new ToolWindow(this, "LevelEditorToolWindowLoading", "Loading Level Editor...", 250, 250, 300, 80);
	loadingWindow->GetMinimizeButton()->SetIsVisible(false);
	loadingWindow->GetMaximizeButton()->SetIsVisible(false);
	loadingWindow->GetCloseButton()->SetIsVisible(false);
	loadingWindow->GetContextMenuButton()->SetIsVisible(false);
	loadingWindow->AddChild(loadingLabel);

	this->AddChild(loadingWindow);

	editedLevel = nullptr;

	EventManager::Subscribe(this); // To receive Update messages
}

LevelEditor::~LevelEditor()
{
	LogEngine::Log(LOG_DEBUG, "LevelEditor", "Destructor called.");

	//Will the super Node's destructor be called???
}

void LevelEditor::Update()
{
	loadIndex++;

	if (loadIndex == 1)
	{
		InitializeLevelEditor();
		InitializeLevel("");

		//ShowAllWindows();
		loadingWindow->SetIsVisible(false);
	}
}

void LevelEditor::InitializeLevelEditor()
{
	toolsWindow = new ToolWindow(this, "LevelEditorToolWindowTools", "Tools", 5, 5, 50, 450);
	toolsWindow->GetMinimizeButton()->SetIsVisible(false);
	toolsWindow->GetMaximizeButton()->SetIsVisible(false);
	toolsWindow->GetContextMenuButton()->SetIsVisible(false);

	objectExplorerWindow = new ToolWindow(this, "LevelEditorToolWindowObjectExplorer", "Explorer", this->GetWidth() - 160, 5, 150, 280);
	objectExplorerWindow->GetMinimizeButton()->SetIsVisible(false);
	objectExplorerWindow->GetMaximizeButton()->SetIsVisible(false);
	objectExplorerWindow->GetContextMenuButton()->SetIsVisible(false);

	objectPropertiesWindow = new ToolWindow(this, "LevelEditorToolWindowObjectProperties", "Properties", this->GetWidth() - 160, 285, 150, 280);
	objectPropertiesWindow->GetMinimizeButton()->SetIsVisible(false);
	objectPropertiesWindow->GetMaximizeButton()->SetIsVisible(false);
	objectPropertiesWindow->GetContextMenuButton()->SetIsVisible(false);

	viewportWindow = new ToolWindow(this, "LevelEditorToolWindowViewport", "Viewport", 60, 5, 640, 570);
	viewportWindow->GetMinimizeButton()->SetIsVisible(false);
	viewportWindow->GetMaximizeButton()->SetIsVisible(false);
	viewportWindow->GetContextMenuButton()->SetIsVisible(false);

	cameraTopView = new Camera3D();
	cameraTopView->angleX = Math::DegreeToRadian(90.0f);
	cameraTopView->angleY = Math::DegreeToRadian(0.0f);
	cameraTopView->angleZ = 0;//Math::DegreeToRadian(180.0f);
	cameraTopView->posX = 0;// 750;
	cameraTopView->posY = 0;// -150;
	cameraTopView->posZ = -30;
	cameraTopView->scaling = 0.025f;

	Mat4* projectionMatrixTop = new Mat4();
	cameraTopView->SetProjection(projectionMatrixTop->Identity());

	cameraPlayer = new Camera3D();
	cameraPlayer->angleX = Math::DegreeToRadian(90.0f);
	cameraPlayer->angleY = 0;//Math::DegreeToRadian(45.0f);
	cameraPlayer->angleZ = 0;//Math::DegreeToRadian(180.0f);
	cameraPlayer->posX = 0;//-10;
	cameraPlayer->posY = 0;//-10;
	cameraPlayer->posZ = 0;
	cameraPlayer->scaling = 0.025f;

	Mat4* projectionMatrixPlayer = new Mat4();
	cameraPlayer->SetProjection(projectionMatrixPlayer->ProjectPerspective(90.0f, (float)RendererFront::GetWindowWidth() / (float)RendererFront::GetWindowHeight(), 0.1f, 1000.0f));


	viewport = new Viewport();
	viewport->SetX(0);
	viewport->SetY(0);
	viewport->SetSize(new Size(viewportWindow->GetWidth(), viewportWindow->GetHeight()));
	viewport->SetCamera(cameraTopView);
	viewportWindow->AddChild(viewport);

	this->AddChild(viewportWindow);
	this->AddChild(toolsWindow);
	this->AddChild(objectExplorerWindow);
	this->AddChild(objectPropertiesWindow);

	RecalcViewportWindowDimensions();

	viewport->SetIsFocused(true);

	//HideAllWindows();
}

void LevelEditor::HideAllWindows()
{
	viewport->SetIsVisible(false);
	toolsWindow->SetIsVisible(false);
	objectExplorerWindow->SetIsVisible(false);
	objectPropertiesWindow->SetIsVisible(false);
}

void LevelEditor::ShowAllWindows()
{
	viewport->SetIsVisible(true);
	toolsWindow->SetIsVisible(true);
	objectExplorerWindow->SetIsVisible(true);
	objectPropertiesWindow->SetIsVisible(true);
}

void LevelEditor::InitializeLevel(std::string levelPathName)
{
	if (levelPathName == "")
	{
		//editedLevel = new Level(16, 16);
		editedLevel = new Level(40, 40);
		viewport->SetRenderedLevel(editedLevel);
	}
}

void LevelEditor::Draw(GraphicsContext* g)
{

}

void LevelEditor::ProcessMessage(Message* msg)
{
	//Call the base class's similar method (LevelEditor is inheriting from ToolWindow)
	super::ProcessMessage(msg);

	HandleUi(msg);
	HandleKeyboard(msg);
}

void LevelEditor::HandleUi(Message* msg)
{
	if (msg->type == MSG_BUTTON_CLICKED)
	{
		if (msg->sender == this->GetCloseButton())
		{
			GameEngine::StopLoop();
		}
	}
}

void LevelEditor::HandleKeyboard(Message* msg)
{
	if (msg->type == MSG_KEYDOWN)
	{
		HandleWindowOptions(msg);
		HandleViewportOptions(msg);
	}
}

void LevelEditor::HandleWindowOptions(Message* msg)
{
	if (msg->sdlEvent->key.keysym.sym == SDLK_F5)
	{
		ToggleToolsWindow();
	}
	if (msg->sdlEvent->key.keysym.sym == SDLK_F6)
	{
		ToggleObjectExplorerWindow();
	}
	if (msg->sdlEvent->key.keysym.sym == SDLK_F7)
	{
		ToggleObjectPropertiesWindow();
	}
	if (msg->sdlEvent->key.keysym.sym == SDLK_F8)
	{
		ToggleToolsWindow();
		ToggleObjectExplorerWindow();
		ToggleObjectPropertiesWindow();
	}
}

void LevelEditor::HandleViewportOptions(Message* msg)
{
	if (msg->sdlEvent->key.keysym.sym == SDLK_F1)
	{
		viewport->SetCamera(cameraTopView);
	}
	if (msg->sdlEvent->key.keysym.sym == SDLK_F2)
	{
		viewport->SetCamera(cameraPlayer);
	}
}

void LevelEditor::ToggleToolsWindow()
{
	bool isVisible = toolsWindow->GetIsVisible();

	if (isVisible)
	{
		toolsWindow->SetIsVisible(false);
	}
	else
	{
		toolsWindow->SetIsVisible(true);
		toolsWindow->GetContextMenuButton()->SetIsVisible(false);
		toolsWindow->GetMinimizeButton()->SetIsVisible(false);
		toolsWindow->GetMaximizeButton()->SetIsVisible(false);
	}	

	RecalcViewportWindowDimensions();
}

void LevelEditor::ToggleObjectExplorerWindow()
{
	bool isVisible = objectExplorerWindow->GetIsVisible();

	if (isVisible)
	{
		objectExplorerWindow->SetIsVisible(false);
	}
	else
	{
		objectExplorerWindow->SetIsVisible(true);
		objectExplorerWindow->GetContextMenuButton()->SetIsVisible(false);
		objectExplorerWindow->GetMinimizeButton()->SetIsVisible(false);
		objectExplorerWindow->GetMaximizeButton()->SetIsVisible(false);
	}

	RecalcViewportWindowDimensions();
}

void LevelEditor::ToggleObjectPropertiesWindow()
{
	bool isVisible = objectPropertiesWindow->GetIsVisible();

	if (isVisible)
	{
		objectPropertiesWindow->SetIsVisible(false);
	}
	else
	{
		objectPropertiesWindow->SetIsVisible(true);
		objectPropertiesWindow->GetContextMenuButton()->SetIsVisible(false);
		objectPropertiesWindow->GetMinimizeButton()->SetIsVisible(false);
		objectPropertiesWindow->GetMaximizeButton()->SetIsVisible(false);
	}

	RecalcViewportWindowDimensions();
}

void LevelEditor::RecalcViewportWindowDimensions()
{
	int windowPosX = 5;
	int windowPosY = 5;
	int windowWidth = this->GetWidth() - 15;
	int windowHeight = this->GetHeight() - 30;

	if (toolsWindow->GetIsVisible())
	{
		windowPosX += toolsWindow->GetWidth() + 5;
		windowWidth -= toolsWindow->GetWidth() + 5;
	}

	if (objectExplorerWindow->GetIsVisible() || objectPropertiesWindow->GetIsVisible())
	{
		windowWidth -= objectExplorerWindow->GetWidth() + 5;
	}

	viewportWindow->SetX(windowPosX);
	viewportWindow->SetY(windowPosY);
	viewportWindow->SetSize(new Size(windowWidth, windowHeight));

	viewport->SetSize(new Size(windowWidth - 10, windowHeight - 25));
}

