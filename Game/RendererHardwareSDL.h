#pragma once
#include "Renderer.h"

class RendererHardwareSDL : public Renderer
{
protected:
	//uint32_t* m_FrameBuffer;
	//SDL_Surface* m_FrameBufferSurface;
	//SDL_Surface* m_FrameBufferHelperSurface;
	//SDL_Texture* m_FrameBufferTexture;

	void CreateFrameBuffer() override;
public:
	RendererHardwareSDL(RendererOptions* rendererOptions);
	~RendererHardwareSDL();

	void BeginFrame() override;
	void PresentFrame() override;

	void* CreatePixelDataFromSurface(SDL_Surface* surface) override;

	void ScreenDrawLine(int x0, int y0, int x1, int y1) override;
	//void ScreenDrawRectangle(int x0, int y0, int x1, int y1) override;
	//void ScreenDrawFilledRectangle(int x0, int y0, int x1, int y1) override;
	//int ScreenDrawTextGetTextWidth(std::string text, Font* font) override;
	//int ScreenDrawTextGetTextHeight(Font* font) override;
	//void ScreenDrawTexture(Texture* texture, int x, int y) override;
	void ScreenDrawText(std::string text, Font* font, int x, int y) override;
	void ScreenDrawTexture(Texture* texture, Rectangle* rectSource, Rectangle* rectTarget) override;
	void ScreenDrawTriangle(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2) override;
	//void ScreenDrawFillTriangle(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2) override;
	//void ScreenDrawFillTriangleFlatBottom(Math::Vec4& v0, Math::Vec4& v1, Math::Vec4& v2) override;
	//void ScreenDrawFillTriangleFlatTop(Math::Vec4& v0, Math::Vec4& v1, Math::Vec4& v2) override;
	//void ScreenDrawFillTriangleFlatBottomWithDepthTesting(Math::Vec4& v0, Math::Vec4& v1, Math::Vec4& v2) override;
	//void ScreenDrawFillTriangleFlatTopWithDepthTesting(Math::Vec4& v0, Math::Vec4& v1, Math::Vec4& v2) override;
	//void ScreenDrawTexturedTriangleFlatBottom(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2) override;
	//void ScreenDrawTexturedTriangleFlatTop(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2) override;
};
