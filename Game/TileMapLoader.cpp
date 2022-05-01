#include "TileMapLoader.h"
#include "GameSettings.h"

int TileMapLoader::lastIdUsed = 0;

TileMap* TileMapLoader::CreateNew()
{
	lastIdUsed++;

	if (lastIdUsed % 2 == 1)
	{
		//return CreateLevelLarge();
	}

	return CreateLevelSmall();
}

TileMap* TileMapLoader::CreateLevelLarge()
{
	int rows = 16;
	int columns = 16;

	TileMap* newTileMap = new TileMap(lastIdUsed, rows, columns, GameSettings::SpriteWidth, GameSettings::SpriteHeight, "LargeLevel");

	// [row][col]
	uint16_t* pMapArray = new uint16_t[rows * columns]
	{
		2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2,
		2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2,
		2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2,
		2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2,
		2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2,
		2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2,
		2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2,
		2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2,
		2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2,
		2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2,
		2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2,
		2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2,
		2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2,
		2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2,
		2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2,
		4,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2,
	};

	//newTileMap->layers.push_back(new TileMapLayer(rows, columns, pMapArray, "MasterGridFinal.png"));

	return newTileMap;
}

TileMap* TileMapLoader::CreateLevelSmall()
{
	int rows = 8;
	int columns = 8;
	int tileWidth = 64;
	int tileHeight = 32;

	uint16_t* pMapArray; // [row][col]

	TileMap* newTileMap = new TileMap(lastIdUsed, rows, columns, tileWidth, tileHeight, "SmallLevel");

	// LIQUID
	pMapArray = new uint16_t[rows * columns]
	{
		65535,  65535,  65535,  65535, 65535,  65535,  65535,  65535,  
		65535,  65535,  65535,  65535, 65535,  65535,  65535,  65535,
		65535,  65535,  65535,  65535, 65535,  65535,  65535,  65535,
		65535,  65535,  65535,  65535, 65535,  65535,  65535,  65535,
		65535,  65535,  65535,  65535, 65535,  65535,  65535,  65535,
		65535,  65535,  65535,  65535, 65535,  65535,  65535,  65535,
		65535,  65535,  65535,  65535, 65535,  65535,  65535,  65535,
		65535,  65535,  65535,  65535, 65535,  65535,  65535,  65535,
	};

	newTileMap->AddLayer(TileMapLayerType::Liquid, new TileMapLayer(rows, columns, pMapArray, "TileSet32bit-2.png"));

	// FLOOR
	pMapArray = new uint16_t[rows * columns]
	{
		1,  1,  1,  1,  1,  1,  1,  1,
		1,  1,  1,  1,  1,  1,  1,  1,
		1,  1,  1,  1,  1,  1,  1,  1,
		1,  1,  1,  1,  1,  1,  1,  1,
		1,  1,  1,  1,  1,  1,  1,  1,
		1,  1,  1,  1,  1,  1,  1,  1,
		1,  1,  1,  1,  1,  1,  1,  1,
		1,  1,  1,  1,  1,  1,  1,  1,
	};
	
	newTileMap->AddLayer(TileMapLayerType::Floor, new TileMapLayer(rows, columns, pMapArray, "TileSet32bit-2.png"));

	// WALLS
	pMapArray = new uint16_t[rows * columns]
	{
		65535,  65535,  65535,  65535, 65535,  65535,  65535,  65535,
		65535,  65535,  65535,  65535, 65535,  65535,  65535,  65535,
		65535, 3,   65535,  65535, 65535,  65535,  65535,  65535,
		65535, 2,   65535,  65535, 65535,  3,  65535,  65535,
		65535, 3,   65535,  65535, 65535,  2,  65535,  65535,
		65535, 2,   65535,  65535, 65535,  3,  65535,  65535,
		65535, 3,   65535,  65535, 65535,  2,  65535,  65535,
		65535, 2,   65535,  65535, 65535,  65535,  65535,  65535,
	};

	newTileMap->AddLayer(TileMapLayerType::Walls, new TileMapLayer(rows, columns, pMapArray, "TileSet32bit-2.png"));

	// OCCUPIED
	pMapArray = new uint16_t[rows * columns]
	{
		65535,  65535,  65535,  65535, 65535,  65535,  65535,  65535,
		65535,  65535,  65535,  65535, 65535,  65535,  65535,  65535,
		65535,      4,    65535,  65535, 65535,  65535,  65535,  65535,
		65535,      4,    65535,  65535, 65535,  4,  65535,  65535,
		65535,      4,    65535,  65535, 65535,  4,  65535,  65535,
		65535,      4,    65535,  65535, 65535,  4,  65535,  65535,
		65535,      4,    65535,  65535, 65535,  4,  65535,  65535,
		65535,      4,    65535,  65535, 65535,  65535,  65535,  65535,
	};

	newTileMap->AddLayer(TileMapLayerType::Occupy, new TileMapLayer(rows, columns, pMapArray, "TileSet32bit-2.png"));

	// TILE SELECTION
	pMapArray = new uint16_t[rows * columns]
	{
		65535,  65535,  65535,  65535, 65535,  65535,  65535,  65535,
		65535,  65535,  65535,  65535, 65535,  65535,  65535,  65535,
		65535,  65535,  65535,  65535, 65535,  65535,  65535,  65535,
		65535,  65535,  65535,  65535, 65535,  65535,  65535,  65535,
		65535,  65535,  65535,  65535, 65535,  65535,  65535,  65535,
		65535,  65535,  65535,  65535, 65535,  65535,  65535,  65535,
		65535,  65535,  65535,  65535, 65535,  65535,  65535,  65535,
		65535,  65535,  65535,  65535, 65535,  65535,  65535,  65535,
	};

	newTileMap->AddLayer(TileMapLayerType::Selection, new TileMapLayer(rows, columns, pMapArray, "TileSetSelection.png"));

	return newTileMap;
}