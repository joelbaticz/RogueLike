#include "RenderingEngine.h"
#include "GameEngine.h"

std::string			RenderingEngine::s_ComponentName;
SDL_Window*			RenderingEngine::s_Window;
SDL_Renderer*		RenderingEngine::s_Renderer;
Color*				RenderingEngine::s_CurrentPenColor;
Color*				RenderingEngine::s_CurrentFillColor;
Rectangle*			RenderingEngine::s_ClippingRectangle;
SDL_Texture*		RenderingEngine::s_FrameBufferTexture;
uint8_t*			RenderingEngine::s_FrameBuffer;
SDL_Surface*		RenderingEngine::s_FrameBufferSurface;
SDL_Surface*		RenderingEngine::s_FrameBufferHelperSurface;
int					RenderingEngine::s_FrameX;
int					RenderingEngine::s_FrameY;
int					RenderingEngine::s_FrameWidth;
int					RenderingEngine::s_FrameHeight;
bool				RenderingEngine::s_WindowIsShown;


static int s_ColorOffset = 0;
static int s_ColorOffsetDelta = 1;

//Hidden Constructor - won't be called - since it's static (no instantiation)
RenderingEngine::RenderingEngine()
{
	LogEngine::Log(LOG_TRACE, s_ComponentName, "Constructor called.");
}

//Hidden Destructor
RenderingEngine::~RenderingEngine()
{
	LogEngine::Log(LOG_TRACE, s_ComponentName, "Destructor called.");
}

int RenderingEngine::Init(std::string windowTitle, int windowX, int windowY, int windowWidth, int windowHeight)
{
	s_ComponentName = "RenderingEngine";
	s_Window = nullptr;
	s_Renderer = nullptr;
	s_CurrentFillColor = nullptr;
	s_CurrentPenColor = nullptr;
	s_FrameBufferTexture = nullptr;
	s_FrameX = windowX;
	s_FrameY = windowY;
	s_FrameWidth = windowWidth;
	s_FrameHeight = windowHeight;
	//s_FrameBuffer = new uint8_t[width * height];

	LogEngine::Log(LOG_TRACE, s_ComponentName, "Init() called.");

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		LogEngine::Log(LOG_ERROR, s_ComponentName, SDL_GetError());
		return 1;
	}
	LogEngine::Log(LOG_TRACE, s_ComponentName, "SDL_Init...OK");

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		LogEngine::Log(LOG_ERROR, s_ComponentName, SDL_GetError());
		return 1;
	}
	LogEngine::Log(LOG_TRACE, s_ComponentName, "SDL_Image...OK");

	if (TTF_Init() != 0)
	{
		LogEngine::Log(LOG_ERROR, s_ComponentName, SDL_GetError());
		return 1;
	}
	LogEngine::Log(LOG_TRACE, s_ComponentName, "SDL_Ttf...OK");

	s_Window = SDL_CreateWindow("Hello World!", windowX, windowY, windowWidth, windowHeight, SDL_WINDOW_HIDDEN);
	//   SDL_WINDOW_SHOWN
	//   SDL_WINDOW_HIDDEN
	// | SDL_WINDOW_BORDERLESS
	// | SDL_WINDOW_FULLSCREEN	
	
	if (s_Window == nullptr)
	{
		LogEngine::Log(LOG_ERROR, s_ComponentName, SDL_GetError());
		return 1;
	}
	LogEngine::Log(LOG_TRACE, s_ComponentName, "Creating window...OK");

	s_Renderer = SDL_CreateRenderer(s_Window, -1, SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_ACCELERATED | SDL_WINDOW_OPENGL);
	// | SDL_RENDERER_SOFTWARE
	// | SDL_RENDERER_ACCELERATED
	// | SDL_RENDERER_PRESENTVSYNC
	// | SDL_WINDOW_OPENGL
	// | SDL_WINDOW_VULKAN

	if (s_Renderer == nullptr)
	{
		LogEngine::Log(LOG_ERROR, s_ComponentName, SDL_GetError());
		return 1;
	}

	LogEngine::Log(LOG_TRACE, s_ComponentName, "Creating renderer...OK");

	ClearScreen();
	
	LogEngine::Log(LOG_TRACE, s_ComponentName, "Setting background color...OK");
	
	s_CurrentPenColor = AssetManager::CreateColor(255, 192, 192, 192);
	s_CurrentFillColor = AssetManager::CreateColor(255, 128, 128, 128);
	
	LogEngine::Log(LOG_TRACE, s_ComponentName, "Creating default colors...OK.");

	CreateFrameBuffer();

	if (s_FrameBufferSurface == nullptr)
	{
		LogEngine::Log(LOG_ERROR, s_ComponentName, SDL_GetError());
		return 1;
	}

	s_FrameBuffer = (uint8_t*)s_FrameBufferSurface->pixels;

	LogEngine::Log(LOG_TRACE, s_ComponentName, "Creating Frame Buffer...OK.");


	LogEngine::Log(LOG_TRACE, s_ComponentName, "Init()...OK.");
	return 0;
}

