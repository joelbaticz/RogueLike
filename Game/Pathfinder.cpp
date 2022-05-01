#include "Pathfinder.h"
#include <queue>
#include "RendererFront.h"
#include "AssetManager.h"

//void Pathfinder::GetNextTile(TileMap* map, int sourceTileX, int sourceTileY, int targetTileX, int targetTileY, int& nextTileX, int& nextTileY)
//{
//	int diffX = targetTileX - sourceTileX;
//	int diffY = targetTileY - sourceTileY;
//	int dX = 0;
//	int dY = 0;
//	int choosenDX = 0;
//	int choosenDY = 0;
//
//	if (diffX == 0 && diffY == 0)
//	{
//		nextTileX = sourceTileX;
//		nextTileY = sourceTileY;
//	}
//
//	if (diffX != 0)
//	{
//		dX = diffX / abs(diffX);
//	}
//
//	if (diffY != 0)
//	{
//		dY = diffY / abs(diffY);
//	}
//
//	if (map->IsOccupied(sourceTileX + dX, sourceTileY + dY))
//	{
//		if (map->IsOccupied(sourceTileX + dX, sourceTileY))
//		{
//
//			if (map->IsOccupied(sourceTileX, sourceTileY + dY))
//			{
//				choosenDX = 0;
//				choosenDY = 0;
//			}
//			else
//			{
//				choosenDX = 0;
//				choosenDY = dY;
//			}
//		}
//		else
//		{
//			choosenDX = dX;
//			choosenDY = 0;
//		}
//	}
//	else
//	{
//		choosenDX = dX;
//		choosenDY = dY;
//	}
//
//	nextTileX = sourceTileX + choosenDX;
//	nextTileY = sourceTileY + choosenDY;	
//}
//



// TRYING




//void AddSurroundings(std::queue<PathNode> path, TileMap* map, PathNode node)
//{
//	if (!map->IsOccupied(node.x + 1, node.y))
//	{
//		PathNode rootNode = PathNode();
//		rootNode.x = node.x + 1;
//		rootNode.y = sourceTileY;
//		rootNode.cost = 0;
//		rootNode.isVisited = false;
//
//		path.push(node.x)
//	}
//}
//

PathFinder::PathFinder()
{}

PathFinder::~PathFinder()
{
	path.clear();
	delete this;
}

void AddSourceNode(std::vector<PathNode*>* path, TileMap* map, int x, int y)
{
	PathNode* newNode = new PathNode();
	newNode->x = x;
	newNode->y = y;
	newNode->cost = 0;

	path->push_back(newNode);
}

// Returns whether or not the source is found
void AddNodeIfFree(std::vector<PathNode*>* path, TileMap* map, int x, int y, int cost)
{
	if (!map->IsOccupied(x, y))
	{
		// It's free, we can move here

		for(int i = 0; i < path->size(); i++)
		{
			PathNode* nodeToCheck = path->at(i);
			if (nodeToCheck->x == x && nodeToCheck->y == y)
			{
				// Node already added

				return;
			}
		}

		PathNode* newNode = new PathNode();
		newNode->x = x;
		newNode->y = y;
		newNode->cost = cost;

		path->push_back(newNode);

		//int screenX = 50;
		//int screenY = 50;

		////map->IsoToScreen(x, y, screenX, screenY);

		//TextureAtlas* textureToDraw = AssetManager::CreateTextureAtlas(Configuration::UIPath + "Button.png");
		//textureToDraw->SetHorizontalCount(1);
		//textureToDraw->SetVerticalCount(5);
		//Rectangle rectSource = Rectangle();
		//
		//textureToDraw->GetTextureRectangle(0, &rectSource);

		//Rectangle rectDest = Rectangle();
		//rectDest.SetX(screenX);
		//rectDest.SetY(screenY);
		//rectDest.SetWidth(50);
		//rectDest.SetHeight(50);

		//RendererFront::ScreenDrawTexture(textureToDraw, &rectSource, &rectDest);
	}
}

PathFinder* PathFinder::pathFinderInstance = nullptr;


