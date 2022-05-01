#pragma once
#include <SDL.h>
#include <string>
#include "Color.h"
#include "Texture.h"
#include "Rectangle.h"
#include "DrawMode.h"
#include "RendererOptions.h"
#include "Node.h"
#include "Font.h"
#include "Math.h"

class Renderer
{
protected:
	RendererOptions*	m_RendererOptions;
	std::string			m_ComponentName;
	SDL_Window*			m_Window;
	SDL_Renderer*		m_Renderer;
	Color*				m_CurrentPenColor;
	Color*				m_CurrentFillColor;
	Texture*			m_CurrentTexture;
	Rectangle*			m_ClippingRectangle;
	float*				m_DepthBuffer;
	short*				m_SelectionBuffer; //Stencil Buffer
	DrawMode			m_DrawMode = DrawMode(DrawMode::Filled);
	int					m_FrameX;
	int					m_FrameY;
	int					m_FrameWidth;
	int					m_FrameHeight;
	bool				m_WindowIsShown;

	int Max(int value1, int value2);
	int Min(int value1, int value2);
	void Swap(int& value1, int& value2);

	void ClearScreen();
	virtual void CreateFrameBuffer() abstract;
public:
	Renderer(RendererOptions* rendererOptions);
	~Renderer();

	int Init();
	void UnInit();

	void ShowWindow(bool isShow);
	void SetWindowFullScreen();
	void SetWindowMinimize();

	SDL_Renderer* GetRenderer();
	int GetWindowWidth();
	int GetWindowHeight();
	Rectangle* GetClippingRectangle();

	void SetPenColor(Color* color);
	void SetFillColor(Color* color);
	void SetDrawMode(DrawMode drawMode);
	void SetTexture(Texture* texture);
	void SetClippingRectangle(Rectangle* rect);
	
	Rectangle* ClipToParentRectangle(Node* node, Rectangle* rect);

	short GetSelectionBufferValue(int x, int y);

	int ScreenDrawTextGetTextWidth(std::string text, Font* font);
	int ScreenDrawTextGetTextHeight(Font* font);

	virtual void BeginFrame() abstract;
	virtual void PresentFrame() abstract;

	virtual void* CreatePixelDataFromSurface(SDL_Surface* surface) abstract;


	virtual void ScreenDrawLine(int x0, int y0, int x1, int y1) abstract;
	//virtual void ScreenDrawRectangle(int x0, int y0, int x1, int y1) abstract;
	//virtual void ScreenDrawFilledRectangle(int x0, int y0, int x1, int y1) abstract;
	virtual void ScreenDrawText(std::string text, Font* font, int x, int y) abstract;
	//virtual void ScreenDrawTexture(Texture* texture, int x, int y) abstract;
	virtual void ScreenDrawTexture(Texture* texture, Rectangle* rectSource, Rectangle* rectTarget) abstract;
	virtual void ScreenDrawTriangle(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2) abstract;
	//virtual void ScreenDrawFillTriangle(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2) abstract;
	//virtual void ScreenDrawFillTriangleFlatBottom(Math::Vec4& v0, Math::Vec4& v1, Math::Vec4& v2) abstract;
	//virtual void ScreenDrawFillTriangleFlatTop(Math::Vec4& v0, Math::Vec4& v1, Math::Vec4& v2) abstract;
	//virtual void ScreenDrawFillTriangleFlatBottomWithDepthTesting(Math::Vec4& v0, Math::Vec4& v1, Math::Vec4& v2) abstract;
	//virtual void ScreenDrawFillTriangleFlatTopWithDepthTesting(Math::Vec4& v0, Math::Vec4& v1, Math::Vec4& v2) abstract;
	//virtual void ScreenDrawTexturedTriangleFlatBottom(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2) abstract;
	//virtual void ScreenDrawTexturedTriangleFlatTop(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2) abstract;

	void Swap(Math::Vertex& v0, Math::Vertex& v1);
};
