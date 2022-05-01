#include "Renderer.h"
#include "LogEngine.h"
#include <SDL_ttf.h>
#include "AssetManager.h"

Renderer::Renderer(RendererOptions* rendererOptions)
{
	m_RendererOptions = rendererOptions;

	m_ComponentName = "Renderer";
	m_Window = nullptr;
	m_Renderer = nullptr;
	m_CurrentFillColor = nullptr;
	m_CurrentPenColor = nullptr;
	m_FrameX = rendererOptions->windowX;
	m_FrameY = rendererOptions->windowY;
	m_FrameWidth = rendererOptions->windowWidth;
	m_FrameHeight = rendererOptions->windowHeight;
	m_DrawMode = DrawMode(DrawMode::Filled);
}

Renderer::~Renderer() = default;

int Renderer::Init()
{
	LogEngine::Log(LOG_DEBUG, m_ComponentName, "Init() called.");

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		LogEngine::Log(LOG_ERROR, m_ComponentName, SDL_GetError());
		return 1;
	}
	LogEngine::Log(LOG_DEBUG, m_ComponentName, "SDL_Init...OK");

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		LogEngine::Log(LOG_ERROR, m_ComponentName, SDL_GetError());
		return 1;
	}
	LogEngine::Log(LOG_DEBUG, m_ComponentName, "SDL_Image...OK");

	if (TTF_Init() != 0)
	{
		LogEngine::Log(LOG_ERROR, m_ComponentName, SDL_GetError());
		return 1;
	}
	LogEngine::Log(LOG_DEBUG, m_ComponentName, "SDL_Ttf...OK");

	Uint32 rendererFlags = SDL_WINDOW_SHOWN;

	if (m_RendererOptions->windowIsFullScreen)
	{
		rendererFlags |= SDL_WINDOW_FULLSCREEN;
	}

	m_Window = SDL_CreateWindow(m_RendererOptions->windowTitle.c_str(), m_RendererOptions->windowX, m_RendererOptions->windowY, m_RendererOptions->windowWidth, m_RendererOptions->windowHeight, rendererFlags);
	//   SDL_WINDOW_SHOWN
	//   SDL_WINDOW_HIDDEN
	// | SDL_WINDOW_BORDERLESS
	// | SDL_WINDOW_FULLSCREEN	

	if (m_Window == nullptr)
	{
		LogEngine::Log(LOG_ERROR, m_ComponentName, SDL_GetError());
		return 1;
	}
	LogEngine::Log(LOG_DEBUG, m_ComponentName, "Creating window...OK");

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_TARGETTEXTURE);// | SDL_RENDERER_ACCELERATED | SDL_WINDOW_OPENGL);
	// SDL_RENDERER_TARGETTEXTURE
	// | SDL_RENDERER_SOFTWARE
	// | SDL_RENDERER_ACCELERATED
	// | SDL_RENDERER_PRESENTVSYNC
	// | SDL_WINDOW_OPENGL
	// | SDL_WINDOW_VULKAN

	if (m_Renderer == nullptr)
	{
		LogEngine::Log(LOG_ERROR, m_ComponentName, SDL_GetError());
		return 1;
	}

	LogEngine::Log(LOG_DEBUG, m_ComponentName, "Creating renderer...OK");

	ClearScreen();

	m_CurrentPenColor = AssetManager::CreateColor(255, 192, 192, 192);
	m_CurrentFillColor = AssetManager::CreateColor(255, 128, 128, 128);
	m_DrawMode = DrawMode::Filled;
	m_CurrentTexture = AssetManager::CreateTextureAtlas("DefaultTextureSet.png");
	m_ClippingRectangle = new Rectangle(0, 0, 640, 580);

	LogEngine::Log(LOG_TRACE, m_ComponentName, "Setting default resources...OK.");

	CreateFrameBuffer();

	LogEngine::Log(LOG_TRACE, m_ComponentName, "Creating buffers...OK.");

	LogEngine::Log(LOG_TRACE, m_ComponentName, "Renderer Init...OK.");
	return 0;
}

void Renderer::UnInit()
{
	if (m_CurrentPenColor != nullptr)
	{
		delete m_CurrentPenColor;
	}

	if (m_CurrentFillColor != nullptr)
	{
		delete m_CurrentFillColor;
	}

	if (m_CurrentTexture != nullptr)
	{
		//delete m_CurrentTexture;
	}

	if (m_ClippingRectangle != nullptr)
	{
		delete m_ClippingRectangle;
	}

	if (m_RendererOptions != nullptr)
	{
		//delete m_RendererOptions;
	}

	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
	}

	if (m_Window != nullptr)
	{
		SDL_DestroyWindow(m_Window);
	}

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int Renderer::Max(int value1, int value2)
{
	if (value1 > value2)
	{
		return value1;
	}

	return value2;
}

int Renderer::Min(int value1, int value2)
{
	if (value1 < value2)
	{
		return value1;
	}

	return value2;
}

void Renderer::Swap(int& value1, int& value2)
{
	int temp = value1;
	value1 = value2;
	value2 = temp;
}

void Renderer::ClearScreen()
{
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_Renderer);
	SDL_RenderPresent(m_Renderer);
}

