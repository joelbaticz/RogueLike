#pragma once

#include "ShapeNode.h"
#include "ToolWindow.h"
#include "Label.h"
#include "Level.h"
#include "Viewport.h"
#include "Camera3D.h"

class LevelEditor : public ToolWindow // ShapeNode
{
private:
	typedef	ToolWindow	super; // Create super keyword to access the base class

	int					loadIndex = 0;

	ToolWindow*			loadingWindow;
	Label*				loadingLabel;
	ToolWindow*			objectExplorerWindow;
	ToolWindow*			objectPropertiesWindow;
	ToolWindow*			toolsWindow;
	ToolWindow*			viewportWindow;
	Viewport*			viewport;
	Camera3D*			cameraTopView;
	Camera3D*			cameraPlayer;

	Level*				editedLevel;

	void InitializeLevelEditor();
	void HideAllWindows();
	void ShowAllWindows();
	void InitializeLevel(std::string levelPathName);
	void HandleUi(Message* msg);
	void HandleKeyboard(Message* msg);
	void HandleWindowOptions(Message* msg);
	void HandleViewportOptions(Message* msg);
	
	void ToggleToolsWindow();
	void ToggleObjectExplorerWindow();
	void ToggleObjectPropertiesWindow();
	void RecalcViewportWindowDimensions();
public:
	LevelEditor();
	~LevelEditor();

	void Update();
	void Draw(GraphicsContext* g) override;
	void ProcessMessage(Message* msg) override; //Need to be a ControlNode to receive these I think
};
