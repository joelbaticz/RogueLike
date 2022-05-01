#pragma once

#include "Node.h"
#include "LogEngine.h"
#include "ToolWindow.h"

class LoadingScreen2 : public ShapeNode
{
private:
	typedef Node	super;
	Node*			scene;

	void DrawChild(Node* node);
public:
	LoadingScreen2();
	~LoadingScreen2();

	void Update();
	//void Draw(GraphicsContext* g) override;
	void ProcessMessage(Message* msg) override;
};