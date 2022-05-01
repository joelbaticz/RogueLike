#include "AssetManager.h"
#include <algorithm>
#include <string>
#include <fstream>
#include "RendererFront.h"

std::string						AssetManager::s_ComponentName;
std::string						AssetManager::s_ImageResourcePath;
std::string						AssetManager::s_FontResourcePath;
std::string						AssetManager::s_SoundResourcePath;
											  
Palette*						AssetManager::s_DefaultPalette;
Color*							AssetManager::s_DefaultPenColor;
Color*							AssetManager::s_DefaultFillColor;
Color*							AssetManager::s_TransparentColor;
Texture*						AssetManager::s_DefaultTexture;
Font*							AssetManager::s_DefaultFont;
											  
Color*							AssetManager::s_ColorAssets;
int								AssetManager::s_ColorAssetsCount;
Texture*						AssetManager::s_TextureAssets;
int								AssetManager::s_TextureAssetCount;
Font*							AssetManager::s_FontAssets;
int								AssetManager::s_FontAssetCount;
											  
int								AssetManager::s_LastResourceIdGiven;

std::vector<LoadableResource*>	AssetManager::s_ResourceCache;

//Hidden Constructor - won't be called - since it's static (no instantiation)
AssetManager::AssetManager()
{
	LogEngine::Log(LOG_DEBUG, s_ComponentName, "Constructor called.");
}

//Hidden Desctructor - won't be called - since it's static (no instantiation)
AssetManager::~AssetManager()
{
	LogEngine::Log(LOG_DEBUG, s_ComponentName, "Destructor called.");
}

int AssetManager::SetUpResourcePaths()
{
	//Gather the BasePath from SDL (we use static, so it will be global --> we need to query only once)
	static std::string basePath;

	if (basePath.empty())
	{
		basePath = SDL_GetBasePath();

		if (basePath.empty())
		{
			//Error("getResourcePath", SDL_GetError());
			return 1;
		}
		else
		{
			int pos = basePath.rfind("bin");
			basePath = basePath.substr(0, pos);
		}
	}

	s_ImageResourcePath = basePath + "res" + Configuration::PathSeparator + "images" + Configuration::PathSeparator;
	s_FontResourcePath = basePath + "res" + Configuration::PathSeparator + "fonts" + Configuration::PathSeparator;
	s_SoundResourcePath = basePath + "res" + Configuration::PathSeparator + "sounds" + Configuration::PathSeparator;

	LogEngine::Log(LOG_TRACE, s_ComponentName, "ImageResourcePath: " + s_ImageResourcePath);
	LogEngine::Log(LOG_TRACE, s_ComponentName, "FontResourcePath: "  + s_FontResourcePath);
	LogEngine::Log(LOG_TRACE, s_ComponentName, "SoundResourcePath: " + s_SoundResourcePath);

	return 0;
}

int AssetManager::Init(std::string resourcePath)
{
	s_ComponentName = "AssetManager";
	s_ImageResourcePath = "";
	s_FontResourcePath = "";
	s_SoundResourcePath = "";
	
	s_ColorAssets = nullptr;
	s_ColorAssetsCount = 0;
	s_TextureAssets = nullptr;
	s_TextureAssetCount = 0;
	s_FontAssets = nullptr;
	s_FontAssetCount = 0;
	s_DefaultTexture = nullptr;

	LogEngine::Log(LOG_DEBUG, s_ComponentName, "Init() called.");

	//Set up Paths
	if (SetUpResourcePaths() != 0)
	{
		LogEngine::Log(LOG_DEBUG, s_ComponentName, "Init...ERROR.");
		return 1;
	};

	LogEngine::Log(LOG_TRACE, s_ComponentName, "Init()...OK.");

	return 0;
}

void AssetManager::UnInit()
{
	for(int i = 0; i < s_ResourceCache.size(); i++)
	{
		LoadableResource* resource = s_ResourceCache.at(i);

		//if (dynamic_cast<TextureAtlas*>(resource))
		//{
		//	Texture* texture = (Texture*)resource;
		//	delete texture->GetPixelData();
		//	SDL_Texture* sdlTexture = texture->GetTexture();
		//	SDL_DestroyTexture(sdlTexture);
		//}

		delete resource;
	}

	s_ResourceCache.clear();
}


