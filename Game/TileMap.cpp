#include "TileMap.h"
#include "Actor2d.h"
#include "AssetManager.h"
#include "RendererFront.h"
#include "GameSettings.h"

TileMap::TileMap()
{
	this->id = 1;
	this->name = "NewTileMapLayer";
	this->rows = 8;
	this->columns = 8;

	this->SetFillColor(AssetManager::CreateColor(255, 160, 160, 0));
	this->SetStrokeColor(AssetManager::CreateColor(255, 200, 200, 0));

	Init();
}

TileMap::TileMap(int id, int rows, int columns, int tileWidth, int tileHeight, std::string name)
{
	this->id = id;
	this->name = name;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	this->rows = rows;
	this->columns = columns;

	Init();
}

TileMap::~TileMap() = default;

void TileMap::Init()
{
	Size* mapSize = new Size(columns * tileWidth, rows * tileHeight);
	this->SetSize(mapSize);

	colorBackground = AssetManager::CreateColor(255, 60, 188, 252);

	this->SetIsVisible(true);
}

void TileMap::ScreenToIso(int screenX, int screenY, int& tileX, int& tileY)
{
	float tileSize = GameSettings::SpriteWidth;

	float screenWidth = RendererFront::GetWindowWidth();
	float screenHeight = RendererFront::GetWindowHeight();

	float centerX = screenWidth / 2;
	float centerY = screenHeight / 2;

	float baseX = centerX - (rows - columns) * (tileSize / 2) + tileSize / 2;
	float baseY = centerY - (rows + columns) * (tileSize / 4) + 2 * tileSize;

	float tempX = ((screenX - baseX) / tileSize);
	float tempY = (screenY - baseY) / (tileSize / 2);

	tileX = (tempY + tempX) + 1;
	tileY = (tempY - tempX);
}

void TileMap::IsoToScreen(int tileX, int tileY, int& screenX, int& screenY)
{
	int tileWidth = GameSettings::SpriteWidth;
	int tileHeight = GameSettings::SpriteHeight;
	int tileSize = tileWidth;

	int tileSizeHalf = tileSize / 2;
	int tileSizeQuater = tileSize / 4;

	float screenWidth = RendererFront::GetWindowWidth();
	float screenHeight = RendererFront::GetWindowHeight();

	float centerX = screenWidth / 2;
	float centerY = screenHeight / 2;

	int baseX = centerX - (rows - columns) * (tileSize / 2);
	int baseY = centerY - (rows + columns) * (tileSize / 4);
	//int baseX = originX - (rows - columns + 1) * (tileSize / 2);
	//int baseY = originY - (rows + columns - 1) * (tileSize / 2);

	screenX = baseX + (tileX - tileY) * tileSizeHalf;
	screenY = baseY + (tileX + tileY) * tileSizeQuater;
	//screenX = originX + (tileX - tileY) * tileSizeHalf;
	//screenY = originY + (tileX + tileY) * tileSizeQuater;


}

void TileMap::SetCenter(int centerX, int centerY)
{
	int tileWidth = GameSettings::SpriteWidth;
	int tileWidthHalf = tileWidth / 2;
	int tileHeight = tileWidthHalf;
	int tileHeightHalf = tileHeight / 2;

	originX = centerX - (rows - columns + 1) * tileWidthHalf;
	originY = centerY - (rows + columns - 1) * tileHeightHalf;
}


void TileMap::GetPlayerStartPosition(int& tileX, int& tileY)
{
	tileX = 0;
	tileY = 0;
}

bool TileMap::IsOccupied(int tileX, int tileY)
{
	if (tileX < 0 ||
		tileX >= columns ||
		tileY < 0 ||
		tileY >= rows)
	{
		return true;
	}

	if (layerOccupy->GetTileValue(tileX, tileY) == 65535)
	{
		return false;
	}

	return true;
}

