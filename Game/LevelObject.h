#pragma once
#include <vector>
#include "Math.h"
#include "TextureAtlas.h"

class LevelObject
{
protected:
	int objectId;
	std::vector<Math::Vertex> vertexList;
	std::vector<int> indexList;
	TextureAtlas* texture;

	virtual void CreateIndexBuffer();
public:
	LevelObject();
	~LevelObject();

	int GetObjectId();
	void SetObjectId(int objectId);
	TextureAtlas* GetTexture();
	void SetTexture(TextureAtlas* texture);
	virtual std::vector<Math::Vertex> GetVertexList();
	virtual std::vector<int> GetIndexList();
};
