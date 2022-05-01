#include "LevelEditor.h"
#include "AssetManager.h"



LevelEditor::LevelEditor()
{
	LogEngine::Log(LOG_TRACE, "LevelEditor", "Constructor called.");

	this->SetName("LevelEditor");
	this->SetIsVisible(true);
	this->SetLocation(new Location(0, 0));
	this->SetSize(new Size(800, 600));
	//this->SetFillColor(AssetManager::CreateColor(255, 54, 73, 106));
	this->SetFillColor(AssetManager::CreateColor(255, 36, 36, 85));
	this->SetStrokeColor(AssetManager::CreateColor(255, 207, 214, 230));

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
	LogEngine::Log(LOG_TRACE, "LoadingScreen2", "Destructor called.");

	//Will the super Node's destructor be called???
}

void LevelEditor::Update()
{
	loadIndex++;

	if (loadIndex == 1)
	{
		InitializeWindows();
		InitializeLevel("");

		loadingWindow->SetIsVisible(false);
	}
}

void LevelEditor::InitializeWindows()
{
	viewport = new Viewport();
	viewport->SetSize(new Size(this->GetSize()->GetWidth(), this->GetSize()->GetHeight()));

	toolsWindow = new ToolWindow(this, "LevelEditorToolWindowTools", "Tools", 10, 10, 50, 450);
	toolsWindow->GetMinimizeButton()->SetIsVisible(false);
	toolsWindow->GetMaximizeButton()->SetIsVisible(false);
	toolsWindow->GetContextMenuButton()->SetIsVisible(false);

	objectExplorerWindow = new ToolWindow(this, "LevelEditorToolWindowObjectExplorer", "Explorer", 640, 10, 150, 290);
	objectExplorerWindow->GetMinimizeButton()->SetIsVisible(false);
	objectExplorerWindow->GetMaximizeButton()->SetIsVisible(false);
	objectExplorerWindow->GetContextMenuButton()->SetIsVisible(false);

	objectPropertiesWindow = new ToolWindow(this, "LevelEditorToolWindowObjectProperties", "Properties", 640, 300, 150, 290);
	objectPropertiesWindow->GetMinimizeButton()->SetIsVisible(false);
	objectPropertiesWindow->GetMaximizeButton()->SetIsVisible(false);
	objectPropertiesWindow->GetContextMenuButton()->SetIsVisible(false);

	this->AddChild(viewport);
	this->AddChild(toolsWindow);
	this->AddChild(objectExplorerWindow);
	this->AddChild(objectPropertiesWindow);

}

void LevelEditor::InitializeLevel(std::string levelPathName)
{
	if (levelPathName == "")
	{
		editedLevel = new Level();
		viewport->SetRenderedLevel(editedLevel);
		
	}
}

void LevelEditor::ProcessMessage(Message* msg)
{
	//if (msg->type == MSG_BUTTON_CLICKED)
	//{
	//	if (msg->sender == myButton1)
	//	{
}