void TileMap::SetMousePosition(int mouseX, int mouseY)
{
 	ScreenToIso(mouseX, mouseY, selectedTileX, selectedTileY);
}

void TileMap::ClearTileSelection()
{
	for (int y = 0; y < rows; y++)
	{
		for(int x = 0; x < columns; x++)
		{
			layerSelection->layerMapArray[y * columns + x] = 65535;
		}
	}
}

void TileMap::SelectTile(int tileX, int tileY, int distance)
{
	int offset = tileY * columns + tileX;

	if (distance < 16)
	{
		layerSelection->layerMapArray[offset] = distance;
		LogEngine::Log(LOG_ERROR, "SelectTile -- ", std::to_string(distance));
	}	
}

void TileMap::AddLayer(TileMapLayerType type, TileMapLayer* layer)
{
	if (type == TileMapLayerType::Liquid)
	{
		layerLiquid = layer;
	}
	else if (type == TileMapLayerType::Floor)
	{
		layerFloor = layer;
	}
	else if (type == TileMapLayerType::Walls)
	{
		layerWall = layer;
	}
	else if (type == TileMapLayerType::Props)
	{
		layerProps = layer;
	}
	else if (type == TileMapLayerType::Selection)
	{
		layerSelection = layer;
	}
	else if (type == TileMapLayerType::Occupy)
	{
		layerOccupy = layer;
	}
}

void TileMap::AddActor(Actor2d* actor)
{
	actorList.push_back(actor);
	actor->tileMap = this;
}

void TileMap::ScreenDraw()
{
	int tileWidth = GameSettings::SpriteWidth;
	int tileWidthHalf = tileWidth / 2;
	int tileHeight = tileWidthHalf;
	int tileHeightHalf = tileHeight / 2;

	float fElapsedTime = GameEngine::GetDeltaTime();

	// Tile Selection
	if (selectedTileX >= 0 && selectedTileX < columns && selectedTileY >= 0 && selectedTileY < rows)
	{
		layerSelection->layerMapArray[prevSelectedTileY * columns + prevSelectedTileX] = prevSelectedTileValue;
		
		prevSelectedTileValue = layerSelection->layerMapArray[selectedTileY * columns + selectedTileX] ;

		layerSelection->layerMapArray[selectedTileY * columns + selectedTileX] = 0;

		prevSelectedTileX = selectedTileX;
		prevSelectedTileY = selectedTileY;		
	}

	for (int tileY = 0; tileY < rows; tileY++)
	{
		for (int tileX = 0; tileX < columns; tileX++)
		{
			// Water
			layerLiquid->ScreenDrawTile(originX, originY, tileX, tileY);

			// Floor
			layerFloor->ScreenDrawTile(originX, originY, tileX, tileY);

			// Occupy
			layerOccupy->ScreenDrawTile(originX, originY, tileX, tileY);

			// Selection
			layerSelection->ScreenDrawTile(originX, originY, tileX, tileY);

			// Wall
			layerWall->ScreenDrawTile(originX, originY, tileX, tileY);

			// Find actor that is bound to this tile
			for (int i = 0; i < actorList.size(); i++)
			{
				Actor2d* actor = actorList.at(i);

				int currentTileX;
				int currentTileY;

				//if (actor->targetTileX)
				if ((int)actor->tileX == tileX && (int)actor->tileY == tileY)
				{
					actor->ScreenDrawAnimation(fElapsedTime);
				}
			}
		}
	}

	for (int tileY = 0; tileY < rows; tileY++)
	{
		for (int tileX = 0; tileX < columns; tileX++)
		{
			// Occupy
			//layerOccupy->ScreenDrawTile(originX, originY, tileX, tileY);
		}
	}

	//for (int i = 0; i < actorList.size(); i++)
	//{
	//	Actor2d* actor = actorList.at(i);

	//	actor->ScreenDrawAnimation(fElapsedTime);
	//}
}


