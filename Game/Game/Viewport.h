#pragma once
#include "CanvasNode.h"
#include "Level.h"
#include "Math.h"

class Viewport : public CanvasNode
{
private:
	Level*		renderedLevel;
	Math::Mat4	worldMatrix;
	float		rotationAngleX;
	float		rotationAngleY;
	float		rotationAngleZ;

public:
	Viewport();
	~Viewport();

	void SetRenderedLevel(Level* renderedLevel);
	void Draw(GraphicsContext* g) override;
};