Color* AssetManager::GetDefaultPenColor()
{
	if (s_DefaultPenColor == nullptr)
	{
		s_DefaultPenColor = CreateColor(255, 192, 192, 192);
	}

	return s_DefaultPenColor;
}

Color* AssetManager::GetDefaultFillColor()
{
	if (s_DefaultFillColor == nullptr)
	{
		s_DefaultFillColor = CreateColor(255, 255, 128, 128);
	}

	return s_DefaultFillColor;
}

Color* AssetManager::GetTransparentColor()
{
	if (s_TransparentColor == nullptr)
	{
		s_TransparentColor = CreateColor(255, 255, 0, 255);
	}

	return s_TransparentColor;
}

Texture* AssetManager::GetDefaultTexture()
{
	if (s_DefaultTexture == nullptr)
	{
		s_DefaultTexture = CreateTextureAtlas("Button.png");
	}

	return s_DefaultTexture;
}

Font* AssetManager::GetDefaultFont()
{
	if (s_DefaultFont == nullptr)
	{
		s_DefaultFont = CreateFont("Arial16p.fnt");
	}

	return s_DefaultFont;
}

Palette* AssetManager::GetDefaultPalette()
{
	if (s_DefaultPalette == nullptr)
	{
		s_DefaultPalette = new Palette();
		s_DefaultPalette->CreateDefaultPalette();
	}

	return s_DefaultPalette;
}

Color* AssetManager::CreateColor(int a, int r, int g, int b)
{
	Color fromColor = new Color(a, r, g, b);
	Color* pFromColor = &fromColor;
	Color* newColor = new Color();

	uint16_t redValue = r;
	uint16_t greenValue = g;
	uint16_t blueValue = b;

	uint16_t color16bit = 0;
	color16bit |= 1 << 15;
	color16bit |= redValue >> 3 << 10;
	color16bit |= greenValue >> 3 << 5;
	color16bit |= blueValue >> 3 << 0;

	newColor->SetRGB555(color16bit);
	newColor->SetColor(255, r, g, b);

	GetDefaultPalette()->CreateCompatibleColor(pFromColor, newColor);

	newColor->SetResourceId(s_LastResourceIdGiven);
	newColor->SetResourceName("Color");
	   
	//TODO: Put it in ColorAssetList, so we can dispose it on exit

	s_LastResourceIdGiven++;
	return newColor;
}


//Texture* AssetManager::CreateTexture(std::string imageFileName)
//{
//	Texture* newTexture = nullptr;
//	
//	SDL_Surface* sdlSurface = IMG_Load((s_ImageResourcePath + imageFileName).c_str());
//
//	if (sdlSurface == nullptr)
//	{
//		LogEngine::Log(LOG_TRACE, s_ComponentName, "CreateTexture() failed on " + imageFileName);
//		return nullptr;
//	}
//
//	int textureWidth = sdlSurface->w;
//	int textureWidthInBytes = sdlSurface->w; //We are creating 8bit out of 24bits [sdlSurface->pitch];
//	int textureHeight = sdlSurface->h;
//
//	newTexture = new Texture();
//	newTexture->SetResourceId(s_LastResourceIdGiven);
//	newTexture->SetResourceName("TextureImage");
//	newTexture->SetResourceFileNamePath(imageFileName);
//	newTexture->SetWidth(textureWidth);
//	newTexture->SetWidthInBytes(textureWidthInBytes);
//	newTexture->SetHeight(textureHeight);
//
//	return newTexture;
//	
//	//Create compatible color texture pixels
//	uint8_t* pixelData = new uint8_t[textureWidth * textureHeight];
//	
//	for (int y = 0; y < textureHeight; y++)
//	{
//		for (int x = 0; x < textureWidth; x++)
//		{
//			int redValue	= ((uint8_t*)sdlSurface->pixels)[y*textureWidthInBytes + x*3];
//			int greenValue	= ((uint8_t*)sdlSurface->pixels)[y*textureWidthInBytes + x*3 + 1];
//			int blueValue	= ((uint8_t*)sdlSurface->pixels)[y*textureWidthInBytes + x*3 + 2];
//
//			Color color = Color(255, redValue, greenValue, blueValue);
//			Color compatibleColor = s_DefaultPalette->CreateCompatibleColor(&color);
//
//			pixelData[y*textureWidth + x] = compatibleColor.GetIndex();
//		}
//	}
//
//	newTexture->SetPixelData((void*)pixelData);
//
//	//32-bit color: copy image data
//
//	//TODO: Put it in TextureAssetList, so we can dispose it on exit
//
//	s_LastResourceIdGiven++;
//	return newTexture;
//}

