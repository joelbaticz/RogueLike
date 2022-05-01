#pragma once

#include "TileMap.h"
//#include <queue>

class PathNode
{
public:
	int x;
	int y;
	int cost;
	bool isVisited;
};

class PathFinder
{
	static PathFinder* pathFinderInstance;

	std::vector<PathNode*> path;
	PathFinder();
	~PathFinder();
public:
	static void GetNextTile(TileMap* map, int sourceTileX, int sourceTileY, int targetTileX, int targetTileY, int& nextTileX, int&nextTileY);
};
