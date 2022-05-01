#pragma once

#include "Rectangle.h" 
#include "Color.h"
#include "Font.h"
#include "Texture.h"

class GraphicsContext
{
private:
	Rectangle*	boundsRect;
	Rectangle*	clippingRect;
	Color*		penColor;
	Color*		fillColor;
public:
	GraphicsContext();
	~GraphicsContext();

	Rectangle* GetBounds();
	void SetBoundsRectangle(Rectangle* otherBoundsRect);
	Rectangle* GetClippingRectangle();
	void SetClippingRectangle(Rectangle* otherClippingRect);


	void SetPenColor(Color* color);
	void SetFillColor(Color* color);
	
	void BeginDraw();
	void EndDraw();
	void DrawLine(int x0, int y0, int x1, int y1);
	void DrawRectangle(int x0, int y0, int x1, int y1);
	void DrawFilledRectangle(int x0, int y0, int x1, int y1);
	void DrawText(std::string text, Font* font, int x, int y);
	void DrawTexture(Texture* texture, int x, int y);
	void DrawTexture(Texture* texture, Rectangle* rectSource, Rectangle* rectTarget);
};
