#include "TileMapLayer.h"
#include "AssetManager.h"
#include "RendererFront.h"
#include "GameSettings.h"

TileMapLayer::TileMapLayer(int rows, int columns, uint16_t* layerMapArray, std::string tileSetName)
{
	this->rows = rows;
	this->columns = columns;
	this->layerMapArray = layerMapArray;

	tileSet = AssetManager::CreateTextureAtlas(tileSetName);
	tileSet->SetHorizontalCount(4);
	tileSet->SetVerticalCount(4);
}

int TileMapLayer::GetTileValue(int tileX, int tileY)
{
	return layerMapArray[tileY * columns + tileX];
}

void TileMapLayer::ScreenDraw(int baseX, int baseY)
{
	int tileSize = 128;
	int tileWidth = tileSize;
	int tileHeight = tileSize;

	int tileSizeHalf = tileSize / 2;
	int tileSizeQuater = tileSize / 4;

	Rectangle sourceRect = Rectangle(0, 0, tileWidth, tileHeight);
	Rectangle targetRect = Rectangle(0, 0, tileWidth, tileHeight);

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < columns; x++)
		{
			uint8_t tileIndex = layerMapArray[y * columns + x];

			if (tileIndex != 65535)
			{
				tileSet->GetTextureRectangle(tileIndex, &sourceRect);

				int screenX = baseX + (x - y) * tileSizeHalf;
				int screenY = baseY + (x + y) * tileSizeQuater;

				targetRect.SetX(screenX);
				targetRect.SetY(screenY);

				RendererFront::ScreenDrawTexture(tileSet, &sourceRect, &targetRect);
			}
		}
	}

	return;

	//int tileWidth = 256;
	//int tileHeight = 256;

	//Rectangle sourceRect = Rectangle(0, 0, 16, 16);
	//Rectangle targetRect = Rectangle(0, 0, tileWidth, tileHeight);

	//int tileMapX = 0;
	//int tileMapY = 0;

	//for (int y = 0; y < rows; y++)
	//{
	//	for (int x = 0; x < columns; x++)
	//	{
	//		uint8_t textureIndex = layerMapArray[y * columns + x];

	//		tileSet->GetTextureRectangle(textureIndex, &sourceRect);

	//		targetRect.SetX(x * tileWidth + tileMapX);
	//		targetRect.SetY(y * tileHeight + tileMapY);

	//		RendererFront::ScreenDrawTexture(tileSet, &sourceRect, &targetRect);
	//	}
	//}

	//return;

	// Tile Draw Speed Test
	// 640x480x16bit- (120000 tiles @ 109 fps) - Memcpy
	// 640x480x16bit- (120000 tiles @ 49 fps) - ForLoop
	// 640x480x8bit- (120000 tiles @ 102 fps) - Memcpy	
	// 640x480x8bit- (120000 tiles @ 48 fps) - ForLoop

	//int renderedTiles = 0;
	//int tileSize = 16;

	//tileSet->GetTextureRectangle(1, &sourceRect);
	//sourceRect.SetWidth(tileSize);
	//sourceRect.SetHeight(tileSize);
	//targetRect.SetWidth(tileSize);
	//targetRect.SetHeight(tileSize);

	//for (int i = 0; i < 100; i++)
	//{
	//	for (int x = 0; x < RendererFront::GetWindowWidth() / tileSize; x++)
	//	{
	//		for (int y = 0; y < RendererFront::GetWindowHeight() / tileSize; y++)
	//		{
	//			targetRect.SetX(x * tileSize + tileMapX);
	//			targetRect.SetY(y * tileSize + tileMapY);

	//			RendererFront::ScreenDrawTexture(tileSet, &sourceRect, &targetRect);

	//			renderedTiles++;
	//		}
	//	}
	//}

	//RendererFront::ScreenDrawText("Rendered tiles:" + std::to_string(renderedTiles), AssetManager::GetDefaultFont(), 10, 160);
}

void TileMapLayer::ScreenDrawTile(int baseX, int baseY, int tileX, int tileY)
{
	int tileWidth = GameSettings::SpriteWidth;
	int tileHeight = GameSettings::SpriteHeight;
	int tileSize = tileWidth;

	int tileSizeHalf = tileSize / 2;
	int tileSizeQuater = tileSize / 4;

	Rectangle sourceRect = Rectangle(0, 0, tileWidth, tileHeight);
	Rectangle targetRect = Rectangle(0, 0, tileWidth, tileHeight);

	uint8_t tileIndex = layerMapArray[tileY * columns + tileX];

	if (tileIndex != 65535)
	{
		tileSet->GetTextureRectangle(tileIndex, &sourceRect);

		int screenX = baseX + (tileX - tileY) * tileSizeHalf;
		int screenY = baseY + (tileX + tileY) * tileSizeQuater;

		targetRect.SetX(screenX);
		targetRect.SetY(screenY);

		RendererFront::ScreenDrawTexture(tileSet, &sourceRect, &targetRect);
	}
}




