#include "RendererSoftware16Bits.h"
#include "AssetManager.h"

RendererSoftware16Bits::RendererSoftware16Bits(RendererOptions* rendererOptions) : Renderer(rendererOptions)
{ }

RendererSoftware16Bits::~RendererSoftware16Bits() = default;

void RendererSoftware16Bits::CreateFrameBuffer()
{
	m_FrameBufferTexture = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_RGB555, SDL_TEXTUREACCESS_STREAMING, m_FrameWidth, m_FrameHeight);

	void* pixels;
	int pitch;
	SDL_LockTexture(m_FrameBufferTexture, NULL, &pixels, &pitch);

	m_FrameBuffer = (uint16_t*)pixels;
	m_DepthBuffer = (float*)new float[m_FrameWidth * m_FrameHeight];
	m_SelectionBuffer = (short*)new short[m_FrameWidth * m_FrameHeight];

	m_CurrentFillColor = AssetManager::CreateColor(255, 255, 0, 255);
}

void RendererSoftware16Bits::BeginFrame()
{
	SDL_SetRenderDrawColor(m_Renderer, 0, 255, 0, 255);
	SDL_RenderClear(m_Renderer);
}

void RendererSoftware16Bits::PresentFrame()
{
	void* pixels;
	int pitch;

	SDL_UnlockTexture(m_FrameBufferTexture);

	SDL_RenderCopy(m_Renderer, m_FrameBufferTexture, NULL, NULL);
	SDL_RenderPresent(m_Renderer);

	SDL_LockTexture(m_FrameBufferTexture, NULL, &pixels, &pitch);

	// Clear Depth Buffer
	int offset = 0;
	for (int i = 0; i < m_FrameHeight * m_FrameWidth; i++, offset++)
	{
		m_DepthBuffer[offset] = -1000.0f;
	}
}

void* RendererSoftware16Bits::CreatePixelDataFromSurface(SDL_Surface* surface)
{
	int textureWidth = surface->w;
	int textureHeight = surface->h;
	int textureWidthInBytes = surface->pitch;// > w; //We are creating 8bit out of 24bits [sdlSurface->pitch];
	int textureBytesPerPixel = textureWidthInBytes / textureWidth;

	uint16_t* pixelData = new uint16_t[textureWidth * textureHeight];

	for (int y = 0; y < textureHeight; y++)
	{
		for (int x = 0; x < textureWidth; x++)
		{
			//uint8_t alphaValue = ((uint8_t*)sdlSurface->pixels)[y * textureWidthInBytes + x * textureBytesPerPixel];
			uint8_t redValue = ((uint8_t*)surface->pixels)[y * textureWidthInBytes + x * textureBytesPerPixel];
			uint8_t greenValue = ((uint8_t*)surface->pixels)[y * textureWidthInBytes + x * textureBytesPerPixel + 1];
			uint8_t blueValue = ((uint8_t*)surface->pixels)[y * textureWidthInBytes + x * textureBytesPerPixel + 2];

			uint16_t color16bit = 0;
			color16bit |= 1 << 15;
			color16bit |= (uint8_t)redValue >> 3 << 10;
			color16bit |= (uint8_t)greenValue >> 3 << 5;
			color16bit |= (uint8_t)blueValue >> 3 << 0;

			pixelData[y * textureWidth + x] = color16bit;
		}
	}

	return pixelData;
}

__forceinline void RendererSoftware16Bits::ScreenDrawText(std::string text, Font* font, int x, int y)
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