// It would be better to provide a list of PathNodes to fill in
void PathFinder::GetNextTile(TileMap* map, int sourceTileX, int sourceTileY, int targetTileX, int targetTileY, int& nextTileX, int& nextTileY)
{
	// Only perform pathfinding if Target is not occupied
	if (map->IsOccupied(targetTileX, targetTileY))
	{
		return;
	}

	if (pathFinderInstance == nullptr)
	{
		pathFinderInstance = new PathFinder();
		pathFinderInstance->path = std::vector<PathNode*>();
	}

	// Start from source

	bool foundTarget = false;
	int currentCost = 0;
	int nextCost = 0;
	int maxCost = 0;

	pathFinderInstance->path.clear();
	AddSourceNode(&pathFinderInstance->path, map, sourceTileX, sourceTileY);

	while (!foundTarget)
	{
		// Look up all nodes with cost = currentCost

		for (int i = 0; i < pathFinderInstance->path.size(); i++)
		{
			if (foundTarget)
			{
				continue;
			}

			PathNode* nodeToCheck = pathFinderInstance->path.at(i);
			nextCost = currentCost + 1;

			if (nodeToCheck->cost == currentCost)
			{
				// Add all surrounding nodes to the path if free

				for (int dy = -1; dy < 2; dy++)
				{
					for (int dx = -1; dx < 2; dx++)
					{
						if (foundTarget)
						{
							continue;
						}

						int nextX = nodeToCheck->x + dx;
						int nextY = nodeToCheck->y + dy;

						if (nextX == targetTileX && nextY == targetTileY)
						{
							maxCost = nextCost;
							foundTarget = true;
						}

						//else
						{
							AddNodeIfFree(&pathFinderInstance->path, map, nextX, nextY, nextCost);
						}
					}
				}
			}
		}

		currentCost = nextCost;
	}

	// Target was found, build path from target to source
	std::vector<PathNode*> selectedPath = std::vector<PathNode*>();
	map->ClearTileSelection();

	int prevCost = maxCost;
	int pathX = targetTileX;
	int pathY = targetTileY;

	bool foundPath = false;

	while (!foundPath)
	{

		int minStepCost = 10000;
		int chosenIndex = 0;
		for (int dy = -1; dy < 2; dy++)
		{
			for (int dx = -1; dx < 2; dx++)
			{
				int nextX = pathX + dx;
				int nextY = pathY + dy;

				for (int i = 0; i < pathFinderInstance->path.size(); i++)
				{
					PathNode* nodeToCheck = pathFinderInstance->path.at(i);

					int stepBackCost = abs(nodeToCheck->x - sourceTileX) + abs(nodeToCheck->y - sourceTileY);

					if (nodeToCheck->x == nextX && nodeToCheck->y == nextY && nodeToCheck->cost < prevCost && stepBackCost < minStepCost)
					{
						minStepCost = stepBackCost;
						chosenIndex = i;
					}
				}
			}
		}

		PathNode* nodeChoosen = pathFinderInstance->path.at(chosenIndex);

		if (nodeChoosen->x == sourceTileX && nodeChoosen->y == sourceTileY)
		{
			foundPath = true;
		}

		// Found surrounding tile that leads back to source
		PathNode* newWaybackNode = new PathNode();
		newWaybackNode->x = nodeChoosen->x;
		newWaybackNode->y = nodeChoosen->y;
		newWaybackNode->cost = nodeChoosen->cost;

		selectedPath.push_back(newWaybackNode);
		map->SelectTile(newWaybackNode->x, newWaybackNode->y, newWaybackNode->cost);

		pathX = nodeChoosen->x;
		pathY = nodeChoosen->y;
		prevCost = nodeChoosen->cost;
	}


	//for (int i = 0; i < selectedPath.size(); i++)
	//{
	//	PathNode* pathNode = selectedPath.at(i);
	//	map->SelectTile(pathNode->x, pathNode->y, pathNode->cost);
	//}

	//for (int i = 0; i < pathFinderInstance->path.size(); i++)
	//{
	//	PathNode* nodeToCheck = pathFinderInstance->path.at(i);

	//	if (nodeToCheck->x == targetTileX && nodeToCheck->y)
	//	{
	//		
	//	}

	//	map->SelectTile(nodeToCheck->x, nodeToCheck->y, nodeToCheck->cost);
	//}


	nextTileX = sourceTileX;
	nextTileY = sourceTileY;
	
}


//PathNode* nextNode = pathFinderInstance->path.front();
//pathFinderInstance->path.erase(pathFinderInstance->path.begin());
////pathFinder->path.pop_back();
//
//nextNode->isVisited = true;



