#pragma once

#include "LevelObject.h"

class Cube: public LevelObject
{
protected:
	void CreateIndexBuffer() override;
public:
	Cube();
	Cube(Math::Vec4 centerPos, float size);
	~Cube();
};