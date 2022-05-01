#include "RendererHardwareSDL.h"
#include "AssetManager.h"

RendererHardwareSDL::RendererHardwareSDL(RendererOptions* rendererOptions) : Renderer(rendererOptions)
{ }

RendererHardwareSDL::~RendererHardwareSDL() = default;

void RendererHardwareSDL::CreateFrameBuffer()
{
	//m_FrameBufferTexture = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, m_FrameWidth, m_FrameHeight);
}

void RendererHardwareSDL::BeginFrame()
{
	SDL_SetRenderDrawColor(m_Renderer, 0, 32, 64, 255);
	SDL_RenderClear(m_Renderer);
}

void RendererHardwareSDL::PresentFrame()
{
	SDL_RenderPresent(m_Renderer);
}

void* RendererHardwareSDL::CreatePixelDataFromSurface(SDL_Surface * surface)
{
	int textureWidth = surface->w;
	int textureHeight = surface->h;
	int textureWidthInBytes = surface->pitch;// > w; //We are creating 8bit out of 24bits [sdlSurface->pitch];
	int textureBytesPerPixel = textureWidthInBytes / textureWidth;

	//return new uint32_t[1];

	uint32_t* pixelData = new uint32_t[textureWidth * textureHeight];

	for (int y = 0; y < textureHeight; y++)
	{
		for (int x = 0; x < textureWidth; x++)
		{
			//uint32_t color32bit = ((uint32_t*)surface->pixels)[y * textureWidthInBytes / 4 + x * textureBytesPerPixel / 4];

			uint8_t alphaValue = ((uint8_t*)surface->pixels)[y * textureWidthInBytes + x * textureBytesPerPixel + 3];
			uint8_t redValue = ((uint8_t*)surface->pixels)[y * textureWidthInBytes + x * textureBytesPerPixel];
			uint8_t greenValue = ((uint8_t*)surface->pixels)[y * textureWidthInBytes + x * textureBytesPerPixel + 1];
			uint8_t blueValue = ((uint8_t*)surface->pixels)[y * textureWidthInBytes + x * textureBytesPerPixel + 2];

			uint32_t color32bit = 255 << 24 | redValue << 16 | greenValue << 8 | blueValue;

			pixelData[y * textureWidth + x] = color32bit;

			if (redValue == 255 && greenValue == 0 && blueValue == 255)
			{
				((uint8_t*)surface->pixels)[y * textureWidthInBytes + x * textureBytesPerPixel] = 0;
				((uint8_t*)surface->pixels)[y * textureWidthInBytes + x * textureBytesPerPixel + 1] = 0;
				((uint8_t*)surface->pixels)[y * textureWidthInBytes + x * textureBytesPerPixel + 2] = 0;
				((uint8_t*)surface->pixels)[y * textureWidthInBytes + x * textureBytesPerPixel + 3] = 0;
			}
		}
	}

	return pixelData;
}

__forceinline void RendererHardwareSDL::ScreenDrawText(std::string text, Font* font, int x, int y)
{
	TextureAtlas* fontTextureAtlas = font->GetTextureAtlas();

	int fontTop = font->GetTop();
	int fontBottom = font->GetBottom();
	int fontHeight = fontBottom - fontTop;

	Rectangle rectSource = Rectangle();
	Rectangle* pRectSource = &rectSource;

	Rectangle rectTarget = Rectangle(x, y, 0, 0);
	Rectangle* pRectTarget = &rectTarget;

	for (int i = 0; i < text.length(); i++)
	{
		int asciiCode = text[i];

		fontTextureAtlas->GetTextureRectangle(asciiCode, pRectSource);

		pRectSource->SetY(pRectSource->GetY() + fontTop);
		pRectSource->SetWidth(font->GetCharacterWidth(asciiCode));
		pRectSource->SetHeight(fontHeight);

		pRectTarget->SetWidth(font->GetCharacterWidth(asciiCode));
		pRectTarget->SetHeight(fontHeight);

		ScreenDrawTexture(fontTextureAtlas, pRectSource, pRectTarget);

		pRectTarget->SetX(pRectTarget->GetX() + font->GetCharacterWidth(asciiCode));
	}
}

__forceinline void RendererHardwareSDL::ScreenDrawTexture(Texture * texture, Rectangle * rectSource, Rectangle * rectTarget)
{
	if (m_ClippingRectangle->IsEmpty())
	{
		return;
	}

	//Target Rectangle
 	int targetWidth = rectTarget->GetWidth();
	int targetHeight = rectTarget->GetHeight();
	int targetX0 = rectTarget->GetX();
	int targetY0 = rectTarget->GetY();
	int targetX1 = targetX0 + targetWidth;
	int targetY1 = targetY0 + targetHeight;

	//Clipping Rectangle
	//int clipX0 = m_ClippingRectangle->GetX();
	//int clipY0 = m_ClippingRectangle->GetY();
	//int clipX1 = clipX0 + m_ClippingRectangle->GetWidth();
	//int clipY1 = clipY0 + m_ClippingRectangle->GetHeight();
	SDL_Rect* clipRect = &SDL_Rect();
	clipRect->x = m_ClippingRectangle->GetX();
	clipRect->y = m_ClippingRectangle->GetY();
	clipRect->w = m_ClippingRectangle->GetWidth();
	clipRect->h = m_ClippingRectangle->GetHeight();

	SDL_RenderSetClipRect(m_Renderer, clipRect);

	//Actual Drawing Rectangle
	/*int drawX0 = Max(targetX0, clipX0);
	int drawY0 = Max(targetY0, clipY0);
	int drawX1 = Min(targetX1, clipX1);
	int drawY1 = Min(targetY1, clipY1);
	int drawWidth = drawX1 - drawX0;
	int drawHeight = drawY1 - drawY0;*/

	//Source Rectangle
	int sourceX0 = rectSource->GetX();
	int sourceY0 = rectSource->GetY();
	int sourceWidth = rectSource->GetWidth();
	int sourceHeight = rectSource->GetHeight();

	SDL_Rect* sourceRect = &SDL_Rect();
	sourceRect->x = sourceX0;
	sourceRect->y = sourceY0;
	sourceRect->w = sourceWidth;
	sourceRect->h = sourceHeight;

	SDL_Rect* targetRect = &SDL_Rect();
	//targetRect->x = drawX0;
	//targetRect->y = drawY0;
	//targetRect->w = drawWidth;
	//targetRect->h = drawHeight;
	targetRect->x = targetX0;
	targetRect->y = targetY0;
	targetRect->w = targetWidth;
	targetRect->h = targetHeight;

	//SDL_SetTextureBlendMode(texture->GetTexture(), SDL_BlendMode::SDL_BLENDMODE_BLEND);
	SDL_RenderCopy(m_Renderer, texture->GetTexture(), sourceRect, targetRect);
	//SDL_SetRenderDrawColor(m_Renderer, 0, 255, 0, 255);
	//SDL_RenderDrawLine(m_Renderer, 0, 0, 640, 480);
}

void RendererHardwareSDL::ScreenDrawTriangle(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2)
{

}

void RendererHardwareSDL::ScreenDrawLine(int x0, int y0, int x1, int y1)
{
	
}

