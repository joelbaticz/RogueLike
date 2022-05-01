#pragma once
#include <string>
#include <SDL.h>
#include "Node.h"
#include "Math.h"
#include "Rectangle.h"
#include "Font.h"
#include "Texture.h"
#include "DrawMode.h"
#include "Color.h"
#include "Renderer.h"
#include "RendererFactory.h"

class RendererFront
{
private:
	static RendererOptions* rendererOptions;
	static RendererFactory* rendererFactory;
	static Renderer*		renderer;
public:
	static int Init(int windowX, int windowY, int windowWidth, int windowHeigh, bool isFullScreen, std::string windowTitle);
	static void UnInit();

	static void ShowWindow(bool isShow);
	static void SetWindowFullScreen();
	static void SetWindowMinimize();

	static void BeginFrame();
	static void PresentFrame();

	static SDL_Renderer* GetRenderer();
	static int GetWindowWidth();
	static int GetWindowHeight();
	static void SetPenColor(Color* color);
	static void SetFillColor(Color* color);
	static void SetDrawMode(DrawMode drawMode);
	static void SetTexture(Texture* texture);

	static Rectangle* ClipToParentRectangle(Node* node, Rectangle* rect);
	static void SetClippingRectangle(Rectangle* rect);
	static Rectangle* GetClippingRectangle();
	static short GetSelectionBufferValue(int x, int y);

	static int ScreenDrawTextGetTextWidth(std::string text, Font* font);
	static int ScreenDrawTextGetTextHeight(Font* font);

	static void* CreatePixelDataFromSurface(SDL_Surface* surface);

	static void ScreenDrawLine(int x0, int y0, int x1, int y1);
	static void ScreenDrawRectangle(int x0, int y0, int x1, int y1);
	static void ScreenDrawFilledRectangle(int x0, int y0, int x1, int y1);
	__forceinline static void ScreenDrawText(std::string text, Font* font, int x, int y) { renderer->ScreenDrawText(text, font, x, y); }
	static void ScreenDrawTexture(Texture* texture, int x, int y);
	__forceinline static void ScreenDrawTexture(Texture* texture, Rectangle* rectSource, Rectangle* rectTarget) { renderer->ScreenDrawTexture(texture, rectSource, rectTarget); }
	static void ScreenDrawTriangle(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2);
	static void ScreenDrawFillTriangle(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2);
	static void ScreenDrawFillTriangleFlatBottom(Math::Vec4& v0, Math::Vec4& v1, Math::Vec4& v2);
	static void ScreenDrawFillTriangleFlatTop(Math::Vec4& v0, Math::Vec4& v1, Math::Vec4& v2);
	static void ScreenDrawFillTriangleFlatBottomWithDepthTesting(Math::Vec4& v0, Math::Vec4& v1, Math::Vec4& v2);
	static void ScreenDrawFillTriangleFlatTopWithDepthTesting(Math::Vec4& v0, Math::Vec4& v1, Math::Vec4& v2);
	static void ScreenDrawTexturedTriangleFlatBottom(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2);
	static void ScreenDrawTexturedTriangleFlatTop(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2);
};
