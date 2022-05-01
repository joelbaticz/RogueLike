#pragma once

#include "Actor2d.h"

enum class NpcType
{
	BlackSmith = 0,
	Deckard = 1,
	Pepin = 2,
	Akara = 3,
	Other = 10
};

class Npc : public Actor2d
{
private:
	NpcType type;
	float deltaAmount = 0.075;
	float deltaX;
	float deltaY;

	void SetupAssets();
	void SetAnimationProperties();
public:
	Npc(int locationX, int locationY, NpcType type);
	~Npc();

	void SetState(ActorState state) override;
};
