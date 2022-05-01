#include "LoadingBar.h"

#include "AssetManager.h"

LoadingBar::LoadingBar()
{
	loadingBarTextureAtlas = AssetManager::CreateTextureAtlas("loadingbar.png");
	loadingBarTextureAtlas->SetHorizontalCount(1);
	loadingBarTextureAtlas->SetVerticalCount(1);

	SetTextureAtlas(loadingBarTextureAtlas);
}

LoadingBar::~LoadingBar()
{
}

void LoadingBar::Draw(GraphicsContext* g)
{
	barX += 5;
	if (barX > 640) barX = 0;

	g->BeginDraw();

	g->DrawTexture(loadingBarTextureAtlas, barX - 640, 0);
	g->DrawTexture(loadingBarTextureAtlas, barX, 0);
	g->DrawTexture(loadingBarTextureAtlas, barX + 640, 0);

	g->EndDraw();
}