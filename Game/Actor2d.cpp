#include "Actor2d.h"
#include "AssetManager.h"
#include "RendererFront.h"
#include "TileMap.h"
#include "Pathfinder.h"

Actor2d::Actor2d(int tileX, int tileY)
{
	this->tileX = tileX;
	this->tileY = tileY;
	this->targetTileX = tileX;
	this->targetTileY = tileY;

	screenX = (float)tileX;
	screenY = (float)tileY;

	spriteWidth = 96;
	spriteHeight = 96;

	spriteOffsetX = 0;
	spriteOffsetY = 0;

	life = 100;

	textureByState[ActorState::Idle] = NULL;
	textureByState[ActorState::Walk] = NULL;

	animationPlayer = new AnimationPlayer(1, 1.0f);

	SetDirection(ActorDirection::N);
	SetState(ActorState::Idle);

}

Actor2d::~Actor2d() = default;

bool Actor2d::IsAlive()
{
	return this->life > 0;
}

ActorDirection Actor2d::GetDirection()
{
	return direction;
}

void Actor2d::SetDirection(ActorDirection direction)
{
	if (direction == GetDirection())
	{
		return;
	}

	this->direction = direction;
	//animationPlayer->ResetAnimation();
}

ActorState Actor2d::GetState()
{
	return state;
}

void Actor2d::MoveToTile(int tileX, int tileY)
{
	TileMap* currentMap = (TileMap*)tileMap;

	if (currentMap->IsOccupied(tileX, tileY))
	{
		return;
	}

	targetTileX = tileX;
	targetTileY = tileY;

	//HandleInput(PlayerInput::MoveToTile);
	SetState(ActorState::Walk);
}

void Actor2d::SetState(ActorState state)
{
	if (state == GetState())
	{
		return;
	}

	this->state = state;
	//animationPlayer->ResetAnimation();
}

void Actor2d::HandleInput(PlayerInput input)
{	
}

ActorDirection Actor2d::HandleDirection()
{
	ActorDirection newDirection = GetDirection();

	// Player control
	if (deltaY < 0 && deltaX == 0)
	{
		// North
		newDirection = ActorDirection::NE;
	}
	else if (deltaY < 0 && deltaX > 0)
	{
		// North East
		newDirection = ActorDirection::E;
	}
	else if (deltaY == 0 && deltaX > 0)
	{
		// East
		newDirection = ActorDirection::SE;
	}
	else if (deltaY > 0 && deltaX > 0)
	{
		// South East
		newDirection = ActorDirection::S;
	}
	else if (deltaY > 0 && deltaX == 0)
	{
		// South
		newDirection = ActorDirection::SW;
	}
	else if (deltaY > 0 && deltaX < 0)
	{
		// South West
		newDirection = ActorDirection::W;
	}
	else if (deltaY == 0 && deltaX < 0)
	{
		// West
		newDirection = ActorDirection::NW;
	}
	else if (deltaY < 0 && deltaX < 0)
	{
		// North West
		newDirection = ActorDirection::N;
	}

	return newDirection;
}

bool IsEqualWithinTolerance(float value, float expectedValue)
{
	float tolerance = 0.05f;

	if (value >= expectedValue - tolerance && value <= expectedValue + tolerance)
	{
		return true;
	}

	return false;
}