void RenderingEngine::ClearScreen()
{
	SDL_SetRenderDrawColor(s_Renderer, 0, 0, 0, 255);
	SDL_RenderClear(s_Renderer);
	SDL_RenderPresent(s_Renderer);
}

void RenderingEngine::ShowWindow(bool isShow)
{
	if (isShow)
	{
		SDL_ShowWindow(s_Window);
		s_WindowIsShown = true;
	}
	else
	{
		SDL_HideWindow(s_Window);
		s_WindowIsShown = false;
	}
}

void RenderingEngine::CreateFrameBuffer()
{
	//frameBufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8, SDL_TEXTUREACCESS_STREAMING, width, height);

	//frameBufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	s_FrameBufferSurface = SDL_CreateRGBSurface(0, s_FrameWidth, s_FrameHeight, 8, 0, 0, 0, 0);
	
	SDL_Color colors[256];

	//int i;
	//for (i = 0; i < 256; i++)
	//{
	//	colors[i].r = colors[i].g = colors[i].b = (Uint8)i;
	//}

	uint8_t redvalues[] = { 0x00, 0x24, 0x49, 0x6D, 0x92, 0xB6, 0xDB, 0xFF };
	uint8_t greenvalues[] = { 0x00, 0x24, 0x49, 0x6D, 0x92, 0xB6, 0xDB, 0xFF };
	uint8_t bluevalues[] = { 0x00, 0x55, 0xAA, 0xFF };

	size_t i = 0;
	for(uint8_t red : redvalues)
	{
		for (uint8_t green : greenvalues)
		{
			for (uint8_t blue : bluevalues)
			{
				colors[i].r = red;
				colors[i].g = green;
				colors[i].b = blue;
				i++;
			}
		}

		//colors[i].r = colors[i].g = colors[i].b = (Uint8)i;
	}

	SDL_SetPaletteColors(s_FrameBufferSurface->format->palette, colors, 0, 256);

	s_FrameBufferHelperSurface = SDL_CreateRGBSurface(0, s_FrameWidth, s_FrameHeight, 32, 0, 0, 0, 0);
	s_FrameBufferTexture = SDL_CreateTexture(s_Renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, s_FrameWidth, s_FrameHeight);
}

void RenderingEngine::SetPenColor(Color* color)
{
	s_CurrentPenColor = color;
}

void RenderingEngine::SetFillColor(Color* color)
{
	s_CurrentFillColor = color;
}

void RenderingEngine::BeginFrame()
{
	SDL_SetRenderDrawColor(s_Renderer, 0, 0, 0, 255);
	SDL_RenderClear(s_Renderer);

	memset(s_FrameBufferSurface->pixels, 255, s_FrameWidth * s_FrameHeight);

	//int offset = 0;

	//for (int y = 0; y < frameHeight; y++)
	//{
	//	for (int x = 0; x < frameWidth; x++)
	//	{
	//		frameBuffer[offset] = (x + colorOffset) >> 3;
	//		offset++;
	//	}
	//}

	//colorOffset += colorOffsetDelta;
	//if (colorOffset > 1000) colorOffsetDelta=-colorOffsetDelta;
	//if (colorOffset < 0) colorOffsetDelta = -colorOffsetDelta;

}

void RenderingEngine::PresentFrame()
{
	if (!s_WindowIsShown)
	{
		ShowWindow(true);
	}

	void *pixels;
	int pitch;

	SDL_BlitSurface(s_FrameBufferSurface, NULL, s_FrameBufferHelperSurface, NULL);

	SDL_LockTexture(s_FrameBufferTexture, NULL, &pixels, &pitch);
	SDL_ConvertPixels(
		s_FrameBufferHelperSurface->w,
		s_FrameBufferHelperSurface->h,
		s_FrameBufferHelperSurface->format->format,
		s_FrameBufferHelperSurface->pixels,
		s_FrameBufferHelperSurface->pitch,
		SDL_PIXELFORMAT_ARGB8888,
		pixels,
		pitch);
	SDL_UnlockTexture(s_FrameBufferTexture);

	SDL_RenderCopy(s_Renderer, s_FrameBufferTexture, NULL, NULL);
	SDL_RenderPresent(s_Renderer);
}