void Renderer::ShowWindow(bool isShow)
{
	if (isShow)
	{
		SDL_ShowWindow(m_Window);
		m_WindowIsShown = true;
	}
	else
	{
		SDL_HideWindow(m_Window);
		m_WindowIsShown = false;
	}
}

void Renderer::SetWindowFullScreen()
{
	//SDL_SetWindowFullscreen(s_Window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	SDL_SetWindowPosition(m_Window, 0, 0);
}

void Renderer::SetWindowMinimize()
{
	throw std::logic_error("Not implemented");
}

SDL_Renderer* Renderer::GetRenderer()
{
	return m_Renderer;
}

int Renderer::GetWindowWidth()
{
	return m_FrameWidth;
}

int Renderer::GetWindowHeight()
{
	return m_FrameHeight;
}

void Renderer::SetPenColor(Color* color)
{
	m_CurrentPenColor = color;
}

void Renderer::SetFillColor(Color* color)
{
	m_CurrentFillColor = color;
}

void Renderer::SetDrawMode(DrawMode drawMode)
{
	m_DrawMode = drawMode;
}

void Renderer::SetTexture(Texture* texture)
{
	m_CurrentTexture = texture;
}

void Renderer::SetClippingRectangle(Rectangle* rect)
{
	if (m_ClippingRectangle != nullptr)
	{
		delete m_ClippingRectangle;
	}

	int clipX0 = rect->GetX();
	int clipY0 = rect->GetY();
	int clipX1 = clipX0 + rect->GetWidth();
	int clipY1 = clipY0 + rect->GetHeight();

	if (clipX0 < 0)
	{
		clipX0 = 0;
	}

	if (clipX1 < 0)
	{
		clipX1 = 0;
	}

	if (clipX0 > m_FrameWidth)
	{
		clipX0 = m_FrameWidth;
	}

	if (clipX1 > m_FrameWidth)
	{
		clipX1 = m_FrameWidth;
	}

	if (clipY0 < 0)
	{
		clipY0 = 0;
	}

	if (clipY1 < 0)
	{
		clipY1 = 0;
	}

	if (clipY0 > m_FrameHeight)
	{
		clipY0 = m_FrameHeight;
	}

	if (clipY1 > m_FrameHeight)
	{
		clipY1 = m_FrameHeight;
	}

	/*if (clipX + clipW > s_FrameWidth)
	{
		clipW -= clipX + clipW - s_FrameWidth;
	}
*/

	m_ClippingRectangle = new Rectangle(clipX0, clipY0, clipX1 - clipX0, clipY1 - clipY0);
}

Rectangle* Renderer::GetClippingRectangle()
{
	return m_ClippingRectangle;
}

Rectangle* Renderer::ClipToParentRectangle(Node* node, Rectangle* rectResult)
{
	//Should create new Rect for result???
	//Rectangle* rectResult = rect;//new Rectangle(rect);

	//node = node->GetParent();
	//We need to process the current node as well
	while (node != nullptr)
	{
		if (dynamic_cast<CanvasNode*>(node))
		{
			//Node is Drawable
			CanvasNode* cNode = (CanvasNode*)node;
			//TODO: It should be GetClientRectangle instead
			int cNodeX = cNode->GetX();
			int cNodeY = cNode->GetY();
			int cNodeW = cNode->GetWidth();
			int cNodeH = cNode->GetHeight();

			rectResult->SetX(rectResult->GetX() + cNodeX);
			rectResult->SetY(rectResult->GetY() + cNodeY);

			// Experimental:
			if (rectResult->GetX() < cNodeX)
			{
				rectResult->SetX(cNodeX);
			}
			if (rectResult->GetY() < cNodeY)
			{
				rectResult->SetY(cNodeY);
			}

			if (rectResult->GetX() + rectResult->GetWidth() > cNodeX + cNodeW)
			{
				rectResult->SetWidth(cNodeX + cNodeW - rectResult->GetX());
			}
			if (rectResult->GetY() + rectResult->GetHeight() > cNodeY + cNodeH)
			{
				rectResult->SetHeight(cNodeY + cNodeH - rectResult->GetY());
			}
			if (rectResult->GetWidth() < 0) rectResult->SetWidth(0);
			if (rectResult->GetHeight() < 0) rectResult->SetHeight(0);

		}
		node = node->GetParent();
	}

	return rectResult;
}

short Renderer::GetSelectionBufferValue(int x, int y)
{
	int offset = y * m_FrameWidth + x;

	return m_SelectionBuffer[offset];
}

int Renderer::ScreenDrawTextGetTextWidth(std::string text, Font* font)
{
	int width = 0;

	for (int i = 0; i < text.length(); i++)
	{
		int asciiCode = text[i];
		width += font->GetCharacterWidth(asciiCode);
	}

	return width;
}

int Renderer::ScreenDrawTextGetTextHeight(Font* font)
{
	return font->GetBottom() - font->GetTop();
}

void Renderer::Swap(Math::Vertex& v0, Math::Vertex& v1)
{
	Math::Vertex temp = v0;
	v0 = v1;
	v1 = temp;
}
