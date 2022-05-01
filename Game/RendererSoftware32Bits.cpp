#include "RendererSoftware32Bits.h"
#include "AssetManager.h"

RendererSoftware32Bits::RendererSoftware32Bits(RendererOptions* rendererOptions) : Renderer(rendererOptions)
{ }

RendererSoftware32Bits::~RendererSoftware32Bits() = default;

void RendererSoftware32Bits::CreateFrameBuffer()
{
	m_FrameBufferTexture = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, m_FrameWidth, m_FrameHeight);

	void* pixels;
	int pitch;
	SDL_LockTexture(m_FrameBufferTexture, NULL, &pixels, &pitch);

	m_FrameBuffer = (uint32_t*)pixels;
}

void RendererSoftware32Bits::BeginFrame()
{
	SDL_SetRenderDrawColor(m_Renderer, 0, 255, 0, 255);
	SDL_RenderClear(m_Renderer);
}

void RendererSoftware32Bits::PresentFrame()
{
	void* pixels;
	int pitch;
	SDL_Rect* rect = &SDL_Rect();
	rect->x = 100;
	rect->y = 100;
	rect->w = 400;
	rect->h = 400;

	SDL_UnlockTexture(m_FrameBufferTexture);

	SDL_RenderCopy(m_Renderer, m_FrameBufferTexture, NULL, NULL);
	//SDL_RenderFillRect(m_Renderer, rect);
	//SDL_BlitScaled()
	SDL_RenderPresent(m_Renderer);

	SDL_LockTexture(m_FrameBufferTexture, NULL, &pixels, &pitch);
}

void* RendererSoftware32Bits::CreatePixelDataFromSurface(SDL_Surface * surface)
{
	int textureWidth = surface->w;
	int textureHeight = surface->h;
	int textureWidthInBytes = surface->pitch;// > w; //We are creating 8bit out of 24bits [sdlSurface->pitch];
	int textureBytesPerPixel = textureWidthInBytes / textureWidth;

	uint32_t* pixelData = new uint32_t[textureWidth * textureHeight];

	for (int y = 0; y < textureHeight; y++)
	{
		for (int x = 0; x < textureWidth; x++)
		{
			//uint32_t color32bit = ((uint32_t*)surface->pixels)[y * textureWidthInBytes / 4 + x * textureBytesPerPixel / 4];

			//uint8_t alphaValue = ((uint8_t*)sdlSurface->pixels)[y * textureWidthInBytes + x * textureBytesPerPixel];
			uint8_t redValue = ((uint8_t*)surface->pixels)[y * textureWidthInBytes + x * textureBytesPerPixel];
			uint8_t greenValue = ((uint8_t*)surface->pixels)[y * textureWidthInBytes + x * textureBytesPerPixel + 1];
			uint8_t blueValue = ((uint8_t*)surface->pixels)[y * textureWidthInBytes + x * textureBytesPerPixel + 2];

			uint32_t color32bit = 255 << 24 | redValue << 16 | greenValue << 8 | blueValue;

			pixelData[y * textureWidth + x] = color32bit;
		}
	}

	return pixelData;
}

__forceinline void RendererSoftware32Bits::ScreenDrawText(std::string text, Font* font, int x, int y)
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