SDL_Renderer* RenderingEngine::GetRenderer()
{
	return s_Renderer;
}

void RenderingEngine::UnInit()
{
	if (s_Renderer != nullptr)
	{
		SDL_DestroyRenderer(s_Renderer);
	}

	if (s_Window != nullptr)
	{
		SDL_DestroyWindow(s_Window);
	}

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void RenderingEngine::SetWindowFullScreen()
{
	//SDL_SetWindowFullscreen(s_Window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	SDL_SetWindowPosition(s_Window, 0, 0);
}

void RenderingEngine::SetClippingRectangle(Rectangle* rect)
{
	if (s_ClippingRectangle != nullptr)
	{
		delete s_ClippingRectangle;
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

	if (clipX0 > s_FrameWidth)
	{
		clipX0 = s_FrameWidth;
	}

	if (clipX1 > s_FrameWidth)
	{
		clipX1 = s_FrameWidth;
	}

	if (clipY0 < 0)
	{
		clipY0 = 0;
	}

	if (clipY1 < 0)
	{
		clipY1 = 0;
	}

	if (clipY0 > s_FrameHeight)
	{
		clipY0 = s_FrameHeight;
	}

	if (clipY1 > s_FrameHeight)
	{
		clipY1 = s_FrameHeight;
	}

	/*if (clipX + clipW > s_FrameWidth)
	{
		clipW -= clipX + clipW - s_FrameWidth;
	}
*/
		
	s_ClippingRectangle = new Rectangle(clipX0, clipY0, clipX1 - clipX0, clipY1 - clipY0);
}

Rectangle* RenderingEngine::GetClippingRectangle()
{
	return s_ClippingRectangle;
}

Rectangle* RenderingEngine::ClipToParentRectangle(Node* node, Rectangle* rectResult)
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
			int cNodeX = cNode->GetLocation()->GetX();
			int cNodeY = cNode->GetLocation()->GetY();
			int cNodeW = cNode->GetSize()->GetWidth();
			int cNodeH = cNode->GetSize()->GetHeight();

			rectResult->SetX(rectResult->GetX() + cNodeX);
			rectResult->SetY(rectResult->GetY() + cNodeY);

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


int Max(int value1, int value2)
{
	if (value1 > value2)
	{
		return value1;
	}

	return value2;
}

int Min(int value1, int value2)
{
	if (value1 < value2)
	{
		return value1;
	}

	return value2;
}

void Swap(int& value1, int& value2)
{
	int temp = value1;
	value1 = value2;
	value2 = temp;
}

void RenderingEngine::ScreenDrawLine(int x0, int y0, int x1, int y1)
{
	if (s_ClippingRectangle->IsEmpty())
	{
		return;
	}

	//Clipping Rectangle
	int clipX0 = s_ClippingRectangle->GetX();
	int clipY0 = s_ClippingRectangle->GetY();
	int clipX1 = clipX0 + s_ClippingRectangle->GetWidth();
	int clipY1 = clipY0 + s_ClippingRectangle->GetHeight();

	int colorIndex = s_CurrentPenColor->GetIndex();
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
		//numpixels=deltay + 1;
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

	//for (int i=1;i<numpixels;i++)

	int offset = y0 * s_FrameWidth + x0;
	int dyInc1 = s_FrameWidth * yInc1;
	int dyInc2 = s_FrameWidth * yInc2;


	for (int i = 0; i < pixelCount; i++)
	{
		//if ((y>=0) && (y<=itmapBufferHeight))
		//and (x>=0) and (x<=BitmapBufferWidth) then
		//begin
		//  BitmapBufferBits[(y)*(BitmapBufferWidthByte)+(x)]:=BitmapBufferColor;
		//end;
		//painter->drawPoint(x,y);
		//myImage.setPixel(x,y,qRgb(255,0,255));

		//int index=y*frameBufferScanLine+x*frameBufferOffset;
		//int index=y*frameBufferScanLine+x;

		//(*backBuffer)[index]=penColor;

		if (clipX0 <= x && clipX1 > x && clipY0 <= y && clipY1 > y)
		{
			s_FrameBuffer[offset] = colorIndex;
		}

		//frameBuffer2[index] = penColor;

		//frameBuffer[index]=penColor;//0xFF00FF00; //ARGB
		//frameBuffer[y*frameBufferScanLine+x]=0xFF00FF00; //ARGB

		//frameBuffer[index+1]=0;
		//frameBuffer[index+2]=0;

		//frameBuffer[y*frameBufferScanLine+x*4]=0;
		//frameBuffer[y*frameBufferScanLine+x*4+1]=0;
		//frameBuffer[y*frameBufferScanLine+x*4+2]=0;

		if (d < 0)
		{
			d = d + dInc1;
			x = x + xInc1;
			y = y + yInc1;
			//index=index+dyinc1+xinc1;

		}
		else
		{
			d = d + dInc2;
			x = x + xInc2;
			y = y + yInc2;
			//index=index+dyinc2+xinc2;
		}
		offset = y * s_FrameWidth + x;
	}
	/*
			penPosX = x;
			penPosY = y;

	*/
}

void RenderingEngine::ScreenDrawRectangle(int x0, int y0, int x1, int y1)
{
	if (s_ClippingRectangle->IsEmpty())
	{
		return;
	}

	ScreenDrawLine(x0, y0, x1, y0);
	ScreenDrawLine(x0, y1, x1, y1);
	ScreenDrawLine(x0, y0, x0, y1);
	ScreenDrawLine(x1, y0, x1, y1);
}

void RenderingEngine::ScreenDrawFilledRectangle(int x0, int y0, int x1, int y1)
{
	if (s_ClippingRectangle->IsEmpty())
	{
		return;
	}

	//Clipping Rectangle
	int clipX0 = s_ClippingRectangle->GetX();
	int clipY0 = s_ClippingRectangle->GetY();
	int clipX1 = clipX0 + s_ClippingRectangle->GetWidth();
	int clipY1 = clipY0 + s_ClippingRectangle->GetHeight();

	//Actual Drawing Rectangle
	int drawX0 = Max(x0, clipX0);
	int drawY0 = Max(y0, clipY0);
	int drawX1 = Min(x1, clipX1);
	int drawY1 = Min(y1, clipY1);
	int drawWidth = drawX1 - drawX0;
	int drawHeight = drawY1 - drawY0;

	int drawOffset = drawY0 * s_FrameWidth + drawX0;

	int colorIndex = s_CurrentFillColor->GetIndex();

	/*
	for (int y = drawY0; y < drawY1; y++)
	{
		for (int x = drawX0; x < drawX1; x++)
		{
			s_FrameBuffer[drawOffset] = colorIndex;
			drawOffset++;
		}
		drawOffset += s_FrameWidth - drawWidth;
	}
	*/

	uint8_t* cpyDst = s_FrameBuffer + drawOffset;

	for (int y = 0; y < drawHeight; y++)
	{
		memset(cpyDst, colorIndex, drawWidth);
		cpyDst += s_FrameWidth;// -drawWidth;
	}

}

void RenderingEngine::ScreenDrawText(std::string text, Font* font, int x, int y)
{
	if (s_ClippingRectangle->IsEmpty())
	{
		return;
	}
}


//sourceRect - where we grab the pixels from(in texture coordinates)
//equals the whole texture if none given
//targetRect - where we want to render(in screen coords)
//clipRect - the clipping rect(in screen coords)
//drawRect - the intersection of the target and clip(in screen coords)

void RenderingEngine::ScreenDrawTexture(Texture* texture, int x0, int y0)
{
	if (s_ClippingRectangle->IsEmpty())
	{
		return;
	}

	//Target Rectangle
	int targetX0 = x0;
	int targetY0 = y0;
	int targetX1 = targetX0 + texture->GetWidth();
	int targetY1 = targetY0 + texture->GetHeight();

	//Clipping Rectangle
	int clipX0 = s_ClippingRectangle->GetX();
	int clipY0 = s_ClippingRectangle->GetY();
	int clipX1 = clipX0 + s_ClippingRectangle->GetWidth();
	int clipY1 = clipY0 + s_ClippingRectangle->GetHeight();

	if (targetX0 > clipX1 || targetX1 < clipX0 || targetY0 > clipY1 || targetY1 < clipY0)
	{
		return;
	}

	//Limit to actual Drawing Rectangle
	int drawX0 = Max(targetX0, clipX0);
	int drawY0 = Max(targetY0, clipY0);
	int drawX1 = Min(targetX1, clipX1);
	int drawY1 = Min(targetY1, clipY1);
	int drawWidth  = drawX1 - drawX0;
	int drawHeight = drawY1 - drawY0;
	int drawOffset = drawY0 * s_FrameWidth + drawX0;
	int drawOffsetDX = 1;
	int drawOffsetDY = s_FrameWidth - drawWidth;

	//Source Rectangle
	//int sourceX0 = 0;
	//int sourceY0 = 0;
	//int sourceX1 = texture->GetWidth();
	//int sourceY1 = texture->GetHeight();
	//int sourceWidth = texture->GetWidth();
	//int sourceHeight = texture->GetHeight();
	int sourceOffset = 0 + (drawY0 - targetY0) * texture->GetWidth() + (drawX0 - targetX0);
	int sourceOffsetDX = 1;
	int sourceOffsetDY = texture->GetWidth() - drawWidth;

	int textureWidth = texture->GetWidth();
	
	uint8_t* sourcePixelData = (uint8_t*)texture->GetPixelData();
	
	//for (int y = 0; y < drawHeight; y++)
	//{
	//	for (int x = 0; x < drawWidth; x++)
	//	{
	//		s_FrameBuffer[drawOffset] = sourcePixelData[sourceOffset];
	//		sourceOffset += sourceOffsetDX; //sourceOffset++;
	//		drawOffset += drawOffsetDX; //drawOffset++;
	//	}
	//	sourceOffset += sourceOffsetDY; //sourceOffset += texture->GetWidth() - drawWidth; // Line up = textureWidth - how many pixels we draw in one line
	//	drawOffset += drawOffsetDY; //drawOffset += s_FrameWidth - drawWidth; // Line up = screenWidth - how many pixels we draw in one line
	//}

	//return;

	uint8_t* cpySrc = sourcePixelData + sourceOffset;
	uint8_t* cpyDst = s_FrameBuffer + drawOffset;

	for (int y = 0; y < drawHeight; y++)
	{
		memcpy(cpyDst, cpySrc, drawWidth);
		cpySrc += texture->GetWidth();// -drawWidth;
		cpyDst += s_FrameWidth;// -drawWidth;
	}

}

void RenderingEngine::ScreenDrawTexture(Texture* texture, Rectangle* rectSource, Rectangle* rectTarget)
{
	if (s_ClippingRectangle->IsEmpty())
	{
		return;
	}

	//Target Rectangle
	int targetX0 = rectTarget->GetX();
	int targetY0 = rectTarget->GetY();
	int targetX1 = targetX0 + rectTarget->GetWidth();
	int targetY1 = targetY0 + rectTarget->GetHeight();
	int targetWidth = rectTarget->GetWidth();
	int targetHeight = rectTarget->GetHeight();

	//Clipping Rectangle
	int clipX0 = s_ClippingRectangle->GetX();
	int clipY0 = s_ClippingRectangle->GetY();
	int clipX1 = clipX0 + s_ClippingRectangle->GetWidth();
	int clipY1 = clipY0 + s_ClippingRectangle->GetHeight();

	//Actual Drawing Rectangle
	int drawX0 = Max(targetX0, clipX0);
	int drawY0 = Max(targetY0, clipY0);
	int drawX1 = Min(targetX1, clipX1);
	int drawY1 = Min(targetY1, clipY1);
	int drawWidth = drawX1 - drawX0;
	int drawHeight = drawY1 - drawY0;
	int drawOffset = drawY0 * s_FrameWidth + drawX0;
	int drawOffsetDX = 1;
	int drawOffsetDY = s_FrameWidth - drawWidth;

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

	uint8_t* sourcePixelData = (uint8_t*)texture->GetPixelData();

	float fSourceY = (float)sourceY0 + diffY;
	for (int y = 0; y < drawHeight; y++)
	{
		float fSourceX = sourceX0 + diffX;
		for (int x = 0; x < drawWidth; x++)
		{
			int sourceOffset = (int)fSourceY * textureWidth + (int)fSourceX;

			uint8_t pixelValue = sourcePixelData[sourceOffset];

			if (pixelValue != 227)
			{
				s_FrameBuffer[drawOffset] = pixelValue;
			}

			fSourceX += ratioX;
			drawOffset += drawOffsetDX;
		}
		fSourceY += ratioY;
		drawOffset += drawOffsetDY; //drawOffset += s_FrameWidth - drawWidth; // Line up = screenWidth - how many pixels we draw in one line
	}
}





void RenderingEngine::DrawFilledRectangle(Node* node, int x, int y, int w, int h)
{
	Rectangle rectangle = Rectangle(x, y, w, h);
	Rectangle* pRectangle = &rectangle;
	pRectangle = ClipToParentRectangle(node, pRectangle);

	if (pRectangle->GetWidth() != 0 && pRectangle->GetHeight() != 0)
	{	
		int offset = pRectangle->GetY() * s_FrameWidth + pRectangle->GetX();
		int rectWidth = pRectangle->GetWidth();
		int rectHeight = pRectangle->GetHeight();
		int colorIndex = s_CurrentFillColor->GetIndex();

		for (int y = 0; y < rectHeight; y++)
		{
			for (int x = 0; x < rectWidth; x++)
			{
				s_FrameBuffer[offset] = colorIndex;
				offset++;
			}
			offset += s_FrameWidth - rectWidth;
		}
	}
}

void RenderingEngine::DrawText(Node* node, std::string text, Font* font, int x, int y)
{
	return;

	SDL_Surface* surface = nullptr;
	//surface = TTF_RenderText_Solid(font->m_TTF_Font, text.c_str(), *colorForeground);
	//surface = TTF_RenderText_Shaded(font->m_TTF_Font, text.c_str(), *colorForeground, *colorBackground);
//	SDL_Color* sdlColor = currentPenColor->sdlColor;


//	surface = TTF_RenderText_Solid(font->GetTTFFont(), text.c_str(), *sdlColor);

	if (surface == nullptr)
	{
		LogEngine::Log(LOG_ERROR, s_ComponentName, "TTF_RenderText_Solid() ERROR.");
		return;
	}

	SDL_Texture* drawableTexture = SDL_CreateTextureFromSurface(s_Renderer, surface);
	
	SDL_Rect* rectTarget = new SDL_Rect();
	rectTarget->x = x;
	rectTarget->y = y;
	rectTarget->w = surface->w;
	rectTarget->h = surface->h;
	//rectTarget = ClientRectToScreenRect(node, rectTarget);

	SDL_Rect* rectSource = new SDL_Rect();
	rectSource->x = 0;
	rectSource->y = 0;
	rectSource->w = rectTarget->w;
	rectSource->h = rectTarget->h;

	//SDL_SetRenderDrawColor(renderer, currentFillColor->m_SDL_Color->r, currentFillColor->m_SDL_Color->g, currentFillColor->m_SDL_Color->b, currentFillColor->m_SDL_Color->a);
	//SDL_RenderFillRect(renderer, rectTarget);

	if (rectTarget->w != 0 && rectTarget->h != 0)
	{
		SDL_RenderCopy(s_Renderer, drawableTexture, rectSource, rectTarget);
	}
	
	delete rectTarget;
	delete rectSource;
//	delete texture;
	SDL_DestroyTexture(drawableTexture);
	SDL_FreeSurface(surface);
}

void RenderingEngine::DrawTexture(Texture* texture, int x, int y)
{
	return;
	
	//THERE IS ANOTHER DRAWTEXTURE WHICH SPRITENODE IS USING!!!

//	SDL_Texture* drawableTexture = texture->GetTexture();

	SDL_Rect* rectTarget = new SDL_Rect();
	rectTarget->x = x;
	rectTarget->y = y;
	rectTarget->w = texture->GetWidth();
	rectTarget->h = texture->GetHeight();
	//rectTarget = ClientRectToScreenRect(node->GetParent(), rectTarget);

	SDL_Rect* rectSource = new SDL_Rect();
	rectSource->x = 0;
	rectSource->y = 0;
	rectSource->w = rectTarget->w;
	rectSource->h = rectTarget->h;

	//SDL_SetRenderDrawColor(renderer, currentFillColor->m_SDL_Color->r, currentFillColor->m_SDL_Color->g, currentFillColor->m_SDL_Color->b, currentFillColor->m_SDL_Color->a);
	//SDL_RenderFillRect(renderer, rectTarget);

	if (rectTarget->w != 0 && rectTarget->h != 0)
	{
		//SDL_SetTextureAlphaMod(drawableTexture, 128);
//		SDL_SetTextureColorMod(drawableTexture, 255, 0, 0);
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
//		SDL_RenderCopy(renderer, drawableTexture, rectSource, rectTarget);
	}

	delete rectTarget;
	delete rectSource;
	//Do not delete the sdl texture - it belongs to the TextureImage
	//	delete texture;
	//SDL_DestroyTexture(texture);
}

void RenderingEngine::DrawTexture(Node* node, Texture* texture, SDL_Rect* rectSource, SDL_Rect* rectTarget)
{
	uint8_t* sourcePixelData = (uint8_t*)texture->GetPixelData();

	Rectangle rectClipping = Rectangle(rectTarget->x, rectTarget->y, rectTarget->w, rectTarget->h);
	Rectangle* pRectClipping = &rectClipping;
	pRectClipping = ClipToParentRectangle(node->GetParent(), pRectClipping);

	//Rectangle* rectClipping = GetClippingRectangle();

	if (!pRectClipping->IsEmpty())
	//if (rectT.GetWidth() != 0 && rectT.GetHeight() != 0)
	{
		//3 rectangles are at play:
		//Source
		//Target
		//ClippedTarget (adjusted to parent's screen area) 


		int targetX = pRectClipping->GetX();
		int targetY = pRectClipping->GetY();
		int targetWidth = pRectClipping->GetWidth();
		int targetHeight = pRectClipping->GetHeight();
		int offset = targetY * s_FrameWidth + targetX;

		int sourceX = rectSource->x;
		int sourceY = rectSource->y;
		int sourceWidth = rectSource->w;
		int sourceHeight = rectSource->h;
		int sourceOffset = 0;
		//float sourceOffset = (float)(rectSource->y * texture->GetWidth() + rectSource->x);
		
		float ratioX = (float)sourceWidth / (float)rectTarget->w;//targetWidth;
		float ratioY = (float)sourceHeight / (float)rectTarget->h;//targetHeight;

		float textureWidth = (float)texture->GetWidth();
		float sourceyf = sourceY * textureWidth;

		int dOffset = s_FrameWidth - targetWidth;

		for (int y = 0; y < targetHeight; y++)
		{
			float sourcexf = sourceX;
			for (int x = 0; x < targetWidth; x++)
			{
				//int dy = (int)((float)y * ratioY);
				//int dx = (int)((float)x * ratioX);
				//int sourceOffset = ((sourceY + dy) * texture->GetWidth()) + sourceX + dx;

				//int sourceOffset = ((sourceY + (int)dyf) * texture->GetWidth()) + sourceX + (int)dxf;

				sourceOffset = (int)sourceyf + (int)sourcexf;

				s_FrameBuffer[offset] = sourcePixelData[sourceOffset];
				offset++;

				sourcexf += ratioX;

			}
			offset += dOffset;

			//sourceyf += ystuff;
			sourceyf = (int)(sourceY + y* ratioY) * textureWidth;
		}



		//float dyf = 0;
		//float dxf = 0;
		//int sourceOffset = (sourceY * texture->GetWidth()) + sourceX;

		//for (int y = 0; y < rectHeight; y++)
		//{
		//	dxf = 0;
		//	for (int x = 0; x < rectWidth; x++)
		//	{
		//		//int dy = (int)((float)y * ratioY);
		//		//int dx = (int)((float)x * ratioX);
		//		//int sourceOffset = ((sourceY + dy) * texture->GetWidth()) + sourceX + dx;

		//		//int sourceOffset = ((sourceY + (int)dyf) * texture->GetWidth()) + sourceX + (int)dxf;

		//		frameBuffer[offset] = sourcePixelData[sourceOffset];
		//		offset++;

		//		dxf += ratioX;

		//	}
		//	offset += frameWidth - rectWidth;
		//
		//	dyf += ratioY;
		//}






		//SDL_SetTextureBlendMode(drawableTexture, SDL_BLENDMODE_BLEND);
		//SDL_SetTextureAlphaMod(drawableTexture, 240);
		//SDL_SetTextureColorMod(drawableTexture, 255, 0, 0);
		//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
//		SDL_RenderCopy(renderer, drawableTexture, rectSource, rectTarget);
	}

	//delete rectTarget;
	//delete rectSource;
	//Do not delete the sdl texture - it belongs to the TextureImage
	//	delete texture;
	//SDL_DestroyTexture(texture);
}

