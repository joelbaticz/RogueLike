#include "Cube.h"

Cube::Cube(): LevelObject()
{
	vertexList.clear();
	indexList.clear();

	vertexList.push_back(Math::Vertex(Math::Vec4(-1.0f, -1.0f, -1.0f), Math::Vec4(1.0, 0.1, 0.7, 0.7)));
	vertexList.push_back(Math::Vertex(Math::Vec4( 1.0f, -1.0f, -1.0f), Math::Vec4(1.0, 0.1, 0.7, 0.7)));
	vertexList.push_back(Math::Vertex(Math::Vec4( 1.0f,  1.0f, -1.0f), Math::Vec4(1.0, 0.1, 0.7, 0.7)));
	vertexList.push_back(Math::Vertex(Math::Vec4(-1.0f,  1.0f, -1.0f), Math::Vec4(1.0, 0.1, 0.7, 0.7)));
	vertexList.push_back(Math::Vertex(Math::Vec4(-1.0f, -1.0f,  1.0f), Math::Vec4(1.0, 0.1, 0.7, 0.7)));
	vertexList.push_back(Math::Vertex(Math::Vec4( 1.0f, -1.0f,  1.0f), Math::Vec4(1.0, 0.1, 0.7, 0.7)));
	vertexList.push_back(Math::Vertex(Math::Vec4( 1.0f,  1.0f,  1.0f), Math::Vec4(1.0, 0.1, 0.7, 0.7)));
	vertexList.push_back(Math::Vertex(Math::Vec4(-1.0f,  1.0f,  1.0f), Math::Vec4(1.0, 0.1, 0.7, 0.7)));

	CreateIndexBuffer();
}

Cube::Cube(Math::Vec4 pos, float size): LevelObject()
{
	vertexList.clear();
	indexList.clear();

	float s = size / 2;

	int textureXCount = 1;
	int textureYCount = 1;

	int textureIndex = 0;

	float tX0 = (float)(textureIndex % textureXCount) / (float)(textureXCount);
	float tY0 = (float)(textureIndex / textureXCount) / (float)(textureYCount);
	//float tX1 = tX0 + (1 / (float)textureXCount);// - 0.01f;
	//float tY1 = tY0 + (1 / (float)textureYCount);// - 0.01f;

	float tX1 = (float)(textureIndex % textureXCount + 1) / (float)(textureXCount) - 0.001f;
	float tY1 = (float)(textureIndex / textureXCount + 1) / (float)(textureYCount) - 0.001f;

	//Top
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x - s, pos.y + s, pos.z - s), Math::Vec2(tX0, tY0)));
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x - s, pos.y + s, pos.z + s), Math::Vec2(tX0, tY1)));
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x + s, pos.y + s, pos.z + s), Math::Vec2(tX1, tY1)));
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x + s, pos.y + s, pos.z - s), Math::Vec2(tX1, tY0)));
						 
	//Left				 
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x - s, pos.y + s, pos.z + s), Math::Vec2(tX0, tY0)));
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x - s, pos.y - s, pos.z + s), Math::Vec2(tX1, tY0)));
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x - s, pos.y - s, pos.z - s), Math::Vec2(tX1, tY1)));
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x - s, pos.y + s, pos.z - s), Math::Vec2(tX0, tY1)));
						 
	//Right				 
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x + s, pos.y + s, pos.z + s), Math::Vec2(tX0, tY1)));
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x + s, pos.y - s, pos.z + s), Math::Vec2(tX1, tY1)));
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x + s, pos.y - s, pos.z - s), Math::Vec2(tX1, tY0)));
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x + s, pos.y + s, pos.z - s), Math::Vec2(tX0, tY0)));
						 
	//Front				 
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x + s, pos.y + s, pos.z + s), Math::Vec2(tX1, tY1)));
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x + s, pos.y - s, pos.z + s), Math::Vec2(tX1, tY0)));
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x - s, pos.y - s, pos.z + s), Math::Vec2(tX0, tY0)));
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x - s, pos.y + s, pos.z + s), Math::Vec2(tX0, tY1)));
						 
	//Back				 
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x + s, pos.y + s, pos.z - s), Math::Vec2(tX0, tY0)));
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x + s, pos.y - s, pos.z - s), Math::Vec2(tX0, tY1)));
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x - s, pos.y - s, pos.z - s), Math::Vec2(tX1, tY1)));
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x - s, pos.y + s, pos.z - s), Math::Vec2(tX1, tY0)));
						 
	//Bottom			 
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x - s, pos.y - s, pos.z - s), Math::Vec2(tX1, tY1)));
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x - s, pos.y - s, pos.z + s), Math::Vec2(tX1, tY0)));
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x + s, pos.y - s, pos.z + s), Math::Vec2(tX0, tY0)));
	vertexList.push_back(Math::Vertex(Math::Vec4(pos.x + s, pos.y - s, pos.z - s), Math::Vec2(tX0, tY1)));

	Cube::CreateIndexBuffer();
}

Cube::~Cube()
{
	vertexList.clear();
	indexList.clear();
}

void Cube::CreateIndexBuffer()
{
	//Top
	indexList.push_back(0);
	indexList.push_back(1);
	indexList.push_back(2);

	indexList.push_back(0);
	indexList.push_back(2);
	indexList.push_back(3);

	//Left
	indexList.push_back(5);
	indexList.push_back(4);
	indexList.push_back(6);

	indexList.push_back(6);
	indexList.push_back(4);
	indexList.push_back(7);

	//Right
	indexList.push_back(8);
	indexList.push_back(9);
	indexList.push_back(10);

	indexList.push_back(8);
	indexList.push_back(10);
	indexList.push_back(11);

	//Front
	indexList.push_back(13);
	indexList.push_back(12);
	indexList.push_back(14);

	indexList.push_back(15);
	indexList.push_back(14);
	indexList.push_back(12);

	//Back
	indexList.push_back(16);
	indexList.push_back(17);
	indexList.push_back(18);

	indexList.push_back(16);
	indexList.push_back(18);
	indexList.push_back(19);

	//Bottom
	indexList.push_back(21);
	indexList.push_back(20);
	indexList.push_back(22);

	indexList.push_back(22);
	indexList.push_back(20);
	indexList.push_back(23);
}
