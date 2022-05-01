#pragma once

#include "CanvasNode.h"
#include "Color.h"

class ShapeNode : public CanvasNode
{
private:
	Color*					strokeColor;
	Color*					fillColor;
public:
	ShapeNode();
	~ShapeNode();

	Color* GetStrokeColor();
	void SetStrokeColor(Color* color);
	Color* GetFillColor();
	void SetFillColor(Color* color);

	void Draw(GraphicsContext* g) override;
};