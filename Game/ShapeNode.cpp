#include "ShapeNode.h"
#include "AssetManager.h"

ShapeNode::ShapeNode(): CanvasNode()
{
	SetName("Shape");
	strokeColor = AssetManager::GetDefaultPenColor();
	fillColor = AssetManager::GetDefaultFillColor();
	
	//We don't need this, since the CanvasNode will handle this!!!
	/*SDL_Rect* newRect = new SDL_Rect();
	newRect->x = 50;
	newRect->y = 50;
	newRect->w = 50;
	newRect->h = 50;
	SetRect(newRect);*/
}

ShapeNode::~ShapeNode()
{
}

Color* ShapeNode::GetStrokeColor()
{
	return strokeColor;
}

void ShapeNode::SetStrokeColor(Color* value)
{
	strokeColor = new Color(value);

	this->GetGraphics()->SetPenColor(strokeColor);
}

Color* ShapeNode::GetFillColor()
{
	return fillColor;
}

void ShapeNode::SetFillColor(Color* value)
{
	fillColor = new Color(value);
	this->GetGraphics()->SetFillColor(fillColor);

	//fillColor = value;
	//this->GetGraphics()->SetFillColor(value);
}

void ShapeNode::Draw(GraphicsContext* g)
{
	int width = this->GetWidth();
	int height = this->GetHeight();

	g->BeginDraw();

	g->DrawFilledRectangle(0, 0, width, height);
	g->DrawRectangle(0, 0, width, height);

	g->EndDraw();
}
