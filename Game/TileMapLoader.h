#pragma once

#include "TileMap.h"

static class TileMapLoader
{
private:
	static int lastIdUsed;
public:
	static TileMap* CreateNew();
	static TileMap* Load();

	static TileMap* CreateLevelLarge();
	static TileMap* CreateLevelSmall();

};
