#include "RogueLike.h"
#include "AssetManager.h"
#include "Player.h"
#include "Npc.h"
#include "InfoPane.h"
#include "RendererFront.h"
#include "TileMapLoader.h"


RogueLike::RogueLike(): ControlNode("GameBase")
{
	levelInit = true;

	this->SetName("RogueLike");
	this->SetIsVisible(true);
	this->SetX(0);
	this->SetY(0);
	this->SetSize(new Size(RendererFront::GetWindowWidth(), RendererFront::GetWindowHeight()));
	//this->SetFillColor(AssetManager::CreateColor(255, 10, 20, 60));
	//this->SetStrokeColor(AssetManager::CreateColor(255, 10, 20, 60));

	EventManager::Subscribe(this); // To receive Update messages

	buttonMainMenu = new Button(this, "buttonMainMenu", "Main Menu", 10, 10, 80, 20);
	this->AddChild(buttonMainMenu);

	CreateLevel();
	CreatePlayers();
	CreateNPCs();

	levelInit = false;

	InfoPane* infoPane = new InfoPane();
	infoPane->SetLocation(5, RendererFront::GetWindowHeight() - infoPane->GetHeight() - 5);

	this->AddChild(infoPane);
}

RogueLike::~RogueLike() = default;

void RogueLike::SetMainMenu(MainMenu* mainMenu)
{
	this->mainMenu = mainMenu;
}

void RogueLike::CreateLevel()
{
	TileMap* newLevel = TileMapLoader::CreateNew();
	activeLevelIndex = AddLevel(newLevel);
}

int RogueLike::AddLevel(TileMap* newLevel)
{
	levels.insert(levels.end(), newLevel);
	int newLevelIndex = levels.size() - 1;

	return newLevelIndex;
}

void RogueLike::CreatePlayers()
{
	TileMap* currentMap = levels.at(activeLevelIndex);

	// Get Init values from Map
	int startTileX;
	int startTileY;

	currentMap->GetPlayerStartPosition(startTileX, startTileY);

	// Player1 - Mage
	player1 = new Player(startTileX, startTileY, PlayerType::Mage);
	player1->SetState(ActorState::Idle);
	player1->projectiles = &projectiles;
	player1->tileX = 7;
	player1->tileY = 7;

	// Add player to the Map
	currentMap->AddActor(player1);
}

void RogueLike::CreateNPCs()
{
	TileMap* currentMap = levels.at(activeLevelIndex);

	// Init values
	int npc1X = 470;
	int npc1Y = 50;

	int npc2X = 370;
	int npc2Y = 120;

	int npc3X = 370;
	int npc3Y = 250;

	int npc4X = 470;
	int npc4Y = 250;


	// BlackSmith
	npc1 = new Npc(npc1X, npc1Y, NpcType::BlackSmith);
	npc1->SetState(ActorState::Idle);
	npc1->tileX = 0;
	npc1->tileY = 0;

	// Deckard
	npc2 = new Npc(npc2X, npc2Y, NpcType::Deckard);
	npc2->SetState(ActorState::Idle);

	// Healer
	npc3 = new Npc(npc3X, npc3Y, NpcType::Pepin);
	npc3->SetState(ActorState::Idle);

	// Shack
	npc4 = new Npc(npc4X, npc4Y, NpcType::Akara);
	npc4->SetState(ActorState::Idle);

	currentMap->AddActor(npc1);
}

void RogueLike::Update()
{
	if (levelInit)
	{
		return;
	}

	player1->Update();

	//npc1->Update();
	//npc2->Update();
	//npc3->Update();
	//npc4->Update();

	if (projectiles.empty())
	{
		return;
	}

	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles[i]->Update();
	}		
}

