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
}

void ShapeNode::Draw(GraphicsContext* g)
{
	//return;

	//LogEngine::Log(LOG_DEBUG, "ShapeNode", "Draw() called on " + this->GetName());

	//Location* location = this->GetLocation();
	//Size* size = this->GetSize();

	//int width = size->GetWidth();
	//int height = size->GetHeight();

	//int x0 = location->GetX();
	//int y0 = location->GetY();
	//int x1 = x0 + width;
	//int y1 = x0 + height;

	////Rectangle rectBounds = Rectangle(x0, y0, width, height);
	//Rectangle rectBounds = Rectangle(this->GetLocation()->GetX(), this->GetLocation()->GetY(), this->GetSize()->GetWidth(), this->GetSize()->GetHeight());
	//Rectangle* pRectBounds = &rectBounds;
	////Rectangle* pRectClipping =
	//	RenderingEngine::ClipToParentRectangle(this, pRectBounds);

	//RenderingEngine::SetClippingRectangle(pRectBounds);

	//RenderingEngine::SetPenColor(strokeColor);
	//RenderingEngine::SetFillColor(fillColor);
	//RenderingEngine::DrawFilledRectangle(this, 0 , 0, this->GetSize()->GetWidth(), this->GetSize()->GetHeight());
	////RenderingEngine::ScreenDrawFilledRectangle(x0, y0, x1, y1);
	//RenderingEngine::ScreenDrawFilledRectangle(this->GetLocation()->GetX(), this->GetLocation()->GetY(), this->GetSize()->GetWidth(), this->GetSize()->GetHeight());


	////Don't bubble upwards
	////super::Draw();

	int width = this->GetSize()->GetWidth();
	int height = this->GetSize()->GetHeight();

	g->BeginDraw();

	//g->SetFillColor(AssetManager::CreateColor(255, 128, 80, 80));
	//g->SetPenColor(AssetManager::CreateColor(255, 192, 80, 80));

	g->DrawFilledRectangle(0, 0, width, height);
	g->DrawRectangle(0, 0, width, height);

	g->EndDraw();

	//RenderingEngine::SetClippingRectangle(g->GetClippingRectangle());

	//RenderingEngine::SetPenColor(strokeColor);
	//RenderingEngine::SetFillColor(fillColor);
	//RenderingEngine::DrawFilledRectangle(this, 0 , 0, this->GetSize()->GetWidth(), this->GetSize()->GetHeight());

	//A SCREENDRAW-val van valami baj (illetve a width es height-tal)

	//RenderingEngine::ScreenDrawFilledRectangle(x0, y0, x1, y1);
	//RenderingEngine::ScreenDrawFilledRectangle(g->GetBounds()->GetX(), g->GetBounds()->GetY(), g->GetBounds()->GetWidth(), g->GetBounds()->GetHeight());
	
	//RenderingEngine::SetFillColor(AssetManager::CreateColor(255, 80, 80, 0));
	//RenderingEngine::ScreenDrawFilledRectangle(g->GetClippingRectangle()->GetX(), g->GetClippingRectangle()->GetY(), g->GetClippingRectangle()->GetWidth(), g->GetClippingRectangle()->GetHeight());
	//RenderingEngine::SetFillColor(AssetManager::CreateColor(255, 192, 192, 0));
	//RenderingEngine::ScreenDrawRectangle(g->GetClippingRectangle()->GetX(), g->GetClippingRectangle()->GetY(), g->GetClippingRectangle()->GetWidth(), g->GetClippingRectangle()->GetHeight());

}
