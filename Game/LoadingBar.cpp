#include "LoadingBar.h"

#include "AssetManager.h"

LoadingBar::LoadingBar()
{
	loadingBarTextureAtlas = AssetManager::CreateTextureAtlas(Configuration::UIPath + "LoadingBar.png");
	loadingBarTextureAtlas->SetHorizontalCount(1);
	loadingBarTextureAtlas->SetVerticalCount(1);

	SetTextureAtlas(loadingBarTextureAtlas);
}

LoadingBar::~LoadingBar()
{
}

void LoadingBar::Draw(GraphicsContext* g)
{
	float fElapsedTime = GameEngine::GetDeltaTime();

	barX += fElapsedTime / 10;
	if (barX > 640) barX = 0;

	g->BeginDraw();

	g->DrawTexture(loadingBarTextureAtlas, barX - 640, 0);
	g->DrawTexture(loadingBarTextureAtlas, barX, 0);
	g->DrawTexture(loadingBarTextureAtlas, barX + 640, 0);

	g->EndDraw();
}