#include "RendererSoftware8Bits.h"
#include "AssetManager.h"

RendererSoftware8Bits::RendererSoftware8Bits(RendererOptions* rendererOptions): Renderer(rendererOptions)
{ }

RendererSoftware8Bits::~RendererSoftware8Bits() = default;

void RendererSoftware8Bits::CreateFrameBuffer()
{
	m_FrameBufferSurface = SDL_CreateRGBSurface(0, m_FrameWidth, m_FrameHeight, 8, 0, 0, 0, 0);

	SDL_Color colors[256];
	Palette* palette = AssetManager::GetDefaultPalette();

	for (int i = 0; i < 256; i++)
	{
		Color* paletteColor = palette->GetColorAtIndex(i);
		colors[i].r = paletteColor->GetRed();
		colors[i].g = paletteColor->GetGreen();
		colors[i].b = paletteColor->GetBlue();
	}

	SDL_SetPaletteColors(m_FrameBufferSurface->format->palette, colors, 0, 256);

	m_TransparentColorIndex = AssetManager::GetTransparentColor()->GetIndex();

	m_FrameBufferHelperSurface = SDL_CreateRGBSurface(0, m_FrameWidth, m_FrameHeight, 32, 0, 0, 0, 0);

	m_FrameBufferTexture = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, m_FrameWidth, m_FrameHeight);

	m_FrameBuffer = (uint8_t*)m_FrameBufferSurface->pixels;
	m_DepthBuffer = (float*)new float[m_FrameWidth * m_FrameHeight];
	m_SelectionBuffer = (short*)new short[m_FrameWidth * m_FrameHeight];
}

void RendererSoftware8Bits::BeginFrame()
{
	SDL_SetRenderDrawColor(m_Renderer, 0, 255, 0, 255);
	SDL_RenderClear(m_Renderer);

	//SDL_RenderDrawLine(m_Renderer, 0, 0, 640, 480);
	//SDL_Rect rect = SDL_Rect();
	//rect.x = 0;
	//rect.y = 0;
	//rect.w = 640;
	//rect.h = 480;
	//SDL_RenderFillRect(m_Renderer, &rect);

	// Clear Depth Buffer
	int offset = 0;
	for (int i = 0; i < m_FrameHeight * m_FrameWidth; i++, offset++)
	{
		m_DepthBuffer[offset] = -1000.0f;
	}
}

void RendererSoftware8Bits::PresentFrame()
{
	void* pixels;
	int pitch;

	SDL_BlitSurface(m_FrameBufferSurface, NULL, m_FrameBufferHelperSurface, NULL);

	SDL_LockTexture(m_FrameBufferTexture, NULL, &pixels, &pitch);
	SDL_ConvertPixels(
		m_FrameBufferHelperSurface->w,
		m_FrameBufferHelperSurface->h,
		m_FrameBufferHelperSurface->format->format,
		m_FrameBufferHelperSurface->pixels,
		m_FrameBufferHelperSurface->pitch,
		SDL_PIXELFORMAT_ARGB8888,
		pixels,
		pitch);
	SDL_UnlockTexture(m_FrameBufferTexture);

	SDL_RenderCopy(m_Renderer, m_FrameBufferTexture, NULL, NULL);
	SDL_RenderPresent(m_Renderer);
}

void* RendererSoftware8Bits::CreatePixelDataFromSurface(SDL_Surface* surface)
{
	int textureWidth = surface->w;
	int textureHeight = surface->h;
	int textureWidthInBytes = surface->pitch;// > w; //We are creating 8bit out of 24bits [sdlSurface->pitch];
	int textureBytesPerPixel = textureWidthInBytes / textureWidth;

	uint8_t* pixelData = new uint8_t[textureWidth * textureHeight];

	for (int y = 0; y < textureHeight; y++)
	{
		for (int x = 0; x < textureWidth; x++)
		{
			int redValue = ((uint8_t*)surface->pixels)[y * textureWidthInBytes + x * textureBytesPerPixel];
			int greenValue = ((uint8_t*)surface->pixels)[y * textureWidthInBytes + x * textureBytesPerPixel + 1];
			int blueValue = ((uint8_t*)surface->pixels)[y * textureWidthInBytes + x * textureBytesPerPixel + 2];

			Color color = Color(255, redValue, greenValue, blueValue);
			Color compatibleColor = Color();
			AssetManager::GetDefaultPalette()->CreateCompatibleColor(&color, &compatibleColor);

			pixelData[y * textureWidth + x] = compatibleColor.GetIndex();
		}
	}

	return pixelData;
}