void Actor2d::HandleWalkState()
{
	TileMap* map = (TileMap*)tileMap;

	if (map == nullptr)
	{
		return;
	}

	int nextTileX = tileX;
	int nextTileY = tileY;

	//PathFinder::GetNextTile(map, tileX, tileY, targetTileX, targetTileY, nextTileX, nextTileY);

	if (IsEqualWithinTolerance(tileX, nextTileX) && IsEqualWithinTolerance(tileY, nextTileY))
	{
		SetState(ActorState::Idle);
		return;
	}

	int tileWidth = map->tileWidth;
	int tileHeight = map->tileHeight;

	float fElapsedTime = GameEngine::GetDeltaTime();
	float dTime = fElapsedTime / 1000;

	float moveSpeedInSecs = 0.75;
	float stepSpeed = 1 / (float)tileWidth;
	float moveToPerformInPixelsX = stepSpeed / moveSpeedInSecs;
	float moveToPerformInPixelsY = stepSpeed / moveSpeedInSecs / 2;


	// Accumulated elapsed time in accAmount
	accTime += dTime;

	// Is accumulated time larger than what's needed for one pixel movement in the screen?
	if (accTime < stepSpeed * moveSpeedInSecs)
	{
		return;
	}

	//if ((int)tileX != (int)targetTileX || (int)tileY != (int)targetTileY)

	//if (!IsEqualWithinTolerance(tileX, nextTileX) || !IsEqualWithinTolerance(tileY, nextTileY))
	{
		if (tileX < nextTileX)
		{
			deltaX += stepSpeed;
		}
		if (tileX > nextTileX)
		{
			deltaX += -stepSpeed;
		}
		if (tileY < nextTileY)
		{
			deltaY += stepSpeed;
		}
		if (tileY > nextTileY)
		{
			deltaY += -stepSpeed;
		}

		//if (deltaX != 0 || deltaY != 0)
		//if (!IsEqualWithinTolerance(accAmount, 0) || !IsEqualWithinTolerance(accAmount, 0))
		{
			tileX += deltaX;
			tileY += deltaY;

			SetState(ActorState::Walk);
			SetDirection(HandleDirection());

			deltaX = 0;
			deltaY = 0;
		}

	}
	//else
	//{
	//	deltaX = 0;
	//	deltaY = 0;
	//	SetState(ActorState::Idle);
	//}

	accTime = 0;

}

void Actor2d::Update()
{	
	if (GetState() != ActorState::Walk)
	{
		return;
	}

	HandleWalkState();
}

void Actor2d::SetTextureAtlas(ActorState state, TextureAtlas* textureAtlas)
{
	textureByState[state] = textureAtlas;
}

void Actor2d::ScreenDraw()
{
	Rectangle sourceRect = Rectangle(0, 0, 0, 0);
	Rectangle targetRect = Rectangle((int)screenX + spriteOffsetX, (int)screenY + spriteOffsetY, spriteWidth, spriteHeight);

	textureAtlasIdle->GetTextureRectangle((int)direction, &sourceRect);

	RendererFront::ScreenDrawTexture(textureAtlasIdle, &sourceRect, &targetRect);
}

void Actor2d::ScreenDrawAnimation(float elapsedTime)
{
	TileMap* map = (TileMap*)tileMap;

	int tileWidth = map->tileWidth;
	int tileHeight = map->tileHeight;
	int tileWidthHalf = tileWidth / 2;
	int tileHeightHalf = tileHeight / 2;
	int originX = map->originX;
	int originY = map->originY;

	// Calculate Tile Center (the actor sprite can be of different sizes)
 	screenX = originX + (tileX - tileY) * tileWidthHalf + tileWidthHalf;
	screenY = originY + (tileX + tileY) * tileHeightHalf + tileHeightHalf +(2 * tileHeight);

	// Perform sprite size correction
	screenX -= spriteWidth / 2 - spriteOffsetX;
	screenY -= spriteHeight / 2 - spriteOffsetY;

	int maxFrame = animationPlayer->GetMaxFrame();
	int currentFrame = animationPlayer->GetCurrentFrame(elapsedTime);

	Rectangle sourceRect = Rectangle(0, 0, 0, 0);
	Rectangle targetRect = Rectangle((int)screenX, (int)screenY, spriteWidth, spriteHeight);

	TextureAtlas* currentTextureAtlas = textureByState[state];

	if (currentTextureAtlas == NULL)
	{
		return;
	}

	currentTextureAtlas->GetTextureRectangle((int)direction * maxFrame + currentFrame, &sourceRect);

	RendererFront::ScreenDrawTexture(currentTextureAtlas, &sourceRect, &targetRect);



	// Draw Path

	int nextTileX = 0;
	int nextTileY = 0;

	// Actually check if 
	//if (targetTileX != 0 && targetTileY != 0)
	{
		PathFinder::GetNextTile(map, tileX, tileY, targetTileX, targetTileY, nextTileX, nextTileY);
	}

	
}

