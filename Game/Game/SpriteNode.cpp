#include "SpriteNode.h"
#include "RenderingEngine.h"
#include "AssetManager.h"

SpriteNode::SpriteNode()
{
	SetName("SpriteNode");
	textureAtlas = nullptr;
	textureIndex = 0;

	this->ResetGraphicsContext();
	this->GetGraphics()->SetFillColor(AssetManager::CreateColor(255, 80, 80, 80));
	this->GetGraphics()->SetPenColor(AssetManager::CreateColor(255, 192, 192, 128));
}

SpriteNode::~SpriteNode()
{
	//AssetManager::UnsubscribeFromTexture...
}

TextureAtlas* SpriteNode::GetTextureAtlas()
{
	return textureAtlas;
}

void SpriteNode::SetTextureAtlas(TextureAtlas* value)
{
	textureAtlas = value;
}

int SpriteNode::GetTextureIndex()
{
	return textureIndex;
}

void SpriteNode::SetTextureIndex(int value)
{
	textureIndex = value;
}

void SpriteNode::Draw(GraphicsContext* g)
{

	LogEngine::Log(LOG_DEBUG, "SpriteNode", "Draw() called on " + this->GetName());

	if (GetIsVisible())
	{
		//TEST
		//g->BeginDraw();

		//g->DrawFilledRectangle(0, 0, this->GetSize()->GetWidth(), this->GetSize()->GetHeight());
		//g->DrawRectangle(0, 0, this->GetSize()->GetWidth() - 1, this->GetSize()->GetHeight() - 1);

		//g->EndDraw();

		//return;

		Rectangle rectSource = Rectangle();
		Rectangle rectTarget = Rectangle();
		
		Rectangle* pRectSource = &rectSource;
		Rectangle* pRectTarget = &rectTarget;
	
		this->textureAtlas->GetTextureRectangle(textureIndex, pRectSource);

		pRectTarget->SetX(0);
		pRectTarget->SetY(0);
		pRectTarget->SetWidth(this->GetSize()->GetWidth());
		pRectTarget->SetHeight(this->GetSize()->GetHeight());

		g->BeginDraw();

		g->DrawTexture(textureAtlas, pRectSource, pRectTarget);
		
		g->EndDraw();

		return;

	}

	//Don't bubble upwards
	//super::Draw();
}

