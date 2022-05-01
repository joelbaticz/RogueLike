#include "Level.h"
#include "Cube.h"
#include "Floor.h"
#include "TextureAtlas.h"
#include "AssetManager.h"
#include "Player3d.h"

Level::Level(int width, int height)
{
	this->mapWidth = width;
	this->mapHeight = height;
	this->mapScale = 64;//48;

	FillLevel();
	
	AddPlayer();
}

Level::~Level()
{

}

void Level::UpdateState()
{
	player->UpdateState(this);
}


void Level::FillLevel()
{
	//Create null gridcells for entire map
	for (int y = 0; y < mapHeight; y++)
	{
		for (int x = 0; x < mapWidth; x++)
		{
			GridCell* nullCell = new GridCell();
			gridCellList.push_back(nullCell);
		}
	}

	//Fill the map with Empty cells
	for (int y = 0; y < mapHeight; y++)
	{
		for (int x = 0; x < mapWidth; x++)
		{
			Level::AddCellToGrid(x, y, GridCellType::Empty);
		}
	}

	//Create some floor
	for (int y = 4; y < 16; y++)
	{
		for (int x = 4; x < 16; x++)
		{
			if (x == 4 || y == 4)
			{
				Level::AddCellToGrid(x, y, GridCellType::Block);
			}
			else
			{
				Level::AddCellToGrid(x, y, GridCellType::Floor);
			}			
		}
	}

	AddCellToGrid(0, 0, GridCellType::Block);
}

void Level::AddCellToGrid(int posX, int posY, GridCellType type)
{
	int objectId = ++lastObjectIdGiven;

	if (type == GridCellType::Empty)
	{
		Floor* newFloor = new Floor(Math::Vec4(posX * mapScale, 0.0f, posY * mapScale), mapScale);
		newFloor->SetTexture(AssetManager::CreateTextureAtlas("TestTexture3.png"));
		newFloor->SetObjectId(objectId);

		GridCell* newCell = new GridCell();
		newCell->posX = posX;
		newCell->posY = posY;
		newCell->cellType = GridCellType::Empty;
		//newCell->levelObject = nullptr;
		newCell->levelObject = newFloor;

		int offset = posY * mapWidth + posX;
		GridCell* oldCell = gridCellList[offset];
		gridCellList[offset] = newCell;
		
		AddToObjectList(newCell->levelObject);
		RemoveFromObjectList(oldCell->levelObject);

		delete oldCell;
	}
	else if (type == GridCellType::Floor)
	{
		Floor* newFloor = new Floor(Math::Vec4(posX * mapScale, 0.0f, posY * mapScale), mapScale);
		newFloor->SetTexture(AssetManager::CreateTextureAtlas("TestTexture8.png"));
		newFloor->SetObjectId(objectId);

		GridCell* newCell = new GridCell();
		newCell->posX = posX;
		newCell->posY = posY;
		newCell->cellType = GridCellType::Floor;
		newCell->levelObject = newFloor;

		int offset = posY * mapWidth + posX;
		GridCell* oldCell = gridCellList[offset];
		gridCellList[offset] = newCell;

		AddToObjectList(newCell->levelObject);
		RemoveFromObjectList(oldCell->levelObject);

		delete oldCell;
	}
	else if (type == GridCellType::Block)
	{
		Cube* newCube = new Cube(Math::Vec4(posX * mapScale, 0.0f, posY * mapScale), mapScale);
		newCube->SetTexture(AssetManager::CreateTextureAtlas("TestTexture9.png"));
		newCube->SetObjectId(objectId);

		GridCell* newCell = new GridCell();
		newCell->posX = posX;
		newCell->posY = posY;
		newCell->cellType = GridCellType::Floor;
		newCell->levelObject = newCube;

		int offset = posY * mapWidth + posX;
		GridCell* oldCell = gridCellList[offset];
		gridCellList[offset] = newCell;

		AddToObjectList(newCell->levelObject);
		RemoveFromObjectList(oldCell->levelObject);

		delete oldCell;
	}
}

void Level::AddToObjectList(LevelObject* levelObject)
{
	if (levelObject == nullptr)
	{
		return;
	}

	objectList.push_back(levelObject);
}

void Level::RemoveFromObjectList(LevelObject* levelObject)
{
	if (levelObject == nullptr)
	{
		return;
	}

	for (int i = 0; i < objectList.size(); i++)
	{
		if (objectList[i]->GetObjectId() == levelObject->GetObjectId())
		{
			objectList.erase(objectList.begin() + i);
		}
	}

	delete levelObject;
}

LevelObject* Level::GetObjectFromId(int objectId)
{
	for (int i = 0; i < objectList.size(); i++)
	{
		if (objectList[i]->GetObjectId() == objectId)
		{
			return  objectList[i];
			
		}
	}

	return nullptr;
}

GridCell* Level::GetGridCellFromObject(LevelObject* levelObject)
{
	for (GridCell* gridCell : gridCellList)
	{
		if (gridCell->levelObject->GetObjectId() == levelObject->GetObjectId())
		{
			return gridCell;
		}
	}

	return nullptr;
}

LevelObject* Level::GetObjectFromGridCell(GridCell* gridCell)
{
	return gridCell->levelObject;
}