__forceinline void RendererSoftware8Bits::ScreenDrawText(std::string text, Font* font, int x, int y)
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

void RendererSoftware8Bits::ScreenDrawTexture(Texture* texture, Rectangle* rectSource, Rectangle* rectTarget)
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
		uint8_t* sourcePixelData = (uint8_t*)texture->GetPixelData();
		int sourceOffset = 0 + (sourceY0 + diffY) * texture->GetWidth() + (sourceX0 + diffX);
		int sourceOffsetDX = 1;
		int sourceOffsetDY = texture->GetWidth() - drawWidth;

		for (int y = 0; y < drawHeight; y++)
		{
			for (int x = 0; x < drawWidth; x++)
			{
				uint8_t pixelValue = sourcePixelData[sourceOffset];

				if (pixelValue != m_TransparentColorIndex)
				{
					m_FrameBuffer[drawOffset] = pixelValue;
				}

				sourceOffset += sourceOffsetDX; //sourceOffset++;
				drawOffset += drawOffsetDX; //drawOffset++;
			}
			sourceOffset += sourceOffsetDY; //sourceOffset += texture->GetWidth() - drawWidth; // Line up = textureWidth - how many pixels we draw in one line
			drawOffset += drawOffsetDY; //drawOffset += s_FrameWidth - drawWidth; // Line up = screenWidth - how many pixels we draw in one line
		}

		return;
	}

	uint8_t* sourcePixelData = (uint8_t*)texture->GetPixelData();

	float fSourceY = (float)sourceY0 + diffY;
	for (int y = 0; y < drawHeight; y++)
	{
		float fSourceX = sourceX0 + diffX;
		for (int x = 0; x < drawWidth; x++)
		{
			int sourceOffset = (int)fSourceY * textureWidth + (int)fSourceX;

			uint8_t pixelValue = sourcePixelData[sourceOffset];

			if (pixelValue != m_TransparentColorIndex)
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

void RendererSoftware8Bits::ScreenDrawTriangle(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2)
{
	if (m_ClippingRectangle->IsEmpty())
	{
		return;
	}

	//Clipping Rectangle
	int clipX0 = m_ClippingRectangle->GetX();
	int clipY0 = m_ClippingRectangle->GetY();
	int clipX1 = clipX0 + m_ClippingRectangle->GetWidth();
	int clipY1 = clipY0 + m_ClippingRectangle->GetHeight();

	//TODO: Clipping

	if (v0.pos.x < clipX0 || v1.pos.x < clipX0 || v2.pos.x < clipX0 ||
		v0.pos.y < clipY0 || v1.pos.y < clipY0 || v2.pos.y < clipY0 ||
		v0.pos.x > clipX1 || v1.pos.x > clipX1 || v2.pos.x > clipX1 ||
		v0.pos.y > clipY1 || v1.pos.y > clipY1 || v2.pos.y > clipY1)
	{
		return;
	}

	//if (s_DrawMode.HasFlag(DrawMode::Points))
	//{
		//ScreenDrawLine(v0.pos.x, v0.pos.y, v0.pos.x + 1, v0.pos.y);
		//ScreenDrawLine(v1.pos.x, v1.pos.y, v1.pos.x + 1, v1.pos.y);
		//ScreenDrawLine(v2.pos.x, v2.pos.y, v2.pos.x + 1, v2.pos.y);
	//}
	//else if (s_DrawMode.HasFlag(DrawMode::Lines))
	//{
		//ScreenDrawLine(v0.pos.x, v0.pos.y, v1.pos.x, v1.pos.y);
		//ScreenDrawLine(v1.pos.x, v1.pos.y, v2.pos.x, v2.pos.y);
		//ScreenDrawLine(v2.pos.x, v2.pos.y, v0.pos.x, v0.pos.y);
	//}
	//else if (s_DrawMode.HasFlag(DrawMode::Filled) || s_DrawMode.HasFlag(DrawMode::Textured))
	//{
	ScreenDrawFillTriangle(v0, v1, v2);
	//}

	//ScreenDrawLine(v0.pos.x, v0.pos.y, v0.pos.x + 1, v0.pos.y);
	//ScreenDrawLine(v1.pos.x, v1.pos.y, v1.pos.x + 1, v1.pos.y);
	//ScreenDrawLine(v2.pos.x, v2.pos.y, v2.pos.x + 1, v2.pos.y);
}

void  RendererSoftware8Bits::ScreenDrawLine(int x0, int y0, int x1, int y1)
{
	if (m_ClippingRectangle->IsEmpty())
	{
		return;
	}

	//Clipping Rectangle
	int clipX0 = m_ClippingRectangle->GetX();
	int clipY0 = m_ClippingRectangle->GetY();
	int clipX1 = clipX0 + m_ClippingRectangle->GetWidth();
	int clipY1 = clipY0 + m_ClippingRectangle->GetHeight();

	int color = m_CurrentPenColor->GetIndex();

	int deltaX = fabs(x1 - x0);
	int deltaY = fabs(y1 - y0);
	int pixelCount;
	int d;
	int dInc1;
	int dInc2;
	int xInc1;
	int xInc2;
	int yInc1;
	int yInc2;

	//Initialize all vars based on which is the independent variable
	if (deltaX >= deltaY)
	{
		//x is independent variable
		pixelCount = deltaX;
		d = (deltaY * 2) - deltaX;;
		dInc1 = deltaY * 2;
		dInc2 = (deltaY - deltaX) * 2;
		xInc1 = 1;
		xInc2 = 1;
		yInc1 = 0;
		yInc2 = 1;
	}
	else
	{
		//y is independent variable
		pixelCount = deltaY;
		d = (deltaX * 2) - deltaY;
		dInc1 = deltaX * 2;
		dInc2 = (deltaX - deltaY) * 2;
		xInc1 = 0;
		xInc2 = 1;
		yInc1 = 1;
		yInc2 = 1;
	}

	//Make sure x and y move in the right directions
	if (x0 > x1)
	{
		xInc1 = -xInc1;
		xInc2 = -xInc2;
	}

	if (y0 > y1)
	{
		yInc1 = -yInc1;
		yInc2 = -yInc2;
	}

	//Start drawing at <x0, y0>
	int x = x0;
	int y = y0;

	//Draw the pixels
	int offset = y0 * m_FrameWidth + x0;
	int dyInc1 = m_FrameWidth * yInc1;
	int dyInc2 = m_FrameWidth * yInc2;

	for (int i = 0; i < pixelCount; i++)
	{
		if (clipX0 <= x && clipX1 > x && clipY0 <= y && clipY1 > y)
		{
			m_FrameBuffer[offset] = color;
		}

		if (d < 0)
		{
			d = d + dInc1;
			x = x + xInc1;
			y = y + yInc1;
		}
		else
		{
			d = d + dInc2;
			x = x + xInc2;
			y = y + yInc2;
		}
		offset = y * m_FrameWidth + x;
	}
}

void RendererSoftware8Bits::ScreenDrawFillTriangle(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2)
{
	Sort(v0, v1, v2);

	float dy1 = fabs(v1.pos.y - v0.pos.y);
	float dy2 = fabs(v2.pos.y - v0.pos.y);

	if (dy2 == 0.0f)
	{
		return;
	}

	float mx = (v2.pos.x - v0.pos.x) / dy2;
	float mz = (v2.pos.z - v0.pos.z) / dy2;
	float mu = (v2.uv.x - v0.uv.x) / dy2;
	float mv = (v2.uv.y - v0.uv.y) / dy2;

	Math::Vertex vm = Math::Vertex();
	vm.objectId = v0.objectId;
	vm.pos.x = v0.pos.x + mx * dy1;
	vm.pos.y = v1.pos.y;
	vm.pos.z = v0.pos.z + mz * dy1;
	vm.uv.x = v0.uv.x + mu * dy1;
	vm.uv.y = v0.uv.y + mv * dy1;

	if (v1.pos.x < vm.pos.x)
	{
		Swap(v1, vm);
	}

	//ScreenDrawFillTriangleFlatBottom(v0.pos, vm.pos, v1.pos);
	//ScreenDrawFillTriangleFlatTop(vm.pos, v1.pos, v2.pos);

	ScreenDrawTexturedTriangleFlatBottom(v0, vm, v1);
	ScreenDrawTexturedTriangleFlatTop(vm, v1, v2);
}

void RendererSoftware8Bits::ScreenDrawFillTriangleFlatBottom(Math::Vec4& v0, Math::Vec4& v1, Math::Vec4& v2)
{
	int colorIndex = m_CurrentFillColor->GetIndex();

	float dy = fabs(v2.y - v0.y);

	if (dy == 0.0f)
	{
		return;
	}

	float mx1 = (v1.x - v0.x) / dy;
	float mx2 = (v2.x - v0.x) / dy;

	int offset = (int) v0.y * m_FrameWidth;
	uint8_t* cpyDst = m_FrameBuffer + offset;

	for (float j = 0; j < dy; j++, cpyDst += m_FrameWidth)
	{
		int x1 = v0.x + mx1 * j;
		int x2 = v0.x + mx2 * j + 1;

		memset(cpyDst + x1, colorIndex, x2 - x1);
	}
}

void RendererSoftware8Bits::ScreenDrawFillTriangleFlatTop(Math::Vec4& v0, Math::Vec4& v1, Math::Vec4& v2)
{
	int colorIndex = m_CurrentFillColor->GetIndex();

	float dy = fabs(v2.y - v0.y);

	if (dy == 0.0f)
	{
		return;
	}

	float mx2 = (v2.x - v0.x) / dy;
	float mx3 = (v2.x - v1.x) / dy;

	int offset = (int)v0.y * m_FrameWidth;
	uint8_t* cpyDst = m_FrameBuffer + offset;

	for (float j = 0; j < dy; j++, cpyDst += m_FrameWidth)
	{
		int x2 = v0.x + mx2 * j;
		int x3 = v1.x + mx3 * j + 1;

		memset(cpyDst + x2, colorIndex, x3 - x2);
	}
}


void RendererSoftware8Bits::ScreenDrawTexturedTriangleFlatBottom(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2)
{
	int transparentColorIndex = AssetManager::CreateColor(255, 255, 0, 255)->GetIndex();
	float dy = fabs(v2.pos.y - v0.pos.y);

	if (dy == 0.0f)
	{
		return;
	}

	float textureWidth = m_CurrentTexture->GetWidth();
	float textureHeight = m_CurrentTexture->GetHeight();
	uint8_t* textureBuffer = (uint8_t*) m_CurrentTexture->GetPixelData();

	float mx1 = (v1.pos.x - v0.pos.x) / dy;
	float mx2 = (v2.pos.x - v0.pos.x) / dy;

	float mz1 = (v1.pos.z - v0.pos.z) / dy;
	float mz2 = (v2.pos.z - v0.pos.z) / dy;

	float mu1 = (v1.uv.x - v0.uv.x) / dy;
	float mu2 = (v2.uv.x - v0.uv.x) / dy;

	float mv1 = (v1.uv.y - v0.uv.y) / dy;
	float mv2 = (v2.uv.y - v0.uv.y) / dy;

	int offset = (int)v0.pos.y * m_FrameWidth;
	for (int j = 0; j < dy; j++, offset += m_FrameWidth)
	{
		int x1 = v0.pos.x + mx1 * (float)j;
		int x2 = v0.pos.x + mx2 * (float)j;

		float z1 = v0.pos.z + mz1 * (float)j;
		float z2 = v0.pos.z + mz2 * (float)j;

		float u1 = v0.uv.x + mu1 * (float)j;
		float u2 = v0.uv.x + mu2 * (float)j;

		float v1 = v0.uv.y + mv1 * (float)j;
		float v2 = v0.uv.y + mv2 * (float)j;

		float z = z1;
		float dz = (z2 - z1) / (x2 - x1);

		float u = u1;
		float du = (u2 - u1) / (x2 - x1);

		float v = v1;
		float dv = (v2 - v1) / (x2 - x1);

		for (int x = x1; x <= x2; x++, z += dz, u += du, v += dv)
		{
			if (z > m_DepthBuffer[offset + x])
			{
				int tx = (int)(u * textureWidth) % (int)textureWidth;
				int ty = (int)(v * textureHeight) % (int)textureHeight;

				uint8_t color = textureBuffer[(int)(ty * textureWidth + tx)];
				if (color != transparentColorIndex)
				{
					m_DepthBuffer[offset + x] = z;
					m_FrameBuffer[offset + x] = color;
					//s_SelectionBuffer[offset + x] = v0.objectId;
				}
			}
		}
	}
}

void RendererSoftware8Bits::ScreenDrawTexturedTriangleFlatTop(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2)
{
	int transparentColorIndex = AssetManager::CreateColor(255, 255, 0, 255)->GetIndex();
	float dy = fabs(v2.pos.y - v0.pos.y);

	if (dy == 0.0f)
	{
		return;
	}

	float textureWidth = m_CurrentTexture->GetWidth();
	float textureHeight = m_CurrentTexture->GetHeight();
	uint8_t* textureBuffer = (uint8_t*) m_CurrentTexture->GetPixelData();

	float mx2 = (v2.pos.x - v0.pos.x) / dy;
	float mx3 = (v2.pos.x - v1.pos.x) / dy;

	float mz2 = (v2.pos.z - v0.pos.z) / dy;
	float mz3 = (v2.pos.z - v1.pos.z) / dy;

	float mu2 = (v2.uv.x - v0.uv.x) / dy;
	float mu3 = (v2.uv.x - v1.uv.x) / dy;

	float mv2 = (v2.uv.y - v0.uv.y) / dy;
	float mv3 = (v2.uv.y - v1.uv.y) / dy;

	int offset = (int)v0.pos.y * m_FrameWidth;
	for (int j = 0; j < dy; j++, offset += m_FrameWidth)
	{
		int x2 = v0.pos.x + mx2 * (float)j;
		int x3 = v1.pos.x + mx3 * (float)j;

		float z2 = v0.pos.z + mz2 * (float)j;
		float z3 = v1.pos.z + mz3 * (float)j;

		float u2 = v0.uv.x + mu2 * (float)j;
		float u3 = v1.uv.x + mu3 * (float)j;

		float v2 = v0.uv.y + mv2 * (float)j;
		float v3 = v1.uv.y + mv3 * (float)j;

		float z = z2;
		float dz = (z3 - z2) / (x3 - x2);

		float u = u2;
		float du = (u3 - u2) / (x3 - x2);

		float v = v2;
		float dv = (v3 - v2) / (x3 - x2);

		for (int x = x2; x <= x3; x++, z += dz, u += du, v += dv)
		{
			if (z > m_DepthBuffer[offset + x])
			{
				int tx = (int)(u * textureWidth) % (int)textureWidth;
				int ty = (int)(v * textureHeight) % (int)textureHeight;

				uint8_t color = textureBuffer[(int)(ty * textureWidth + tx)];

				if (color != transparentColorIndex)
				{
					m_DepthBuffer[offset + x] = z;
					m_FrameBuffer[offset + x] = color;
					//m_SelectionBuffer[offset + x] = v0.objectId;
				}
			}
		}
	}
}