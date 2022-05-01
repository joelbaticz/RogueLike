#include "GraphicsContext.h"
#include "AssetManager.h"
#include "RendererFront.h"

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
	RendererFront::SetPenColor(penColor);
}

void GraphicsContext::SetFillColor(Color* color)
{
	if (this->fillColor != nullptr)
	{
		//delete this->fillColor;
	}

	this->fillColor = new Color(color);
	RendererFront::SetFillColor(fillColor);
	//this->fillColor = color;
	//RendererFront::SetFillColor(color);
}

void GraphicsContext::SetDrawMode(DrawMode drawMode)
{
	RendererFront::SetDrawMode(drawMode);
}

void GraphicsContext::SetTexture(Texture* texture)
{
	RendererFront::SetTexture(texture);
}

void GraphicsContext::BeginDraw()
{
	//RendererFront::SetClippingRectangle(new Rectangle(0, 0, 800, 600));

	RendererFront::SetClippingRectangle(this->clippingRect);
	RendererFront::SetPenColor(this->penColor);
	RendererFront::SetFillColor(this->fillColor);
}

void GraphicsContext::EndDraw()
{}

void GraphicsContext::DrawLine(int x0, int y0, int x1, int y1)
{
	int boundsX = this->boundsRect->GetX();
	int boundsY = this->boundsRect->GetY();

	RendererFront::ScreenDrawLine(boundsX + x0, boundsY + y0, boundsX + x1, boundsY + y1);
}

void GraphicsContext::DrawRectangle(int x0, int y0, int x1, int y1)
{
	int boundsX = this->boundsRect->GetX();
	int boundsY = this->boundsRect->GetY();

	RendererFront::ScreenDrawRectangle(boundsX + x0, boundsY + y0, boundsX + x1, boundsY + y1);
}

void GraphicsContext::DrawFilledRectangle(int x0, int y0, int x1, int y1)
{
	int boundsX = this->boundsRect->GetX();
	int boundsY = this->boundsRect->GetY();

	RendererFront::ScreenDrawFilledRectangle(boundsX + x0, boundsY + y0, boundsX + x1, boundsY + y1);
}

void GraphicsContext::DrawText(std::string text, Font* font, int x, int y)
{
	int boundsX = this->boundsRect->GetX();
	int boundsY = this->boundsRect->GetY();

	RendererFront::ScreenDrawText(text, font, boundsX + x, boundsY + y);
}

void GraphicsContext::DrawTexture(Texture* texture, int x, int y)
{
	int boundsX = this->boundsRect->GetX();
	int boundsY = this->boundsRect->GetY();

	RendererFront::ScreenDrawTexture(texture, boundsX + x, boundsY + y);

	return;

	// With Triangles

	Math::Vertex v0, v1, v2, v3;

	float width = texture->GetWidth();
	float height = texture->GetHeight();

	v0.pos.x += x + boundsX;
	v0.pos.y += y + boundsY;

	v1.pos.x += x + width + boundsX;
	v1.pos.y += y + boundsY;

	v2.pos.x += x + width + boundsX;
	v2.pos.y += y + height + boundsY;

	v3.pos.x += x + boundsX;
	v3.pos.y += y + height + boundsY;

	RendererFront::SetTexture(texture);
	RendererFront::SetDrawMode(DrawMode::Lines);

	RendererFront::ScreenDrawTriangle(v0, v1, v2);
	RendererFront::ScreenDrawTriangle(v0, v2, v3);
}

void GraphicsContext::DrawTexture(Texture* texture, Rectangle* pRectSource, Rectangle* pRectTarget)
{
	int boundsX = this->boundsRect->GetX();
	int boundsY = this->boundsRect->GetY();
	Rectangle rectTargetWithBounds = Rectangle();
	Rectangle* pRectTargetWithBounds = &rectTargetWithBounds;

	pRectTargetWithBounds->SetX(boundsX + pRectTarget->GetX());
	pRectTargetWithBounds->SetY(boundsY + pRectTarget->GetY());
	pRectTargetWithBounds->SetWidth(pRectTarget->GetWidth());
	pRectTargetWithBounds->SetHeight(pRectTarget->GetHeight());

	RendererFront::ScreenDrawTexture(texture, pRectSource, pRectTargetWithBounds);

	return;

	// With Triangles

	Math::Vertex v0, v1, v2, v3;

	float sourceX0 = (float)pRectSource->GetX() / (float)texture->GetWidth();
	float sourceY0 = (float)pRectSource->GetY() / (float)texture->GetHeight();
	float sourceX1 = (float)(pRectSource->GetX() + pRectSource->GetWidth()) / (float)texture->GetWidth();
	float sourceY1 = (float)(pRectSource->GetY() + pRectSource->GetHeight()) / (float)texture->GetHeight();

	float targetX0 = pRectTargetWithBounds->GetX();
	float targetY0 = pRectTargetWithBounds->GetY();
	float targetX1 = pRectTargetWithBounds->GetX() + pRectTargetWithBounds->GetWidth();
	float targetY1 = pRectTargetWithBounds->GetY() + pRectTargetWithBounds->GetHeight();

	v0.objectId = 1;
	v0.pos.x = targetX0;
	v0.pos.y = targetY0;
	v0.uv.x = sourceX0;
	v0.uv.y = sourceY0;

	v1.objectId = 1;
	v1.pos.x = targetX1;
	v1.pos.y = targetY0;
	v1.uv.x = sourceX1;
	v1.uv.y = sourceY0;

	v2.objectId = 1;
	v2.pos.x = targetX1;
	v2.pos.y = targetY1;
	v2.uv.x = sourceX1;
	v2.uv.y = sourceY1;

	v3.objectId = 1;
	v3.pos.x = targetX0;
	v3.pos.y = targetY1;
	v3.uv.x = sourceX0;
	v3.uv.y = sourceY1;

	RendererFront::SetTexture(texture);
	RendererFront::SetDrawMode(DrawMode::Lines);

	RendererFront::ScreenDrawTriangle(v0, v1, v2);
	RendererFront::ScreenDrawTriangle(v0, v2, v3);
}

void GraphicsContext::DrawTriangle(Math::Vertex v0, Math::Vertex v1, Math::Vertex v2)
{
	int boundsX = this->boundsRect->GetX();
	int boundsY = this->boundsRect->GetY();

	v0.pos.x += boundsX;
	v0.pos.y += boundsY;

	v1.pos.x += boundsX;
	v1.pos.y += boundsY;

	v2.pos.x += boundsX;
	v2.pos.y += boundsY;

	RendererFront::ScreenDrawTriangle(v0, v1, v2);
}

