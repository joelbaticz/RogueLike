#pragma once
#include "Actor2d.h"


class Projectile : public Actor2d
{
	int type;
public:
	float deltaX;
	float deltaY;

	Projectile(float originX, float originY, float deltaX, float deltaY, int type);
	~Projectile();

	ActorDirection HandleDirection(float deltaX, float deltaY);

	void Update() override;
	void ScreenDrawAnimation(float elapsedTime) override;
};
