#include "GraphicsContext.h"
#include "AssetManager.h"

GraphicsContext::GraphicsContext()
{
	this->penColor = AssetManager::CreateColor(255, 0, 40, 80);
	this->fillColor = AssetManager::CreateColor(255, 0, 80, 120);
	this->boundsRect = new Rectangle();
	this->clippingRect = new Rectangle();
}

GraphicsContext::~GraphicsContext()
{
	delete this->clippingRect;
	delete this->boundsRect;
	delete this->fillColor;
	delete this->penColor;	
}

Rectangle* GraphicsContext::GetBounds()
{
	return this->boundsRect;
}

void GraphicsContext::SetBoundsRectangle(Rectangle* otherBoundsRect)
{
	this->boundsRect = otherBoundsRect;
}

Rectangle* GraphicsContext::GetClippingRectangle()
{
	return this->clippingRect;
}

void GraphicsContext::SetClippingRectangle(Rectangle* otherClippingRect)
{
	this->clippingRect = otherClippingRect;
}

void GraphicsContext::SetPenColor(Color* color)
{
	if (this->penColor != nullptr)
	{
		//delete this->penColor;
	}

	this->penColor = new Color(color);
	RenderingEngine::SetPenColor(penColor);
}

void GraphicsContext::SetFillColor(Color* color)
{
	if (this->fillColor != nullptr)
	{
		//delete this->fillColor;
	}

	this->fillColor = new Color(color);
	RenderingEngine::SetPenColor(fillColor);
}

void GraphicsContext::BeginDraw()
{
	//RenderingEngine::SetClippingRectangle(new Rectangle(0, 0, 800, 600));

	RenderingEngine::SetClippingRectangle(this->clippingRect);
	RenderingEngine::SetPenColor(this->penColor);
	RenderingEngine::SetFillColor(this->fillColor);
}

void GraphicsContext::EndDraw()
{}

void GraphicsContext::DrawLine(int x0, int y0, int x1, int y1)
{
	int boundsX = this->boundsRect->GetX();
	int boundsY = this->boundsRect->GetY();

	RenderingEngine::ScreenDrawLine(boundsX + x0, boundsY + y0, boundsX + x1, boundsY + y1);
}

void GraphicsContext::DrawRectangle(int x0, int y0, int x1, int y1)
{
	int boundsX = this->boundsRect->GetX();
	int boundsY = this->boundsRect->GetY();

	RenderingEngine::ScreenDrawRectangle(boundsX + x0, boundsY + y0, boundsX + x1, boundsY + y1);
}

void GraphicsContext::DrawFilledRectangle(int x0, int y0, int x1, int y1)
{
	int boundsX = this->boundsRect->GetX();
	int boundsY = this->boundsRect->GetY();

	RenderingEngine::ScreenDrawFilledRectangle(boundsX + x0, boundsY + y0, boundsX + x1, boundsY + y1);
}

void GraphicsContext::DrawText(std::string text, Font* font, int x, int y)
{}

void GraphicsContext::DrawTexture(Texture* texture, int x, int y)
{
	int boundsX = this->boundsRect->GetX();
	int boundsY = this->boundsRect->GetY();

	RenderingEngine::ScreenDrawTexture(texture, boundsX + x, boundsY + y);
}

void GraphicsContext::DrawTexture(Texture* texture, Rectangle* pRectSource, Rectangle* pRectTarget)
{
	Rectangle rectTargetWithBounds = Rectangle();
	Rectangle* pRectTargetWithBounds = &rectTargetWithBounds;
	int boundsX = this->boundsRect->GetX();
	int boundsY = this->boundsRect->GetY();

	pRectTargetWithBounds->SetX(boundsX + pRectTarget->GetX());
	pRectTargetWithBounds->SetY(boundsY + pRectTarget->GetY());
	pRectTargetWithBounds->SetWidth(pRectTarget->GetWidth());
	pRectTargetWithBounds->SetHeight(pRectTarget->GetHeight());

	RenderingEngine::ScreenDrawTexture(texture, pRectSource, pRectTargetWithBounds);
}

