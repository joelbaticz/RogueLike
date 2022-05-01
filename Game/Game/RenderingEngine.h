#pragma once

#include <string>
#include "SDL.h"
#include "LogEngine.h"
#include "RenderingEngine.h"
#include "Node.h"
#include "Color.h"
#include "Font.h"
#include "Texture.h"
#include "Rectangle.h"


class RenderingEngine
{
private:
	static std::string		s_ComponentName;
	static SDL_Window*		s_Window;
	static SDL_Renderer*    s_Renderer;
	static Color*			s_CurrentPenColor;
	static Color*			s_CurrentFillColor;
	static Rectangle*		s_ClippingRectangle;
	static SDL_Texture*		s_FrameBufferTexture;
	static uint8_t*			s_FrameBuffer;
	static SDL_Surface*		s_FrameBufferSurface;
	static SDL_Surface*		s_FrameBufferHelperSurface;
	static int				s_FrameX;
	static int				s_FrameY;
	static int				s_FrameWidth;
	static int				s_FrameHeight;
	static bool				s_WindowIsShown;
	
	RenderingEngine();
	~RenderingEngine();

	static void ClearScreen();
	static void CreateFrameBuffer();

public:
	static int Init(std::string windowTitle, int windowX, int windowY, int windowWidth, int windowHeigh);
	static void UnInit();

	static void ShowWindow(bool isShow);
	static void SetWindowFullScreen();
	static void SetWindowMinimize();

	static void BeginFrame();
	static void PresentFrame();

	static SDL_Renderer* GetRenderer();
	static void SetPenColor(Color* color);
	static void SetFillColor(Color* color);

	static void ScreenDrawLine(int x0, int y0, int x1, int y1);
	static void ScreenDrawRectangle(int x0, int y0, int x1, int y1);
	static void ScreenDrawFilledRectangle(int x0, int y0, int x1, int y1);
	static void ScreenDrawText(std::string text, Font* font, int x, int y);
	static void ScreenDrawTexture(Texture* texture, int x, int y);
	static void ScreenDrawTexture(Texture* texture, Rectangle* rectSource, Rectangle* rectTarget);
	


	//static void DrawRectangle(Node* node, int x, int y, int w, int h);
	static void DrawFilledRectangle(Node* node, int x, int y, int w, int h);
	static void DrawText(Node* node, std::string text, Font* font, int x, int y);
	static void DrawTexture(Texture* texture, int x, int y);
	static void DrawTexture(Node* node, Texture* texture, SDL_Rect* rectSource, SDL_Rect* rectTarget);

	static Rectangle* ClipToParentRectangle(Node* node, Rectangle* rect);
	static void SetClippingRectangle(Rectangle* rect);
	static Rectangle* GetClippingRectangle();
};