Font* AssetManager::CreateFont(std::string fontFileName)
{
	std::string resourceFileNamePath = s_FontResourcePath + fontFileName;
	std::transform(resourceFileNamePath.begin(), resourceFileNamePath.end(), resourceFileNamePath.begin(), ::toupper);

	LoadableResource* resource;
	Font* newFont = nullptr;
	
	resource = GetResourceFromCache(resourceFileNamePath);

	if (resource != nullptr)
	{
		int origFlags = LogEngine::GetFilterFlags();
		//LogEngine::SetFilterFlags(origFlags | LOG_DEBUG);
		LogEngine::Log(LOG_DEBUG, "AssetManager", resourceFileNamePath + ", RefCount=" + std::to_string(resource->GetReferenceCount()));
		LogEngine::SetFilterFlags(origFlags);

		newFont = (Font*)resource;
		return newFont;
	}

	newFont = new Font();
	newFont->SetResourceId(s_LastResourceIdGiven);
	newFont->SetResourceName("Font");
	newFont->SetResourceFileNamePath(resourceFileNamePath);
	newFont->SetFontFile(resourceFileNamePath);
	newFont->SetReferenceCount(1);

	AddResourceToCache((LoadableResource*)newFont);

	s_LastResourceIdGiven++;
	return newFont;
}

LoadableResource* AssetManager::GetResourceFromCache(std::string resourceFileNamePath)
{
	for(LoadableResource* resource : s_ResourceCache)
	{
		if (resourceFileNamePath.compare(resource->GetResourceFileNamePath()) == 0)
		{
			int refCount = resource->GetReferenceCount();
			refCount++;
			resource->SetReferenceCount(refCount);

			return resource;
		}
	}

	return nullptr;
}

void AssetManager::AddResourceToCache(LoadableResource* resource)
{
	s_ResourceCache.push_back(resource);
}

