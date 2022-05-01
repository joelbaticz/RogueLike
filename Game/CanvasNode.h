#pragma once

#include "Node.h"
#include "GraphicsContext.h"
#include "Rectangle.h"
#include "Location.h"
#include "Size.h"

class CanvasNode: public Node
{
private:
	bool			isVisible;

	GraphicsContext* graphics;

	int x;
	int y;
	int width;
	int height;
	int minimizedWindows = 0;

	void SetGraphicsContext();
	void SetBoundsRect();
	void SetClippingRect();
protected:
	void GetScreenBoundsLoop(Node* node, Rectangle* boundsRect);

public:
	// Constructors / Destructors
	CanvasNode();
	CanvasNode(std::string name);
	~CanvasNode();

	// Accessors
	bool GetIsVisible();
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
	Size* GetSize();
	Rectangle* GetRectangle();
	int GetMinimizedWindows();
	GraphicsContext* GetGraphics();

	// Mutators
	virtual void SetIsVisible(bool isVisible);
	virtual void SetX(int x); // Performs reset GraphicsContext
	virtual void SetY(int y); // Performs reset GraphicsContext
	virtual void SetLocation(int x, int y); // Performs reset GraphicsContext
	virtual void SetLocation(Location* location); // Performs reset GraphicsContext
	virtual void SetWidth(int width); // Performs reset GraphicsContext
	virtual void SetHeight(int height); // Performs reset GraphicsContext
	virtual void SetSize(int width, int height); // Performs reset GraphicsContext
	virtual void SetSize(Size* size); // Performs reset GraphicsContext
	virtual void SetRectangle(Rectangle* rect); // Performs reset GraphicsContext
	void SetMinimizedWindows(int isMinimized);
	void SetGraphics(GraphicsContext* graphics);
	Node* SetParent(Node* value) override;

	// Methods
	virtual void ProcessMessage(Message* msg);
	virtual void Draw(GraphicsContext* g);
	void AddChild(Node* nodeToAdd) override;
	void BringToFront();
	virtual void ResetGraphicsContext();
};