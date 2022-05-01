#include "SpriteNinePatch.h"
#include "RenderingEngine.h"
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
	//return;

	//No call to parent is needed

	LogEngine::Log(LOG_DEBUG, "SpriteNinePatch", "Draw() called on " + this->GetName());

	if (GetIsVisible())
	{

		//canvasNode->GetRectangle(); "Get's the control's rectangular area in client coordinates. It means X, Y values are 0."
		//canvasNode->GetClientRect(); "Get's the control's rectangular client area (without frames, scrollbars and whatnot) in client coordinates."
		//canvasNode=>RectToScreen(); "Projects a rectangular client area to screen coordinates. Only masses with X and Y coordinates."
		//canvasNode->RectToClient(); "Projects a rectangular screen area to client coordinates."
		//renderer->GetCurrentClippingRect();
		//renderer->SetClippingRect(); "Sets a clipping rectangle. Screen or client coordinates?"

		//In windows you need to acquire a Graphics context and you call DrawLine, DrawRectangle with it.
		//It means you can draw knowing only the client relative coordinates. I guess it gets the Device Context for you. ClientDC or DC depends on
		//the control itself.
		//I guess the renderer should do graphics in screen coordinates and the "graphics context" should translate for you.
		//CreateGraphics could be a method in the canvas which you need to acquire at the Draw call and dispose of it every frame.
		//In Java this Graphics thin is passed on to the draw method as a parameter that you can use already preset for you.
		//And it lives inside the Control.

		//We can do that the Renderer will only have ScreenDrawLine, ScreenDrawRectangle and the rest. It would use the currently set pencolor,
		//fillcolor and clipping area. Obviously it would use screen coordinates.

		//The Graphics Context on the other hand would work take in client coordinates and translate them to screen coordinates.
		//This added complexity would not be present when we are directly drawing to the screen.
		//The Graphics Context would only be used to draw the UI elements. The game itself would only use the screen or only would draw into a texture
		//anyways. Not sure about the client to screen translation penalties, but clipping is needed even when we are drawing to an image/texture.


		//ClipToParentRectangle inkabb a CanvasNode resze kene legyen, semmint a RenderingEngine-e
		//Ahhoz, hogy ne minden frame-en szamoljuk ki a ClippingWindow-t ahhoz azt le kellene tarolni es csak a SetSize, SetLocation-nel ujra kiszamolni
		//Valamint jo lenne ha a drawing client coordinatakban tortenne amit egy object (vagy a CanvasNode maga) transzlalna screen coordokba.
		//Viszont ez az egesz ClipToParent csak a UI-hoz kell igazibol!
		//Az actual game logic-hoz Sprite/Tile drawing es 3D-s cuccok azokhoz nem kell.
		//Tehat a Sprite/SpriteNinePatch nem kene, hogy CancasNode legyen es ezek csak screencoord-ban szamolnak?
		//A Scene hasznalhat Sprite-okat es Canvas item-eket.

		//---2019-12-24
		//Rectangle rectScreen = Rectangle(this->GetLocation()->GetX(), this->GetLocation()->GetY(), this->GetSize()->GetWidth(), this->GetSize()->GetHeight());
		//Rectangle* pRectScreen = &rectScreen;
		//pRectScreen = RenderingEngine::ClipToParentRectangle(this->GetParent(), pRectScreen);
		//RenderingEngine::SetClippingRectangle(pRectScreen);
		//---

		//---2020-01-02

		//TEST
		//g->BeginDraw();
	
		//g->DrawFilledRectangle(0, 0, this->GetSize()->GetWidth(), this->GetSize()->GetHeight());
		//g->DrawRectangle(0, 0, this->GetSize()->GetWidth() - 1, this->GetSize()->GetHeight() - 1);

		//g->EndDraw();

		//return;


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
		pRectSprite->SetWidth(this->GetSize()->GetWidth());
		pRectSprite->SetHeight(this->GetSize()->GetHeight());

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

		return;

		//---




		//RenderingEngine::SetClippingRectangle(g->GetClippingRectangle());

		//Rectangle rectangleTexture = Rectangle();
		//Rectangle* pRectangleTexture = &rectangleTexture;
		//this->textureAtlas->GetTextureRectangle(textureIndex, pRectangleTexture);

		//SDL_Rect rectTexture = SDL_Rect();
		//SDL_Rect* pRectTexture = &rectTexture;
		//pRectTexture->x = pRectangleTexture->GetX();
		//pRectTexture->y = pRectangleTexture->GetY();
		//pRectTexture->w = pRectangleTexture->GetWidth();
		//pRectTexture->h = pRectangleTexture->GetHeight();

		//SDL_Rect rectSprite = SDL_Rect();
		//SDL_Rect* pRectSprite = &rectSprite;
		//pRectSprite->x = this->GetLocation()->GetX();
		//pRectSprite->y = this->GetLocation()->GetY();
		//pRectSprite->w = this->GetSize()->GetWidth();
		//pRectSprite->h = this->GetSize()->GetHeight();

		////Do 9TilePath thingy with using TextureIndex

		//SDL_Rect rectSource = SDL_Rect();
		//SDL_Rect* pRectSource = &rectSource;
		//SDL_Rect rectTarget = SDL_Rect();
		//SDL_Rect* pRectTarget = &rectTarget;
		//int cs = cornerSize;

		////Top Left
		//pRectSource->x = pRectTexture->x;
		//pRectSource->y = pRectTexture->y;
		//pRectSource->w = cs;
		//pRectSource->h = cs;
		//pRectTarget->x = pRectSprite->x;
		//pRectTarget->y = pRectSprite->y;
		//pRectTarget->w = cs;
		//pRectTarget->h = cs;
		//RenderingEngine::DrawTexture(this, textureAtlas, pRectSource, pRectTarget);
		////RenderingEngine::ScreenDrawTexture(textureAtlas, )

		////Top Middle
		//pRectSource->x = pRectTexture->x + cs;
		//pRectSource->y = pRectTexture->y;
		//pRectSource->w = pRectTexture->w - cs * 2;
		//pRectSource->h = cs;
		//pRectTarget->x = pRectSprite->x + cs;
		//pRectTarget->y = pRectSprite->y;
		//pRectTarget->w = pRectSprite->w - cs * 2;
		//pRectTarget->h = cs;
		//RenderingEngine::DrawTexture(this, textureAtlas, pRectSource, pRectTarget);

		////Top Right
		//pRectSource->x = pRectTexture->x + pRectTexture->w - cs;
		//pRectSource->y = pRectTexture->y;
		//pRectSource->w = cs;
		//pRectSource->h = cs;
		//pRectTarget->x = pRectSprite->x + pRectSprite->w - cs;
		//pRectTarget->y = pRectSprite->y;
		//pRectTarget->w = cs;
		//pRectTarget->h = cs;
		//RenderingEngine::DrawTexture(this, textureAtlas, pRectSource, pRectTarget);



		////Middle Left
		//pRectSource->x = pRectTexture->x;
		//pRectSource->y = pRectTexture->y + cs;
		//pRectSource->w = cs;
		//pRectSource->h = pRectTexture->h - cs * 2;
		//pRectTarget->x = pRectSprite->x;
		//pRectTarget->y = pRectSprite->y + cs;
		//pRectTarget->w = cs;
		//pRectTarget->h = pRectSprite->h - cs * 2;
		//RenderingEngine::DrawTexture(this, textureAtlas, pRectSource, pRectTarget);


		////Middle Middle
		//pRectSource->x = pRectTexture->x + cs;
		//pRectSource->y = pRectTexture->y + cs;
		//pRectSource->w = pRectTexture->w - cs * 2;
		//pRectSource->h = pRectTexture->h - cs * 2;
		//pRectTarget->x = pRectSprite->x + cs;
		//pRectTarget->y = pRectSprite->y + cs;
		//pRectTarget->w = pRectSprite->w - cs * 2;
		//pRectTarget->h = pRectSprite->h - cs * 2;
		//RenderingEngine::DrawTexture(this, textureAtlas, pRectSource, pRectTarget);


		////Middle Right
		//pRectSource->x = pRectTexture->x + pRectTexture->w - cs;
		//pRectSource->y = pRectTexture->y + cs;
		//pRectSource->w = cs;
		//pRectSource->h = pRectTexture->h - cs * 2;
		//pRectTarget->x = pRectSprite->x + pRectSprite->w - cs;
		//pRectTarget->y = pRectSprite->y + cs;
		//pRectTarget->w = cs;
		//pRectTarget->h = pRectSprite->h - cs * 2;
		//RenderingEngine::DrawTexture(this, textureAtlas, pRectSource, pRectTarget);


		////Bottom Left
		//pRectSource->x = pRectTexture->x;
		//pRectSource->y = pRectTexture->y + pRectTexture->h - cs;
		//pRectSource->w = cs;
		//pRectSource->h = cs;
		//pRectTarget->x = pRectSprite->x;
		//pRectTarget->y = pRectSprite->y + pRectSprite->h - cs;
		//pRectTarget->w = cs;
		//pRectTarget->h = cs;
		//RenderingEngine::DrawTexture(this, textureAtlas, pRectSource, pRectTarget);


		////Bottom Middle
		//pRectSource->x = pRectTexture->x + cs;
		//pRectSource->y = pRectTexture->y + pRectTexture->h - cs;
		//pRectSource->w = pRectTexture->w - cs * 2;
		//pRectSource->h = cs;
		//pRectTarget->x = pRectSprite->x + cs;
		//pRectTarget->y = pRectSprite->y + pRectSprite->h - cs;
		//pRectTarget->w = pRectSprite->w - cs * 2;
		//pRectTarget->h = cs;
		//RenderingEngine::DrawTexture(this, textureAtlas, pRectSource, pRectTarget);


		////Bottom Right
		//pRectSource->x = pRectTexture->x + pRectTexture->w - cs;
		//pRectSource->y = pRectTexture->y + pRectTexture->h - cs;
		//pRectSource->w = cs;
		//pRectSource->h = cs;
		//pRectTarget->x = pRectSprite->x + pRectSprite->w - cs;
		//pRectTarget->y = pRectSprite->y + pRectSprite->h - cs;
		//pRectTarget->w = cs;
		//pRectTarget->h = cs;
		//RenderingEngine::DrawTexture(this, textureAtlas, pRectSource, pRectTarget);



		//TEST

		//return;

		//int width = g->GetBounds()->GetWidth();
		//int height = g->GetBounds()->GetHeight();

		//g->BeginDraw();
		//g->SetPenColor(AssetManager::CreateColor(255, 255, 0, 0));
		//g->SetFillColor(AssetManager::CreateColor(255, 0, 255, 0));

		//g->DrawFilledRectangle(0, 0, width, height);
		//g->DrawLine(0, 0, width, height);
		//g->DrawLine(0, height, width, 0);

		//g->EndDraw();

		//int x = g->GetBounds()->GetX();
		//int y = g->GetBounds()->GetY();
		//int width = g->GetBounds()->GetWidth();
		//int height = g->GetBounds()->GetHeight();

		//Rectangle rectThis = Rectangle(this->GetLocation()->GetX(), this->GetLocation()->GetY(), this->GetSize()->GetWidth(), this->GetSize()->GetHeight());
		//Rectangle* pRectThis = &rectThis;
		//pRectThis = RenderingEngine::ClipToParentRectangle(this->GetParent(), pRectThis);

		//RenderingEngine::SetClippingRectangle(g->GetClippingRectangle());
		//RenderingEngine::ScreenDrawFilledRectangle(x, y, x + width, y + height);

		//Rectangle screen = Rectangle(0, 0, 800, 600);
		//Rectangle* pScreen = &screen;
		//RenderingEngine::SetClippingRectangle(pScreen);

		//RenderingEngine::ScreenDrawLine(x, y, x + width, y + height);
		//RenderingEngine::ScreenDrawLine(x, y + height, x + width, y);
	}

	//Don't bubble upwards
	//super::Draw();
}

