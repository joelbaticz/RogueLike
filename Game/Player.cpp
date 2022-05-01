#include "Player.h"
#include "AssetManager.h"
#include "Projectile.h"
#include "TileMap.h"

Player::Player(int locationX, int locationY, PlayerType type) : Actor2d(locationX, locationY)
{
	this->type = type;

	SetupAssets();
}

Player::~Player() = default;

void Player::SetupAssets()
{
	if (type == PlayerType::Mage)
	{
		TextureAtlas* taIdle = AssetManager::CreateTextureAtlas("Mage-IdleTown.png");
		taIdle->SetHorizontalCount(20);
		taIdle->SetVerticalCount(8);

		TextureAtlas* taWalk = AssetManager::CreateTextureAtlas("Mage-Walk.png");
		taWalk->SetHorizontalCount(8);
		taWalk->SetVerticalCount(8);

		TextureAtlas* taFire = AssetManager::CreateTextureAtlas("Mage-Fire.png");
		taFire->SetHorizontalCount(12);
		taFire->SetVerticalCount(8);

		SetTextureAtlas(ActorState::Idle, taIdle);
		SetTextureAtlas(ActorState::Walk, taWalk);
		SetTextureAtlas(ActorState::Attack, taFire);
	}
	else
	{
		throw new std::logic_error("Player type not implemented");
	}
}

void Player::SetState(ActorState state)
{
	if (GetState() != state)
	{
		Actor2d::SetState(state);

		SetAnimationProperties();
	}
}

void Player::SetAnimationProperties()
{
	if (type == PlayerType::Mage)
	{
		if (state == ActorState::Idle)
		{
			animationPlayer->SetMaxFrame(20);
			animationPlayer->SetAnimationLength(3.0); // Anim length in secs
			spriteOffsetX = 0;
			spriteOffsetY = 0;
			spriteWidth = 96;
			spriteHeight = 96;
		}
		else if (state == ActorState::Walk)
		{
			animationPlayer->SetMaxFrame(8);
			animationPlayer->SetAnimationLength(0.5);
			spriteOffsetX = 0;
			spriteOffsetY = 0;
			spriteWidth = 96;
			spriteHeight = 96;
		}
		else if (state == ActorState::Attack)
		{
			animationPlayer->SetMaxFrame(12);
			animationPlayer->SetAnimationLength(0.5);
			spriteOffsetX = 0;
			spriteOffsetY = -16;
			spriteWidth = 128;
			spriteHeight = 128;
		}
	}
}

void Player::MoveToSelectedTile()
{
	TileMap* currentMap = (TileMap*)tileMap;

	int tileX = currentMap->selectedTileX;
	int tileY = currentMap->selectedTileY;

	MoveToTile(tileX, tileY);
}


