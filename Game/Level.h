#pragma once

#include <vector>
#include "LevelObject.h"
#include "Player3d.h"
#include "Math.h"

enum class GridCellType
{
	Empty = 0,
	Floor,
	Block,
	FenceN,
	FenceS,
	FenceW,
	FenceE,
};

class GridCell
{
public:
	int				posX;
	int				posY;
	GridCellType	cellType;

	LevelObject*	levelObject;
};

class Level
{
private:
	int						lastObjectIdGiven = 0;

	int						mapWidth;
	int						mapHeight;
	int						mapScale;		// How big each cell will be

	void FillLevel();
	void AddCellToGrid(int posX, int posY, GridCellType type);
	void AddToObjectList(LevelObject* levelObject);
	void RemoveFromObjectList(LevelObject* levelObject);

	void AddPlayer();
	bool IsPointInsideOfTriangle(std::vector<Math::Vertex> triangleVertices, float posX, float posZ);
public:
	std::vector<LevelObject*> objectList;
	std::vector<GridCell*>	gridCellList;
	Player3d* player;
	//std::vector<Actor*> listActors;

	Level(int width, int height);
	~Level();

	LevelObject* GetObjectFromId(int objectId);
	GridCell* GetGridCellFromObject(LevelObject* levelObject);
	LevelObject* GetObjectFromGridCell(GridCell* gridCell);
	void ReplaceCell(GridCell* gridCell, GridCellType newType);

	void UpdateState();
	bool IsFloorReached(Math::Vec4& position);

	void LoadLevelFromFile();
};