__forceinline void RendererSoftware16Bits::ScreenDrawTexture(Texture * texture, Rectangle * rectSource, Rectangle * rectTarget)
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
		uint16_t* sourcePixelData = (uint16_t*)texture->GetPixelData();
		
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
				uint16_t pixelValue = sourcePixelData[sourceOffset];

				if (pixelValue != 0xfc1f)
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

	uint16_t* sourcePixelData = (uint16_t*)texture->GetPixelData();

	float fSourceY = (float)sourceY0 + diffY;
	for (int y = 0; y < drawHeight; y++)
	{
		float fSourceX = sourceX0 + diffX;
		for (int x = 0; x < drawWidth; x++)
		{
			int sourceOffset = (int)fSourceY * textureWidth + (int)fSourceX;

			uint16_t pixelValue = sourcePixelData[sourceOffset];

			if (pixelValue != 0xfc1f)
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

void  RendererSoftware16Bits::ScreenDrawLine(int x0, int y0, int x1, int y1)
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

	uint16_t color = m_CurrentPenColor->GetRGB555();

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

void RendererSoftware16Bits::ScreenDrawTriangle(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2)
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

void RendererSoftware16Bits::ScreenDrawFillTriangleFlatBottom(Math::Vec4& v0, Math::Vec4& v1, Math::Vec4& v2)
{
	uint16_t color = m_CurrentFillColor->GetRGB555();

	float dy = fabs(v2.y - v0.y);

	if (dy == 0.0f)
	{
		return;
	}

	float mx1 = (v1.x - v0.x) / dy;
	float mx2 = (v2.x - v0.x) / dy;

	int offset = (int)v0.y * m_FrameWidth;

	for (float j = 0; j < dy; j++, offset += m_FrameWidth)
	{
		int x1 = v0.x + mx1 * j;
		int x2 = v0.x + mx2 * j + 1;


		for (int x = x1; x <= x2; x++)
		{
			if (offset + x < 0 || offset + x > m_FrameWidth * m_FrameHeight)
			{
				continue;
			}

			m_FrameBuffer[offset + x] = color;
		}
	}
}

void RendererSoftware16Bits::ScreenDrawFillTriangleFlatTop(Math::Vec4& v0, Math::Vec4& v1, Math::Vec4& v2)
{
	uint16_t color = m_CurrentFillColor->GetRGB555();

	float dy = fabs(v2.y - v0.y);

	if (dy == 0.0f)
	{
		return;
	}

	float mx2 = (v2.x - v0.x) / dy;
	float mx3 = (v2.x - v1.x) / dy;

	int offset = (int)v0.y * m_FrameWidth;

	for (float j = 0; j < dy; j++, offset += m_FrameWidth)
	{
		int x2 = v0.x + mx2 * j;
		int x3 = v1.x + mx3 * j + 1;

		for (int x = x2; x <= x3; x++)
		{
			if (offset + x < 0 || offset + x > m_FrameWidth * m_FrameHeight)
			{
				continue;
			}

			m_FrameBuffer[offset + x] = color;
		}
	}
}


void RendererSoftware16Bits::ScreenDrawTexturedTriangleFlatBottom(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2)
{
	int transparentColorIndex = AssetManager::CreateColor(255, 255, 0, 255)->GetIndex();
	float dy = fabs(v2.pos.y - v0.pos.y);

	if (dy == 0.0f)
	{
		return;
	}

	float textureWidth = m_CurrentTexture->GetWidth();
	float textureHeight = m_CurrentTexture->GetHeight();
	uint16_t* textureBuffer = (uint16_t*)m_CurrentTexture->GetPixelData();

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
			if (offset + x < 0 || offset + x > m_FrameWidth * m_FrameHeight)
			{
				continue;
			}

			if (z > m_DepthBuffer[offset + x])
			{
				int tx = (int)(u * textureWidth) % (int)textureWidth;
				int ty = (int)(v * textureHeight) % (int)textureHeight;

				uint16_t color = textureBuffer[(int)(ty * textureWidth + tx)];
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

void RendererSoftware16Bits::ScreenDrawTexturedTriangleFlatTop(Math::Vertex& v0, Math::Vertex& v1, Math::Vertex& v2)
{
	int transparentColorIndex = AssetManager::CreateColor(255, 255, 0, 255)->GetIndex();
	float dy = fabs(v2.pos.y - v0.pos.y);

	if (dy == 0.0f)
	{
		return;
	}

	float textureWidth = m_CurrentTexture->GetWidth();
	float textureHeight = m_CurrentTexture->GetHeight();
	uint16_t* textureBuffer = (uint16_t*)m_CurrentTexture->GetPixelData();

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
			if (offset + x < 0 || offset + x > m_FrameWidth * m_FrameHeight)
			{
				continue;
			}

			if (z > m_DepthBuffer[offset + x])
			{
				int tx = (int)(u * textureWidth) % (int)textureWidth;
				int ty = (int)(v * textureHeight) % (int)textureHeight;

				uint16_t color = textureBuffer[(int)(ty * textureWidth + tx)];

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