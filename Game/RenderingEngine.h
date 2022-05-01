#pragma once

#define MODE_16BIT

#include <string>
#include "SDL.h"
#include "LogEngine.h"
#include "Node.h"
#include "Color.h"
#include "Font.h"
#include "Texture.h"
#include "Rectangle.h"
#include "Math.h"
#include "DrawMode.h"

class RenderingEngine
{
private:
	static std::string		s_ComponentName;
	static SDL_Window*		s_Window;
	static SDL_Renderer*    s_Renderer;
	static Color*			s_CurrentPenColor;
	static Color*			s_CurrentFillColor;
	static uint8_t			s_TransparentColorIndex;
	static Texture*			s_CurrentTexture;
	static Rectangle*		s_ClippingRectangle;
	static SDL_Texture*		s_FrameBufferTexture;

#ifdef MODE_16BIT
	static uint16_t* s_FrameBuffer;
#else
	static uint8_t* s_FrameBuffer;
#endif
	
	static SDL_Surface*		s_FrameBufferSurface;
	static SDL_Surface*		s_FrameBufferHelperSurface;
	static float*			s_DepthBuffer;
	static short*			s_SelectionBuffer; //Stencil Buffer
	static int				s_FrameX;
	static int				s_FrameY;
	static int				s_FrameWidth;
	static int				s_FrameHeight;
	static bool				s_WindowIsShown;
	static DrawMode			s_DrawMode;
	
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
	static int GetWindowWidth();
	static int GetWindowHeight();
	static void SetPenColor(Color* color);
	static void SetFillColor(Color* color);
	static void SetDrawMode(DrawMode drawMode);
	static void SetTexture(Texture* texture);

	static void ScreenDrawLine(int x0, int y0, int x1, int y1);
	static void ScreenDrawRectangle(int x0, int y0, int x1, int y1);
	static void ScreenDrawFilledRectangle(int x0, int y0, int x1, int y1);
	static void ScreenDrawText(std::string text, Font* font, int x, int y);
	static int ScreenDrawTextGetTextWidth(std::string text, Font* font);
	static int ScreenDrawTextGetTextHeight(Font* font);
	static void ScreenDrawTexture(Texture* texture, int x, int y);
	static inline void ScreenDrawTexture(Texture* texture, Rectangle* rectSource, Rectangle* rectTarget);
	static void ScreenDrawTriangle(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2);
	static void ScreenDrawFillTriangle(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2);
	static void ScreenDrawFillTriangleFlatBottom(Math::Vec4& v0, Math::Vec4& v1, Math::Vec4& v2);
	static void ScreenDrawFillTriangleFlatTop(Math::Vec4& v0, Math::Vec4& v1, Math::Vec4& v2);
	static void ScreenDrawFillTriangleFlatBottomWithDepthTesting(Math::Vec4& v0, Math::Vec4& v1, Math::Vec4& v2);
	static void ScreenDrawFillTriangleFlatTopWithDepthTesting(Math::Vec4& v0, Math::Vec4& v1, Math::Vec4& v2);
	static void ScreenDrawTexturedTriangleFlatBottom(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2);
	static void ScreenDrawTexturedTriangleFlatTop(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2);

	static Rectangle* ClipToParentRectangle(Node* node, Rectangle* rect);
	static void SetClippingRectangle(Rectangle* rect);
	static Rectangle* GetClippingRectangle();

	static short GetSelectionBufferValue(int x, int y);

	//OBSOLETE
	//static void DrawRectangle(Node* node, int x, int y, int w, int h);
	static void DrawFilledRectangle(Node* node, int x, int y, int w, int h);
	static void DrawText(Node* node, std::string text, Font* font, int x, int y);
	static void DrawTexture(Texture* texture, int x, int y);
	static void DrawTexture(Node* node, Texture* texture, SDL_Rect* rectSource, SDL_Rect* rectTarget);
};