#pragma once

#include "ShapeNode.h"
#include "TileMapLayer.h"
#include "Actor2d.h"
#include <string>
#include <vector>


class TileMap: public ShapeNode
{
private:
	int id;
	std::string name;

	Color* colorBackground;

	TileMapLayer* layerLiquid;
	TileMapLayer* layerFloor;
	TileMapLayer* layerWall;
	TileMapLayer* layerProps;
	TileMapLayer* layerOccupy;
	TileMapLayer* layerSelection;

	std::vector<Actor2d*> actorList;

	int prevSelectedTileX;
	int prevSelectedTileY;
	int prevSelectedTileValue;

	void Init();
public:
	int selectedTileX;
	int selectedTileY;

	int tileWidth;
	int tileHeight;

	int rows;
	int columns;

	int originX;
	int originY;

	TileMap();
	TileMap(int id, int rows, int columns, int tileWidth, int tileHeight, std::string name);
	~TileMap();

	void ScreenToIso(int screenX, int screenY, int& tileX, int& tileY);
	void IsoToScreen(int tileX, int tileY, int& screenX, int& screenY);

	void SetCenter(int centerX, int centerY); // On which point the map should focus on
	void GetPlayerStartPosition(int& tileX, int& tileY);
	bool IsOccupied(int tileX, int tileY);

	void AddLayer(TileMapLayerType type, TileMapLayer* layer);
	void AddActor(Actor2d* actor);

	void SetMousePosition(int mouseX, int mouseY);

	void ScreenDraw(); // ScreenDraw uses the caller's graphics context

	void ClearTileSelection();
	void SelectTile(int tileX, int tileY, int distance);

	//void Draw(GraphicsContext* g) override;
};
