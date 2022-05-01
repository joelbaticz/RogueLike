#include "SpriteNinePatch.h"
#include "AssetManager.h"

SpriteNinePatch::SpriteNinePatch()
{
	SetName("SpriteNinePatch");
	textureAtlas = nullptr;
	cornerSize = 0;
	textureIndex = 0;
	//layout = LayoutTile;
	//align = AlignLeft

	this->ResetGraphicsContext();
	this->GetGraphics()->SetFillColor(AssetManager::CreateColor(255, 80, 80, 80));
	this->GetGraphics()->SetPenColor(AssetManager::CreateColor(255, 192, 192, 128));
}

SpriteNinePatch::~SpriteNinePatch()
{
}

int SpriteNinePatch::GetCornerSize()
{
	return cornerSize;
}

void SpriteNinePatch::SetCornerSize(int value)
{
	cornerSize = value;
}


void SpriteNinePatch::Draw(GraphicsContext* g)
{
	if (GetIsVisible())
	{
		int cs = cornerSize;

		Rectangle rectSource = Rectangle();
		Rectangle rectTarget = Rectangle();
		Rectangle rectSprite = Rectangle();
		Rectangle rectTexture = Rectangle();

		Rectangle* pRectSource = &rectSource;
		Rectangle* pRectTarget = &rectTarget;
		Rectangle* pRectSprite = &rectSprite;
		Rectangle* pRectTexture = &rectTexture;

		this->textureAtlas->GetTextureRectangle(textureIndex, pRectTexture);

		pRectSprite->SetX(0);
		pRectSprite->SetY(0);
		pRectSprite->SetWidth(this->GetWidth());
		pRectSprite->SetHeight(this->GetHeight());

		g->BeginDraw();

		//TOP LEFT
		pRectSource->SetX(pRectTexture->GetX());
		pRectSource->SetY(pRectTexture->GetY());
		pRectSource->SetWidth(cs);
		pRectSource->SetHeight(cs);
		pRectTarget->SetX(pRectSprite->GetX());
		pRectTarget->SetY(pRectSprite->GetY());
		pRectTarget->SetWidth(cs);
		pRectTarget->SetHeight(cs);
		g->DrawTexture(textureAtlas, pRectSource, pRectTarget);

		//TOP MIDDLE
		pRectSource->SetX(pRectTexture->GetX() + cs);
		pRectSource->SetY(pRectTexture->GetY());
		pRectSource->SetWidth(pRectTexture->GetWidth() - cs * 2);
		pRectSource->SetHeight(cs);
		pRectTarget->SetX(pRectSprite->GetX() + cs);
		pRectTarget->SetY(pRectSprite->GetY());
		pRectTarget->SetWidth(pRectSprite->GetWidth() - cs * 2);
		pRectTarget->SetHeight(cs);
		g->DrawTexture(textureAtlas, pRectSource, pRectTarget);

		//TOP RIGHT
		pRectSource->SetX(pRectTexture->GetX() + pRectTexture->GetWidth() - cs);
		pRectSource->SetY(pRectTexture->GetY());
		pRectSource->SetWidth(cs);
		pRectSource->SetHeight(cs);
		pRectTarget->SetX(pRectSprite->GetX() + pRectSprite->GetWidth() - cs);
		pRectTarget->SetY(pRectSprite->GetY());
		pRectTarget->SetWidth(cs);
		pRectTarget->SetHeight(cs);
		g->DrawTexture(textureAtlas, pRectSource, pRectTarget);

		//MIDDLE LEFT
		pRectSource->SetX(pRectTexture->GetX());
		pRectSource->SetY(pRectTexture->GetY() + cs);
		pRectSource->SetWidth(cs);
		pRectSource->SetHeight(pRectTexture->GetHeight() - cs * 2);
		pRectTarget->SetX(pRectSprite->GetX());
		pRectTarget->SetY(pRectSprite->GetY() + cs);
		pRectTarget->SetWidth(cs);
		pRectTarget->SetHeight(pRectSprite->GetHeight() - cs * 2);
		g->DrawTexture(textureAtlas, pRectSource, pRectTarget);

		//MIDDLE MIDDLE
		pRectSource->SetX(pRectTexture->GetX() + cs);
		pRectSource->SetY(pRectTexture->GetY() + cs);
		pRectSource->SetWidth(pRectTexture->GetWidth() - cs * 2);
		pRectSource->SetHeight(pRectTexture->GetHeight() - cs * 2);
		pRectTarget->SetX(pRectSprite->GetX() + cs);
		pRectTarget->SetY(pRectSprite->GetY() + cs);
		pRectTarget->SetWidth(pRectSprite->GetWidth() - cs * 2);
		pRectTarget->SetHeight(pRectSprite->GetHeight() - cs * 2);
		g->DrawTexture(textureAtlas, pRectSource, pRectTarget);

		//MIDDLE RIGHT
		pRectSource->SetX(pRectTexture->GetX() + pRectTexture->GetWidth() - cs);
		pRectSource->SetY(pRectTexture->GetY() + cs);
		pRectSource->SetWidth(cs);
		pRectSource->SetHeight(pRectTexture->GetHeight() - cs * 2);
		pRectTarget->SetX(pRectSprite->GetX() + pRectSprite->GetWidth() - cs);
		pRectTarget->SetY(pRectSprite->GetY() + cs);
		pRectTarget->SetWidth(cs);
		pRectTarget->SetHeight(pRectSprite->GetHeight() - cs * 2);
		g->DrawTexture(textureAtlas, pRectSource, pRectTarget);

		//BOTTOM LEFT
		pRectSource->SetX(pRectTexture->GetX());
		pRectSource->SetY(pRectTexture->GetY() + pRectTexture->GetHeight() - cs);
		pRectSource->SetWidth(cs);
		pRectSource->SetHeight(cs);
		pRectTarget->SetX(pRectSprite->GetX());
		pRectTarget->SetY(pRectSprite->GetY() + pRectSprite->GetHeight() - cs);
		pRectTarget->SetWidth(cs);
		pRectTarget->SetHeight(cs);
		g->DrawTexture(textureAtlas, pRectSource, pRectTarget);

		//BOTTOM MIDDLE
		pRectSource->SetX(pRectTexture->GetX() + cs);
		pRectSource->SetY(pRectTexture->GetY() + pRectTexture->GetHeight() - cs);
		pRectSource->SetWidth(pRectTexture->GetWidth() - cs * 2);
		pRectSource->SetHeight(cs);
		pRectTarget->SetX(pRectSprite->GetX() + cs);
		pRectTarget->SetY(pRectSprite->GetY() + pRectSprite->GetHeight() - cs);
		pRectTarget->SetWidth(pRectSprite->GetWidth() - cs * 2);
		pRectTarget->SetHeight(cs);
		g->DrawTexture(textureAtlas, pRectSource, pRectTarget);

		//BOTTOM RIGHT
		pRectSource->SetX(pRectTexture->GetX() + pRectTexture->GetWidth() - cs);
		pRectSource->SetY(pRectTexture->GetY() + pRectTexture->GetHeight() - cs);
		pRectSource->SetWidth(cs);
		pRectSource->SetHeight(cs);
		pRectTarget->SetX(pRectSprite->GetX() + pRectSprite->GetWidth() - cs);
		pRectTarget->SetY(pRectSprite->GetY() + pRectSprite->GetHeight() - cs);
		pRectTarget->SetWidth(cs);
		pRectTarget->SetHeight(cs);
		g->DrawTexture(textureAtlas, pRectSource, pRectTarget);

		g->EndDraw();
	}
}

