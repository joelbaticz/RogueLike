#include "RendererFront.h"
#include "RendererFactory.h"
#include "Renderer.h"

RendererOptions*	RendererFront::rendererOptions = nullptr;
RendererFactory*	RendererFront::rendererFactory = nullptr;
Renderer*			RendererFront::renderer = nullptr;

int RendererFront::Init(int windowX, int windowY, int windowWidth, int windowHeigh, bool isFullScreen, std::string windowTitle)
{
	rendererOptions = new RendererOptions();
	rendererOptions->windowTitle = windowTitle;
	rendererOptions->windowX = windowX;
	rendererOptions->windowY = windowY;
	rendererOptions->windowWidth = windowWidth;
	rendererOptions->windowHeight = windowHeigh;
	rendererOptions->windowIsFullScreen = isFullScreen;
	rendererOptions->colorDepthBits = 32;
	rendererOptions->refreshRate = 60;
	rendererOptions->rendererType = RendererType::SDL;
	//rendererOptions->rendererType = RendererType::Software;

	rendererFactory = new RendererFactory();

	renderer = rendererFactory->CreateRenderer(rendererOptions);

	if (renderer == nullptr)
	{
		return 1;
	}

	renderer->Init();

	return 0;
}

void RendererFront::UnInit()
{
	if (renderer != nullptr)
	{
		renderer->UnInit();
	}	

	delete renderer;
	delete rendererFactory;
	delete rendererOptions;
}

void RendererFront::ShowWindow(bool isShow)
{
	renderer->ShowWindow(isShow);
}

void RendererFront::SetWindowFullScreen()
{
	renderer->SetWindowFullScreen();
}

void RendererFront::SetWindowMinimize()
{
	renderer->SetWindowMinimize();
}

void RendererFront::BeginFrame()
{
	renderer->BeginFrame();
}

void RendererFront::PresentFrame()
{
	renderer->PresentFrame();
}

SDL_Renderer* RendererFront::GetRenderer()
{
	return renderer->GetRenderer();
}

int RendererFront::GetWindowWidth()
{
	return renderer->GetWindowWidth();
}

int RendererFront::GetWindowHeight()
{
	return renderer->GetWindowHeight();
}

void RendererFront::SetPenColor(Color* color)
{
	renderer->SetPenColor(color);
}

void RendererFront::SetFillColor(Color* color)
{
	renderer->SetFillColor(color);
}

void RendererFront::SetDrawMode(DrawMode drawMode)
{
	renderer->SetDrawMode(drawMode);
}

void RendererFront::SetTexture(Texture* texture)
{
	renderer->SetTexture(texture);
}

Rectangle* RendererFront::ClipToParentRectangle(Node* node, Rectangle* rect)
{
	return renderer->ClipToParentRectangle(node, rect);
}

void RendererFront::SetClippingRectangle(Rectangle* rect)
{
	renderer->SetClippingRectangle(rect);
}

Rectangle* RendererFront::GetClippingRectangle()
{
	return renderer->GetClippingRectangle();
}

short RendererFront::GetSelectionBufferValue(int x, int y)
{
	return renderer->GetSelectionBufferValue(x, y);
}

void* RendererFront::CreatePixelDataFromSurface(SDL_Surface* surface)
{
	return renderer->CreatePixelDataFromSurface(surface);
}

void RendererFront::ScreenDrawLine(int x0, int y0, int x1, int y1)
{
	renderer->ScreenDrawLine(x0, y0, x1, y1);
}

void RendererFront::ScreenDrawRectangle(int x0, int y0, int x1, int y1)
{
}

void RendererFront::ScreenDrawFilledRectangle(int x0, int y0, int x1, int y1)
{
}

// ForceInlined! in the header
//void RendererFront::ScreenDrawText(std::string text, Font* font, int x, int y)
//{
//}

int RendererFront::ScreenDrawTextGetTextWidth(std::string text, Font* font)
{
	return renderer->ScreenDrawTextGetTextWidth(text, font);
}

int RendererFront::ScreenDrawTextGetTextHeight(Font* font)
{
	return renderer->ScreenDrawTextGetTextHeight(font);
}

void RendererFront::ScreenDrawTexture(Texture* texture, int x, int y)
{
}

// ForceInlined! in the header
//void RendererFront::ScreenDrawTexture(Texture* texture, Rectangle* rectSource, Rectangle* rectTarget)
//{
//	renderer->ScreenDrawTexture(texture, rectSource, rectTarget);
//}

void RendererFront::ScreenDrawTriangle(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2)
{
	renderer->ScreenDrawTriangle(v0, v1, v2);
}

void RendererFront::ScreenDrawFillTriangle(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2)
{
}

void RendererFront::ScreenDrawFillTriangleFlatBottom(Math::Vec4& v0, Math::Vec4& v1, Math::Vec4& v2)
{
}

void RendererFront::ScreenDrawFillTriangleFlatTop(Math::Vec4& v0, Math::Vec4& v1, Math::Vec4& v2)
{
}

void RendererFront::ScreenDrawFillTriangleFlatBottomWithDepthTesting(Math::Vec4& v0, Math::Vec4& v1, Math::Vec4& v2)
{
}

void RendererFront::ScreenDrawFillTriangleFlatTopWithDepthTesting(Math::Vec4& v0, Math::Vec4& v1, Math::Vec4& v2)
{
}

void RendererFront::ScreenDrawTexturedTriangleFlatBottom(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2)
{
}

void RendererFront::ScreenDrawTexturedTriangleFlatTop(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2)
{
}
