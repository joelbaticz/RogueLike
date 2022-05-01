#pragma once

#include "ShapeNode.h"
#include "ToolWindow.h"
#include "Label.h"
#include "Level.h"
#include "Viewport.h"

class LevelEditor : ShapeNode
{
private:
	int			loadIndex = 0;

	ToolWindow* loadingWindow;
	Label*		loadingLabel;
	ToolWindow* objectExplorerWindow;
	ToolWindow* objectPropertiesWindow;
	ToolWindow* toolsWindow;
	Viewport* viewport;

	Level* editedLevel;

	void InitializeWindows();
	void InitializeLevel(std::string levelPathName);
public:
	LevelEditor();
	~LevelEditor();

	void Update();
	//void Draw(GraphicsContext* g) override;
	void ProcessMessage(Message* msg) override;
};
