#pragma once

#include "Math.h"

class Player3d // ::public Actor
{
private:
	Math::Vec4 playerPos;
	float lookAngleX;
	float lookAngleY;
	float lookangleZ;
	
	float health;

public:
	Player3d(Math::Vec4 pos);
	~Player3d();

	void UpdateState(void* level);

	int GetHealth();
	bool IsAlive();

	Math::Vec4& GetPosition();
};