void RogueLike::Draw(GraphicsContext* g)
{
	float elapsedTime = GameEngine::GetDeltaTime();
	TileMap* currentMap = levels[activeLevelIndex];

	g->BeginDraw();

	int screenWidthHalf = RendererFront::GetWindowWidth() / 2;
	int screenHeightHalf = RendererFront::GetWindowHeight() / 2;

	currentMap->SetCenter(screenWidthHalf, screenHeightHalf);
	currentMap->ScreenDraw();

	if (!projectiles.empty())
	{
		for (int i = 0; i < projectiles.size(); i++)
		{
			projectiles[i]->ScreenDrawAnimation(elapsedTime);
		}
	}

	// Draw "cursor"
	//player1->screenX = mouseX;
	//player1->screenY = mouseY;
	//player1->ScreenDrawAnimation(elapsedTime);

	g->EndDraw();
}

void RogueLike::ProcessMessage(Message* msg)
{
	if (msg->type == MSG_KEYDOWN)
	{
		// Handle Player 1 controls
		//int player1Actions = (int)PlayerAction::None;

		if (msg->sdlEvent->key.keysym.sym == SDLK_UP)
		{
			player1->HandleInput(PlayerInput::MoveUp);
			//player1Actions = player1Actions | (int)PlayerAction::MoveUp;
		}
		if (msg->sdlEvent->key.keysym.sym == SDLK_DOWN)
		{
			player1->HandleInput(PlayerInput::MoveDown);
			//player1Actions = player1Actions | (int)PlayerAction::MoveDown;
		}
		if (msg->sdlEvent->key.keysym.sym == SDLK_LEFT)
		{
			player1->HandleInput(PlayerInput::MoveLeft);
			//player1Actions = player1Actions | (int)PlayerAction::MoveLeft;
		}
		if (msg->sdlEvent->key.keysym.sym == SDLK_RIGHT)
		{
			player1->HandleInput(PlayerInput::MoveRight);
			//player1Actions = player1Actions | (int)PlayerAction::MoveRight;
		}
		if (msg->sdlEvent->key.keysym.sym == SDLK_INSERT)
		{
			player1->HandleInput(PlayerInput::Attack1);
		}

		//player1->HandleAction((PlayerAction)player1Actions);		

		// Handle Player 2 controls

		if (msg->sdlEvent->key.keysym.sym == SDLK_w)
		{
			player2->HandleInput(PlayerInput::MoveUp);
		}
		if (msg->sdlEvent->key.keysym.sym == SDLK_s)
		{
			player2->HandleInput(PlayerInput::MoveDown);
		}
		if (msg->sdlEvent->key.keysym.sym == SDLK_a)
		{
			player2->HandleInput(PlayerInput::MoveLeft);
		}
		if (msg->sdlEvent->key.keysym.sym == SDLK_d)
		{
			player2->HandleInput(PlayerInput::MoveRight);
		}
		if (msg->sdlEvent->key.keysym.sym == SDLK_1)
		{
			player2->HandleInput(PlayerInput::Attack1);
		}
	}

	// Handle other (game wide keystrokes)
	if (msg->type == MSG_KEYUP)
	{
		// New Level
		if (msg->sdlEvent->key.keysym.sym == SDLK_n)
		{
			TileMap* newLevel = TileMapLoader::CreateNew();
			activeLevelIndex = AddLevel(newLevel);
		}
	}

	if (msg->type == MSG_BUTTON_CLICKED)
	{
		if (msg->sender == buttonMainMenu)
		{
			((CanvasNode*)this->mainMenu)->SetIsVisible(true);
			((CanvasNode*)this->mainMenu)->BringToFront();
			this->SetIsVisible(false);
		}
	}
}

void RogueLike::OnMouseMove(Message* msg)
{
	TileMap* currentMap = levels.at(activeLevelIndex);

	mouseX = msg->sdlEvent->motion.x;
	mouseY = msg->sdlEvent->motion.y;

	currentMap->SetMousePosition(mouseX, mouseY);

	player1->MoveToSelectedTile();
}

void RogueLike::OnMouseClick(Message* msg)
{
	if (msg->sdlEvent->button.button == SDL_BUTTON_LEFT)
	{
		player1->MoveToSelectedTile();
	}
	else if (msg->sdlEvent->button.button == SDL_BUTTON_RIGHT)
	{
		player1->HandleInput(PlayerInput::AttackTile);
	}

}

