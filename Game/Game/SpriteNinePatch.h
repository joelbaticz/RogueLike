#pragma once

#include "SpriteNode.h"
#include "Color.h"
#include "Texture.h"
#include "TextureAtlas.h"

class SpriteNinePatch : public SpriteNode
{
private:

protected:
	int						cornerSize;
public:
	SpriteNinePatch();
	~SpriteNinePatch();

	int GetCornerSize();
	void SetCornerSize(int value);

	void Draw(GraphicsContext* g) override;
};