TextureAtlas* AssetManager::CreateTextureAtlas(std::string imageFileName)
{
	std::string resourceFileNamePath = s_ImageResourcePath + imageFileName;
	std::transform(resourceFileNamePath.begin(), resourceFileNamePath.end(), resourceFileNamePath.begin(), ::toupper);
	LoadableResource* resource;
	TextureAtlas* newTextureAtlas = nullptr;

	resource = GetResourceFromCache(resourceFileNamePath);

	if (resource != nullptr)
	{
		int origFlags = LogEngine::GetFilterFlags();
		//LogEngine::SetFilterFlags(origFlags | LOG_DEBUG);
		LogEngine::Log(LOG_DEBUG, "AssetManager", resourceFileNamePath + ", RefCount=" + std::to_string(resource->GetReferenceCount()));
		LogEngine::SetFilterFlags(origFlags);

		newTextureAtlas = (TextureAtlas*)resource;
		return newTextureAtlas;
	}

	SDL_Surface* sdlSurface = IMG_Load((resourceFileNamePath).c_str());

	if (sdlSurface == nullptr)
	{
		LogEngine::Log(LOG_ERROR, s_ComponentName, "CreateTexture() failed on " + imageFileName);
		
		//throw new std::logic_error("Asset was not found! - " + imageFileName);

		return nullptr;
	}

	int textureWidth = sdlSurface->w;
	int textureWidthInBytes = sdlSurface->pitch;// > w; //We are creating 8bit out of 24bits [sdlSurface->pitch];
	int textureBytesPerPixel = textureWidthInBytes / textureWidth;
	int textureHeight = sdlSurface->h;

	newTextureAtlas = new TextureAtlas();
	newTextureAtlas->SetResourceId(s_LastResourceIdGiven);
	newTextureAtlas->SetResourceName("TextureImage");
	newTextureAtlas->SetResourceFileNamePath(resourceFileNamePath);
	newTextureAtlas->SetReferenceCount(1);
	newTextureAtlas->SetWidth(textureWidth);
	newTextureAtlas->SetWidthInBytes(textureWidthInBytes / textureBytesPerPixel);
	newTextureAtlas->SetHeight(textureHeight);
	newTextureAtlas->SetHorizontalCount(1);
	newTextureAtlas->SetVerticalCount(1);

	/*
#define MODE_16BIT
	//Create compatible color texture pixels
#ifdef MODE_16BIT
	//uint16_t* pixelData = new uint16_t[textureWidth * textureHeight];
#else
	//uint8_t* pixelData = new uint8_t[textureWidth * textureHeight];
#endif
	

	for (int y = 0; y < textureHeight; y++)
	{
		for (int x = 0; x < textureWidth; x++)
		{

#ifdef MODE_16BIT
			//uint8_t alphaValue = ((uint8_t*)sdlSurface->pixels)[y * textureWidthInBytes + x * textureBytesPerPixel];
			uint8_t redValue = ((uint8_t*)sdlSurface->pixels)[y * textureWidthInBytes + x * textureBytesPerPixel];
			uint8_t greenValue = ((uint8_t*)sdlSurface->pixels)[y * textureWidthInBytes + x * textureBytesPerPixel + 1];
			uint8_t blueValue = ((uint8_t*)sdlSurface->pixels)[y * textureWidthInBytes + x * textureBytesPerPixel + 2];

			uint16_t color16bit = 0;
			color16bit |= 1 << 15;
			color16bit |= (uint8_t)redValue >> 3<< 10;
			color16bit |= (uint8_t)greenValue >> 3 << 5;
			color16bit |= (uint8_t)blueValue >> 3 << 0;

			pixelData[y * textureWidth + x] = color16bit;
#else
			int redValue = ((uint8_t*)sdlSurface->pixels)[y * textureWidthInBytes + x * textureBytesPerPixel];
			int greenValue = ((uint8_t*)sdlSurface->pixels)[y * textureWidthInBytes + x * textureBytesPerPixel + 1];
			int blueValue = ((uint8_t*)sdlSurface->pixels)[y * textureWidthInBytes + x * textureBytesPerPixel + 2];

			Color color = Color(255, redValue, greenValue, blueValue);
			Color compatibleColor = Color();
			s_DefaultPalette->CreateCompatibleColor(&color, &compatibleColor);

			pixelData[y * textureWidth + x] = compatibleColor.GetIndex();
#endif
		}
	}

	*/

	void* pixelData = RendererFront::CreatePixelDataFromSurface(sdlSurface);
	newTextureAtlas->SetPixelData(pixelData);
	newTextureAtlas->SetTexture(SDL_CreateTextureFromSurface(RendererFront::GetRenderer(), sdlSurface));

	//32-bit color: copy image data

	AddResourceToCache((LoadableResource*)newTextureAtlas);

	int origFlags = LogEngine::GetFilterFlags();
	//LogEngine::SetFilterFlags(origFlags | LOG_DEBUG);
	LogEngine::Log(LOG_DEBUG, "AssetManager", resourceFileNamePath + ", RefCount=" + std::to_string(newTextureAtlas->GetReferenceCount()));
	LogEngine::SetFilterFlags(origFlags);

	// CLEAN UP

	//SDL_FreeSurface(sdlSurface);

	s_LastResourceIdGiven++;
	return newTextureAtlas;
}

//
//
//Font* AssetManager::CreateFont(std::string fontFileName, int size)
//{
//	std::string path = s_FontResourcePath + fontFileName;
//
//	Font* newFont = new Font();
//	newFont->SetFontName("Font" + s_FontAssetCount);
//	newFont->SetFontName(fontFileName);
//	newFont->SetSize(size);
//	newFont->SetTTFFont(TTF_OpenFont(path.c_str(), size));
//
//	if (newFont->GetTTFFont() == nullptr)
//	{
//		delete newFont;
//		return nullptr;
//	}
//
//	//TODO: Add to FontAssetList, so we can dispose it later
//
//	return newFont;
//}
//
