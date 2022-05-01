#pragma once

#include "ShapeNode.h"

class Test1 : public ShapeNode
{
public:
	Test1();
	~Test1();

	void Update() override;
	void Draw(GraphicsContext* g) override;
};
