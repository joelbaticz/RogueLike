#pragma once

#include "LevelObject.h"
#include "TextureAtlas.h"

class Floor : public LevelObject
{
protected:
	void CreateIndexBuffer();
public:
	Floor(Math::Vec4 centerPos, float size);
	~Floor();
};