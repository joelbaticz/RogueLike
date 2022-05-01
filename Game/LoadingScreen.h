#pragma once

#include "Node.h"
#include "LogEngine.h"
//#include "CanvasNode.h"
//#include "ShapeNode.h"
#include "ToolWindow.h"

class LoadingScreen : public ToolWindow//ShapeNode
{
private:
	typedef Node	super;
	Node*			scene;

	void DrawChild(Node* node);
public:
	LoadingScreen();
	~LoadingScreen();

	void Update();
	void Draw(GraphicsContext* g) override;
	void ProcessMessage(Message* msg) override;
};