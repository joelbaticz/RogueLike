#pragma once
#include <cstdint>
#include <string>
#include "TextureAtlas.h"

enum class TileMapLayerType
{
	Liquid = 0,
	Floor = 1,
	Walls = 2,
	Props = 3,
	Selection = 4,
	Occupy = 5
};

// Remark: this is only a storage class for map data
class TileMapLayer
{
private:
	int rows;
	int columns;
	
	TextureAtlas* tileSet;

public:
	uint16_t* layerMapArray;

	TileMapLayer(int rows, int columns, uint16_t* mapArray, std::string tileSetName);
	~TileMapLayer() = default;

	int GetTileValue(int tileX, int tileY);

	void ScreenDraw(int baseX, int baseY); // Uses the graphics context of the caller (ClippingRect and BoundingRect comes from the caller)
	void ScreenDrawTile(int baseX, int baseY, int tileX, int tileY);
};
