#include "Projectile.h"
#include "AssetManager.h"
#include "RendererFront.h"

Projectile::Projectile(float originX, float originY, float deltaX, float deltaY, int type) : Actor2d(originX, originY)
{
	TextureAtlas* taFireball = AssetManager::CreateTextureAtlas("Mage-FireBall.png");
	taFireball->SetHorizontalCount(14);
	taFireball->SetVerticalCount(16);

	SetTextureAtlas(ActorState::Idle, taFireball);

	this->deltaX = deltaX * 0.75;
	this->deltaY = deltaY * 0.75;
	this->type = type;
	SetDirection(HandleDirection(deltaX, deltaY));
	animationPlayer->SetAnimationLength(0.1);
	animationPlayer->SetMaxFrame(14);
}

Projectile::~Projectile() = default;

ActorDirection Projectile::HandleDirection(float deltaX, float deltaY)
{
	ActorDirection newDirection = ActorDirection::None;

	// Player control
	if (deltaY < 0 && deltaX == 0)
	{
		// North
		newDirection = ActorDirection::N;
	}
	else if (deltaY < 0 && deltaX > 0)
	{
		// North East
		newDirection = ActorDirection::NE;
	}
	else if (deltaY == 0 && deltaX > 0)
	{
		// East
		newDirection = ActorDirection::E;
	}
	else if (deltaY > 0 && deltaX > 0)
	{
		// South East
		newDirection = ActorDirection::SE;
	}
	else if (deltaY > 0 && deltaX == 0)
	{
		// South
		newDirection = ActorDirection::S;
	}
	else if (deltaY > 0 && deltaX < 0)
	{
		// South West
		newDirection = ActorDirection::SW;
	}
	else if (deltaY == 0 && deltaX < 0)
	{
		// West
		newDirection = ActorDirection::W;
	}
	else if (deltaY < 0 && deltaX < 0)
	{
		// North West
		newDirection = ActorDirection::NW;
	}

	return newDirection;
}

void Projectile::Update()
{
 	screenX += deltaX;
	screenY += deltaY;
	//SetDirection(HandleDirection(deltaX, deltaY));
}

void Projectile::ScreenDrawAnimation(float elapsedTime)
{
	int maxFrame = animationPlayer->GetMaxFrame();
	int currentFrame = animationPlayer->GetCurrentFrame(elapsedTime);

	Rectangle sourceRect = Rectangle(0, 0, 0, 0);
	Rectangle targetRect = Rectangle((int)screenX - spriteWidth / 2 + spriteOffsetX, (int)screenY - spriteHeight / 2 + spriteOffsetY, spriteWidth, spriteHeight);

	TextureAtlas* currentTextureAtlas = textureByState[state];

	if (currentTextureAtlas == NULL)
	{
		return;
	}

	currentTextureAtlas->GetTextureRectangle((int)direction * 2 * maxFrame + currentFrame, &sourceRect);

	RendererFront::ScreenDrawTexture(currentTextureAtlas, &sourceRect, &targetRect);
}

