#pragma once

#include <vector>
#include "GraphicsContext.h"
#include "Math.h"

class Cube
{
private:
	std::vector<Math::Vec4> vertexList;

public:
	Cube();
	Cube(Math::Vec4 centerPos, float size);
	~Cube();

	std::vector<Math::Vec4> GetVertexList();
};