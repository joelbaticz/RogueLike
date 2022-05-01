#include "LevelObject.h"

LevelObject::LevelObject()
{
	vertexList.clear();
	indexList.clear();
}

LevelObject::~LevelObject()
{
}

int LevelObject::GetObjectId()
{
	return objectId;
}

void LevelObject::SetObjectId(int objectId)
{
	this->objectId = objectId;

	for (int i = 0; i < vertexList.size(); i++)
	{
		vertexList[i].objectId = objectId;
	}
}

TextureAtlas* LevelObject::GetTexture()
{
	return texture;
}

void LevelObject::SetTexture(TextureAtlas* texture)
{
	this->texture = texture;
}

std::vector<Math::Vertex> LevelObject::GetVertexList()
{
	return vertexList;
}

std::vector<int> LevelObject::GetIndexList()
{
	return indexList;
}

void LevelObject::CreateIndexBuffer()
{

}