__forceinline void RendererSoftware32Bits::ScreenDrawTexture(Texture * texture, Rectangle * rectSource, Rectangle * rectTarget)
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
	int clipX0 = m_ClippingRectangle->GetX();
	int clipY0 = m_ClippingRectangle->GetY();
	int clipX1 = clipX0 + m_ClippingRectangle->GetWidth();
	int clipY1 = clipY0 + m_ClippingRectangle->GetHeight();

	//Actual Drawing Rectangle
	int drawX0 = Max(targetX0, clipX0);
	int drawY0 = Max(targetY0, clipY0);
	int drawX1 = Min(targetX1, clipX1);
	int drawY1 = Min(targetY1, clipY1);
	int drawWidth = drawX1 - drawX0;
	int drawHeight = drawY1 - drawY0;
	int drawOffset = drawY0 * m_FrameWidth + drawX0;
	int drawOffsetDX = 1;
	int drawOffsetDY = m_FrameWidth - drawWidth;

	//Source Rectangle
	int sourceX0 = rectSource->GetX();
	int sourceY0 = rectSource->GetY();
	//int sourceX1 = rectSource->GetX() + rectSource->GetWidth();
	//int sourceY1 = rectSource->GetY() + rectSource->GetHeight();
	int sourceWidth = rectSource->GetWidth();
	int sourceHeight = rectSource->GetHeight();

	float ratioX = (float)sourceWidth / (float)targetWidth;
	float ratioY = (float)sourceHeight / (float)targetHeight;
	float diffY = (float)(drawY0 - targetY0) * ratioY;
	float diffX = (float)(drawX0 - targetX0) * ratioX;

	int textureWidth = texture->GetWidth();

	// WHEN SOURCE AND TARGET DIMENSIONS ARE THE SAME

	if (sourceWidth == drawWidth && sourceHeight == drawHeight)
	{
		uint32_t* sourcePixelData = (uint32_t*)texture->GetPixelData();

		int sourceOffset = 0 + (sourceY0 + diffY) * texture->GetWidth() + (sourceX0 + diffX);
		int sourceOffsetDX = 1;
		int sourceOffsetDY = texture->GetWidth() - drawWidth;

		//uint16_t* cpySrc = sourcePixelData + sourceOffset;
		//uint16_t* cpyDst = m_FrameBuffer + drawOffset;
		//uint16_t textureWidth = texture->GetWidth();
		//drawWidth *= 2;

		//for (int y = 0; y < drawHeight; y++, cpySrc += textureWidth, cpyDst += m_FrameWidth)
		//{
		//	memcpy(cpyDst, cpySrc, drawWidth);
		//	//std::copy(cpySrc, cpySrc + drawWidth, cpyDst);

		//	//cpySrc += texture->GetWidth();// -drawWidth;
		//	//cpyDst += m_FrameWidth;// -drawWidth;
		//}

		//return;

		for (int y = 0; y < drawHeight; y++, sourceOffset += sourceOffsetDY, drawOffset += drawOffsetDY)
		{
			for (int x = 0; x < drawWidth; x++, sourceOffset++, drawOffset++)
			{
				uint32_t pixelValue = sourcePixelData[sourceOffset];

				if (pixelValue != 0xffff00ff)
				{
					m_FrameBuffer[drawOffset] = pixelValue;
				}

				//sourceOffset ++;
				//drawOffset ++;

				//sourceOffset += sourceOffsetDX;
				//drawOffset += drawOffsetDX;
			}
			//sourceOffset += sourceOffsetDY; //sourceOffset += texture->GetWidth() - drawWidth; // Line up = textureWidth - how many pixels we draw in one line
			//drawOffset += drawOffsetDY; //drawOffset += s_FrameWidth - drawWidth; // Line up = screenWidth - how many pixels we draw in one line
		}

		return;
	}

	uint32_t* sourcePixelData = (uint32_t*)texture->GetPixelData();

	float fSourceY = (float)sourceY0 + diffY;
	for (int y = 0; y < drawHeight; y++)
	{
		float fSourceX = sourceX0 + diffX;
		for (int x = 0; x < drawWidth; x++)
		{
			int sourceOffset = (int)fSourceY * textureWidth + (int)fSourceX;

			uint32_t pixelValue = sourcePixelData[sourceOffset];

			if (pixelValue != 0xffff00ff)
			{
				m_FrameBuffer[drawOffset] = pixelValue;
			}

			fSourceX += ratioX;
			drawOffset += drawOffsetDX;
		}
		fSourceY += ratioY;
		drawOffset += drawOffsetDY; //drawOffset += s_FrameWidth - drawWidth; // Line up = screenWidth - how many pixels we draw in one line
	}
}

void RendererSoftware32Bits::ScreenDrawTriangle(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2)
{

}

void RendererSoftware32Bits::ScreenDrawLine(int x0, int y0, int x1, int y1)
{
	
}
