#pragma once

#include "SpriteNode.h"

class LoadingBar : public SpriteNode
{
private:
	int barX;
	TextureAtlas* loadingBarTextureAtlas;

public:
	LoadingBar();
	~LoadingBar();

	//void Update() override;
	void Draw(GraphicsContext* g) override;
};