void Level::ReplaceCell(GridCell* gridCell, GridCellType newType)
{
	int posX = gridCell->posX;
	int posY = gridCell->posY;
	int objectId = gridCell->levelObject->GetObjectId();
	LevelObject* oldObject = nullptr;
	LevelObject* newObject = nullptr;

	if (gridCell->levelObject != nullptr)
	{
		oldObject = gridCell->levelObject;
	}

	if (newType == GridCellType::Empty)
	{
		newObject = new Floor(Math::Vec4(posX * mapScale, 0.0f, -posY * mapScale), mapScale);
		newObject->SetTexture(AssetManager::CreateTextureAtlas("TestTexture3.png"));
		newObject->SetObjectId(objectId);

	}
	else if (newType == GridCellType::Floor)
	{
		newObject = new Floor(Math::Vec4(posX * mapScale, 0.0f, -posY * mapScale), mapScale);
		newObject->SetTexture(AssetManager::CreateTextureAtlas("TestTexture8.png"));
		newObject->SetObjectId(objectId);
	}
	else if (newType == GridCellType::Block)
	{
		newObject = new Cube(Math::Vec4(posX * mapScale, 0.0f, - posY * mapScale), mapScale);
		newObject->SetTexture(AssetManager::CreateTextureAtlas("TestTexture7.png"));
		newObject->SetObjectId(objectId);
	}

	gridCell->cellType = newType;
	gridCell->levelObject = newObject;

	RemoveFromObjectList(oldObject);
	AddToObjectList(newObject);
	//delete oldObject;
}

void Level::AddPlayer()
{
	this->player = new Player3d(Math::Vec4(-0.0f, 300.0f, 0.0f));
}

bool Level::IsFloorReached(Math::Vec4& position)
{
	//for (int i = 0; i < objectList.size(); i++)
	//{
	//	if (dynamic_cast<Floor*>(objectList[i]))
	//	{
	//		//It's a floor (4 vertices)
	//		std::vector<Math::Vertex> objectVertices = objectList[i]->GetVertexList();
	//		std::vector<int> objectIndices = objectList[i]->GetIndexList();

	//		std::vector<Math::Vertex> triangleVertrices;
	//		
	//		for (int j = 0; j < objectIndices.size(); j += 3)
	//		{
	//			triangleVertrices.clear();
	//			triangleVertrices.push_back(objectVertices[objectIndices[j]]);
	//			triangleVertrices.push_back(objectVertices[objectIndices[j + 1]]);
	//			triangleVertrices.push_back(objectVertices[objectIndices[j + 2]]);

	//			if (IsPointInsideOfTriangle(triangleVertrices, position.x, position.z))
	//			{
	//				//TODO: do sliding down effect by modifying this method to slowly decrease the passed in position
	//				//      with the difference between the max and the min Z in the triangle
	//				if (position.y <= triangleVertrices[0].pos.y)
	//				{
	//					return true;
	//				}
	//			}
	//		}
	//	}
	//	else if (dynamic_cast<Cube*>(objectList[i]))
	//	{
	//		//It's a cube (24 vertices)
	//		std::vector<Math::Vertex> objectVertices = objectList[i]->GetVertexList();
	//		std::vector<int> objectIndices = objectList[i]->GetIndexList();

	//		std::vector<Math::Vertex> triangleVertrices;

	//		for (int j = 0; j < objectIndices.size(); j += 3)
	//		{
	//			triangleVertrices.clear();
	//			triangleVertrices.push_back(objectVertices[objectIndices[j]]);
	//			triangleVertrices.push_back(objectVertices[objectIndices[j + 1]]);
	//			triangleVertrices.push_back(objectVertices[objectIndices[j + 2]]);

	//			if (IsPointInsideOfTriangle(triangleVertrices, position.x, position.z))
	//			{
	//				//TODO: do sliding down effect by modifying this method to slowly decrease the passed in position
	//				//      with the difference between the max and the min Z in the triangle
	//				if (position.y <= triangleVertrices[0].pos.y)
	//				{
	//					return true;
	//				}
	//			}
	//		}

	//	}
	//	else
	//	{
	//		//It's something else?
	//	}

	//	
	//}


	return false;
}

bool Level::IsPointInsideOfTriangle(std::vector<Math::Vertex> triangleVertices, float posX, float posZ)
{
	float minX = 65535.0f;
	float minZ = 65535.0f;
	float maxX = -65535.0f;
	float maxZ = -65535.0f;

	for (int i = 0; i < 3; i++)
	{
		if (minX > triangleVertices[i].pos.x)
		{
			minX = triangleVertices[i].pos.x;
		}
		if (minZ > triangleVertices[i].pos.z)
		{
			minZ = triangleVertices[i].pos.z;
		}
		if (maxX < triangleVertices[i].pos.x)
		{
			maxX = triangleVertices[i].pos.x;
		}
		if (maxZ < triangleVertices[i].pos.z)
		{
			maxZ = triangleVertices[i].pos.z;
		}
	}

	if (posX > maxX || posZ > maxZ || posX < minX || posZ < minZ)
	{
		return false;
	}

	return true;
}