void Player::HandleInput(PlayerInput input)
{
	if (input == PlayerInput::AttackTile)
	{
		TileMap* currentMap = (TileMap*)tileMap;

		int tileDiffX = (currentMap->selectedTileX - tileX);
		int tileDiffY = (currentMap->selectedTileY - tileY);

		float dirX = 0;
		float dirY = 0;

		if (tileDiffX != 0)
		{
			dirX = tileDiffX / abs(tileDiffX);
		}

		if (tileDiffY != 0)
		{
			dirY = tileDiffY / abs(tileDiffY);
		}


		int sX;
		int sY;

 		currentMap->IsoToScreen(7, 7, sX, sY);

		projectiles->push_back(new Projectile(sX, sY, dirX, dirY, 1));
	}

	return;

	float fElapsedTime = GameEngine::GetDeltaTime();
	float dAmount = deltaAmount * fElapsedTime;

	ActorState currentState = GetState();

	switch(currentState)
	{
	case ActorState::Attack:
		// Wait to finish attack
		return;

	case ActorState::Idle:
	case ActorState::Walk:
		if (input == PlayerInput::Attack1)
		{
			// Start attack
			SetState(ActorState::Attack);

			float dirX = 0;
			float dirY = 0;

			if (GetDirection() == ActorDirection::S)
			{
				dirY = 1;
			}
			if (GetDirection() == ActorDirection::SW)
			{
				dirX = -1;
				dirY = 1;
			}
			if (GetDirection() == ActorDirection::W)
			{
				dirX = -1;
			}
			if (GetDirection() == ActorDirection::NW)
			{
				dirX = -1;
				dirY = -1;
			}

			if (GetDirection() == ActorDirection::N)
			{
				dirY = -1;
			}
			if (GetDirection() == ActorDirection::NE)
			{
				dirX = 1;
				dirY = -1;
			}
			if (GetDirection() == ActorDirection::E)
			{
				dirX = 1;
			}
			if (GetDirection() == ActorDirection::SE)
			{
				dirX = 1;
				dirY = 1;
			}

			projectiles->push_back(new Projectile(screenX, screenY, dirX, dirY, 1));
		}
		if (input == PlayerInput::MoveUp)
		{
			deltaY -= dAmount;
		}
		else if (input == PlayerInput::MoveDown)
		{
			deltaY += dAmount;
		}
		else if (input == PlayerInput::MoveRight)
		{
			deltaX += dAmount;
		}
		else if (input == PlayerInput::MoveLeft)
		{
			deltaX -= dAmount;
		}
		else if (input == PlayerInput::MoveToTile)
		{
			deltaX = (tileX - targetTileX) / dAmount;
			deltaY = (tileY - targetTileY) / dAmount;
		}
		else if (input == PlayerInput::AttackTile)
		{
			int tileDiffX = (tileX - targetTileX);
			int tileDiffY = (tileY - targetTileY);

			float dirX = tileDiffX / tileX;
			float dirY = tileDiffY / tileY;

			int sX;
			int sY;

			

			projectiles->push_back(new Projectile(tileX, tileY, dirX, dirY, 1));
		}

		break;
	}
}

void Player::Update()
{
	Actor2d::Update();

	return;

	ActorState currentState = GetState();
	ActorDirection newDirection = HandleDirection();

	// It can crash if we call SetDirection when direction is actually "None", as it will upset which texture will be grabbed

	if (newDirection == ActorDirection::None)
	{
		idleTickCount += GameEngine::GetDeltaTime();

		if (idleTickCount > 50)
		{
			// Stop walking
			SetState(ActorState::Idle);
		}
	}
	else
	{
		idleTickCount = 0;
	}



	switch(currentState)
	{
	case ActorState::Idle:
		attackingTickCount = 0;

		if (newDirection != ActorDirection::None)
		{
			// Start walking
			SetDirection(newDirection);
			SetState(ActorState::Walk);
		}

		break;

	case ActorState::Walk:
		attackingTickCount = 0;

		if (GetDirection() != newDirection && newDirection != ActorDirection::None)
		{
			// Change direction 
			SetDirection(newDirection);
		}

		break;

	case ActorState::Attack:
		idleTickCount = 0;
		attackingTickCount += GameEngine::GetDeltaTime();

		if (attackingTickCount >= 500.0)
		{
			// Stop attacking
			SetState(ActorState::Idle);
			attackingTickCount = 0;
		}

		break;
	}

	// UPDATE CAN HAPPEN SO QUICKLY THAT DELTAX/Y REMAINS 0 BETWEEN FRAMES
	// SO THE IDLE STATE WILL BE TRIGGERED
	screenX += deltaX;
	screenY += deltaY;

	deltaX = 0;
	deltaY = 0;
}



//
//
//
//if (newDirection == ActorDirection::None)
//{
//	idleTickCount += GameEngine::GetDeltaTime();
//
//	// Was no Delta movement registered between frames (FPS too high can be an issue)
//	if (GetState() != ActorState::Idle && idleTickCount > 0.5)
//	{
//		SetState(ActorState::Idle);
//		idleTickCount = 0.0f;
//	}
//}
//else if (GetDirection() != newDirection || GetState() != ActorState::Walk)
//{
//	if (GetState() != ActorState::Attack)
//	{
//		// Attack is not interruptable
//		SetState(ActorState::Walk);
//	}
//
//	SetDirection(newDirection);
//}
