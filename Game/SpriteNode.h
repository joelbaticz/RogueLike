#pragma once

#include "CanvasNode.h"
#include "Color.h"
#include "Texture.h"
#include "TextureAtlas.h"

class SpriteNode : public CanvasNode
{
private:

protected:
	TextureAtlas*			textureAtlas;
	int						textureIndex;
public:
	SpriteNode();
	~SpriteNode();

	TextureAtlas* GetTextureAtlas();
	void SetTextureAtlas(TextureAtlas* value);
	int GetTextureIndex();
	void SetTextureIndex(int textureIndex);

	void Draw(GraphicsContext* g) override;
};