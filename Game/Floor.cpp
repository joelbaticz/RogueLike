#include "Floor.h"

Floor::Floor(Math::Vec4 pos, float size) : LevelObject()
{
	vertexList.clear();
	indexList.clear();

	this->texture = texture;

	float s = size / 2;

	int textureXCount = 1;
	int textureYCount = 1;
	int textureIndex = 0;
	

	float tX0 = (float)(textureIndex % textureXCount) / (float)(textureXCount);
	float tY0 = (float)(textureIndex / textureXCount) / (float)(textureYCount);
	float tX1 = tX0 + (1 / (float)textureXCount);
	float tY1 = tY0 + (1 / (float)textureYCount);

	//With Color
	//vertexList.push_back(Math::Vertex(Math::Vec4(pos.x - s, pos.y - s, pos.z - s), Math::Vec4(1.0, 0.1, 0.5, 0.3)));
	//vertexList.push_back(Math::Vertex(Math::Vec4(pos.x + s, pos.y - s, pos.z - s), Math::Vec4(1.0, 0.1, 0.5, 0.3)));
	//vertexList.push_back(Math::Vertex(Math::Vec4(pos.x + s, pos.y + s, pos.z - s), Math::Vec4(1.0, 0.1, 0.5, 0.3)));
	//vertexList.push_back(Math::Vertex(Math::Vec4(pos.x - s, pos.y + s, pos.z - s), Math::Vec4(1.0, 0.1, 0.5, 0.3)));

	//With Texture Coords
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x - s, pos.y - s, pos.z - s), Math::Vec2(tX0, tY0)));
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x + s, pos.y - s, pos.z - s), Math::Vec2(tX1, tY0)));
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x + s, pos.y - s, pos.z + s), Math::Vec2(tX1, tY1)));
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x - s, pos.y - s, pos.z + s), Math::Vec2(tX0, tY1)));

	CreateIndexBuffer();
}

Floor::~Floor()
{
	vertexList.clear();
	indexList.clear();
}

void Floor::CreateIndexBuffer()
{
	/*indexList.push_back(0);
	indexList.push_back(1);
	indexList.push_back(2);

	indexList.push_back(2);
	indexList.push_back(3);
	indexList.push_back(0);*/

	indexList.push_back(2);
	indexList.push_back(1);
	indexList.push_back(0);

	indexList.push_back(0);
	indexList.push_back(3);
	indexList.push_back(2);
}
