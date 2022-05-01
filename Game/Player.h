#pragma once

#include "Actor2d.h"
#include "Projectile.h"

enum class PlayerType
{
	Mage = 0,
	Archer = 1,
	Warrior = 2
};

enum class PlayerInput
{
	None = 0,
	MoveUp = 1,
	MoveDown = 2,
	MoveLeft = 3,
	MoveRight = 4,
	Attack1 = 5,
	Attack2 = 6,
	MoveToTile = 7,
	AttackTile = 8
};

class Player : public Actor2d
{
private:
	PlayerType type;
	float deltaAmount = 0.075;

	float idleTickCount;
	float attackingTickCount;

	void SetupAssets();
	void SetAnimationProperties();
public:
	Player(int locationX, int locationY, PlayerType type);
	~Player();

	std::vector<Projectile*>* projectiles;

	void MoveToSelectedTile();

	void SetState(ActorState state) override;
	void HandleInput(PlayerInput action) override;
	void Update() override;
};