#pragma once

#include "SpriteNode.h"
#include "AnimationPlayer.h"
#include <vector>
#include <map>

enum class PlayerInput;

enum class ActorDirection
{
	S = 0,
	SW = 1,
	W = 2,
	NW = 3,
	N = 4,
	NE = 5,
	E = 6,
	SE = 7,
	None = 255
};

enum class ActorState
{
	Idle = 1,
	Walk = 2,
	Attack = 3,
	Dodge = 4,
	Cast = 5
};

class Actor2d
{
protected:
	int life;
	int spriteWidth;
	int spriteHeight;
	int spriteOffsetX;
	int spriteOffsetY;
	ActorDirection direction;
	ActorState state;

	TextureAtlas* textureAtlasIdle;
	TextureAtlas* textureAtlasWalk;

	std::map<ActorState, TextureAtlas*> textureByState = std::map<ActorState, TextureAtlas*>();

	float screenX;
	float screenY;
	float deltaX;
	float deltaY;

	float accTime;

	ActorDirection HandleDirection();
	void HandleWalkState();
public:
	AnimationPlayer* animationPlayer;

	float tileX;
	float tileY;
	float targetTileX;
	float targetTileY;

	void* tileMap;

	Actor2d(int tileX, int tileY);
	~Actor2d();

	bool IsAlive();
	ActorDirection GetDirection();
	ActorState GetState();
	void MoveToTile(int tileX, int tileY);

	void SetDirection(ActorDirection direction);
	void SetTextureAtlas(ActorState state, TextureAtlas* textureAtlas);
	
	// Overridable members
	virtual void SetState(ActorState state);
	virtual void HandleInput(PlayerInput input);
	virtual void Update();

	void ScreenDraw(); // Uses the graphics context of the caller (ClippingRect and BoundingRect comes from the caller) - Actor2d haven't been added to the parent node
	virtual void ScreenDrawAnimation(float elapsedTime); // Uses the graphics context of the caller (ClippingRect and BoundingRect comes from the caller) - Actor2d haven't been added to the parent node
};
