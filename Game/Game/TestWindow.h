#pragma once

#include "ToolWindow.h"

class TestWindow : public ToolWindow
{
public:
	TestWindow();
	~TestWindow();

	void Update();
	void Draw(GraphicsContext* g) override;
};
