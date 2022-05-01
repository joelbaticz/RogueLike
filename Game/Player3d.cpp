#include "Player3d.h"
#include "EventManager.h"
#include "Level.h"

Player3d::Player3d(Math::Vec4 pos)
{
	this->playerPos = Math::Vec4(pos);
	this->health = 100;
}

Player3d::~Player3d()
{

}

void Player3d::UpdateState(void* level)
{
	// Act on gravity
	Level* levelX = (Level*)level;

	if (!levelX->IsFloorReached(this->playerPos))
	{
		playerPos.y -= 1.0f;
	}

	if (health > 0.0f)
	{
		this->health -= 0.01f;
	}	
}

int Player3d::GetHealth()
{
	return (int)health;
}



bool Player3d::IsAlive()
{
	if (health > 0.0f)
	{
		return true;
	}

	return false;
}

Math::Vec4& Player3d::GetPosition()
{
	return playerPos;
}