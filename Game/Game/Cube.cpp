#include "Cube.h"

Cube::Cube()
{
	vertexList.push_back({ -1.0f, -1.0f, -1.0f });
	vertexList.push_back({ 1.0f, -1.0f, -1.0f });
	vertexList.push_back({ 1.0f, 1.0f, -1.0f, });
	vertexList.push_back({ -1.0f, 1.0f, -1.0f, });
	vertexList.push_back({ -1.0f, -1.0f, 1.0f, });
	vertexList.push_back({ 1.0f, -1.0f, 1.0f, });
	vertexList.push_back({ 1.0f, 1.0f, 1.0f, });
	vertexList.push_back({ -1.0f, 1.0f, 1.0f });
}

Cube::Cube(Math::Vec4 pos, float size)
{
	float s = size / 2;
	vertexList.push_back({ pos.x - s, pos.y - s, pos.z - s });
	vertexList.push_back({ pos.x + s, pos.y - s, pos.z - s });
	vertexList.push_back({ pos.x + s, pos.y + s, pos.z - s });
	vertexList.push_back({ pos.x - s, pos.y + s, pos.z - s });
	vertexList.push_back({ pos.x - s, pos.y - s, pos.z + s });
	vertexList.push_back({ pos.x + s, pos.y - s, pos.z + s });
	vertexList.push_back({ pos.x + s, pos.y + s, pos.z + s });
	vertexList.push_back({ pos.x - s, pos.y + s, pos.z + s });

}

Cube::~Cube()
{
	vertexList.clear();
}

std::vector<Math::Vec4> Cube::GetVertexList()
{
	return vertexList;
}


