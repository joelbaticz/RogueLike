#pragma once

#include "Node.h"
#include "Location.h"
#include "Size.h"
#include "Rectangle.h"
#include "GraphicsContext.h"

//#include "SDL.h"
//#include "LogEngine.h"
//#include "GameEngine.h"
//#include "AssetManager.h"
//#include "RenderingEngine.h"

class CanvasNode: public Node
{
private:
	//typedef Node	super;
	bool			isVisible;
	//bool			toBeShownInSceneTree;
	//bool			isFreeFlowNode;

	Location*		location;
	Size*			size;

	GraphicsContext* graphics;

	int minimizedWindows = 0;

	void SetGraphicsContext();
	void SetBoundsRect();
	void SetClippingRect();
protected:
	void GetScreenBoundsLoop(Node* node, Rectangle* boundsRect);

public:
	CanvasNode();
	CanvasNode(std::string name);
	~CanvasNode();

	bool GetIsVisible();
	void SetIsVisible(bool value);
	Location* GetLocation();
	void SetLocation(Location* location);
	Size* GetSize();
	void SetSize(Size* size);
	Rectangle* GetRectangle();
	virtual void SetRectangle(Rectangle* rect);
	Rectangle* SetScreenBounds();
	void BringToFront();

	void ResetGraphicsContext();

	int GetMinimizedWindows();
	void SetMinimizedWindows(int value);

	GraphicsContext* GetGraphics();
	void SetGraphics(GraphicsContext* graphics);

	virtual void ProcessMessage(Message* msg);
	//virtual void Update();
	virtual void Draw(GraphicsContext* g);
	virtual Node* SetParent(Node* value) override;
	virtual void AddChild(Node* nodeToAdd) override;
};