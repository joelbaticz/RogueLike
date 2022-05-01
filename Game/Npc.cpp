#include "Npc.h"
#include "AssetManager.h"

Npc::Npc(int locationX, int locationY, NpcType type) : Actor2d(locationX, locationY)
{
	this->type = type;
	this->direction = (ActorDirection)0; // NPCs don't have separate anims for different directions
	SetupAssets();
}

Npc::~Npc() = default;

void Npc::SetupAssets()
{
	if (type == NpcType::BlackSmith)
	{
		TextureAtlas* taIdle = AssetManager::CreateTextureAtlas("Griswold-Idle.png");
		taIdle->SetHorizontalCount(16);
		taIdle->SetVerticalCount(1);

		SetTextureAtlas(ActorState::Idle, taIdle);
	}
	else if (type == NpcType::Deckard)
	{
		TextureAtlas* taIdle = AssetManager::CreateTextureAtlas("Deckard-Idle.png");
		taIdle->SetHorizontalCount(25);
		taIdle->SetVerticalCount(1);

		SetTextureAtlas(ActorState::Idle, taIdle);
	}
	else if (type == NpcType::Pepin)
	{
		TextureAtlas* taIdle = AssetManager::CreateTextureAtlas("Pepin-Idle.png");
		taIdle->SetHorizontalCount(20);
		taIdle->SetVerticalCount(1);

		SetTextureAtlas(ActorState::Idle, taIdle);
	}
	else if (type == NpcType::Akara)
	{
		TextureAtlas* taIdle = AssetManager::CreateTextureAtlas("Akara-Idle.png");
		taIdle->SetHorizontalCount(19);
		taIdle->SetVerticalCount(1);

		SetTextureAtlas(ActorState::Idle, taIdle);
	}
	else
	{
		throw new std::logic_error("Npc type not implemented");
	}
}

void Npc::SetState(ActorState state)
{
	Actor2d::SetState(state);

	SetAnimationProperties();
}

void Npc::SetAnimationProperties()
{
	if (type == NpcType::BlackSmith)
	{
		if (state == ActorState::Idle)
		{
			animationPlayer->SetMaxFrame(16);
			animationPlayer->SetAnimationLength(1.0f); // Anim length in secs
		}
	}
	if (type == NpcType::Deckard)
	{
		if (state == ActorState::Idle)
		{
			animationPlayer->SetMaxFrame(25);
			animationPlayer->SetAnimationLength(3.0f); // Anim length in secs
		}
	}
	if (type == NpcType::Pepin)
	{
		if (state == ActorState::Idle)
		{
			animationPlayer->SetMaxFrame(20);
			animationPlayer->SetAnimationLength(3.0f); // Anim length in secs
		}
	}
	if (type == NpcType::Akara)
	{
		if (state == ActorState::Idle)
		{
			animationPlayer->SetMaxFrame(19);
			animationPlayer->SetAnimationLength(3.0f); // Anim length in secs
		}
	}
}






