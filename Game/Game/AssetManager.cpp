#include "AssetManager.h"
#include <algorithm>
#include <string>
#include <fstream>

//Specify path seperator based on which platform we are using
#ifdef _WIN32
std::string PATH_SEPARATOR = "\\";
#else
std::string PATH_SEPARATOR = "/";
#endif

std::string						AssetManager::s_ComponentName;
std::string						AssetManager::s_ImageResourcePath;
std::string						AssetManager::s_FontResourcePath;
std::string						AssetManager::s_SoundResourcePath;
											  
Palette*						AssetManager::s_DefaultPalette;
Color*							AssetManager::s_DefaultPenColor;
Color*							AssetManager::s_DefaultFillColor;
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
	LogEngine::Log(LOG_TRACE, s_ComponentName, "Constructor called.");
}

//Hidden Desctructor - won't be called - since it's static (no instantiation)
AssetManager::~AssetManager()
{
	LogEngine::Log(LOG_TRACE, s_ComponentName, "Destructor called.");
}

int AssetManager::SetUpResourcePaths()
{
	//Gather the BasePath from SDL (we use static, so it will be global --> we need to querry only once)
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

	s_ImageResourcePath = basePath + "res" + PATH_SEPARATOR + "images" + PATH_SEPARATOR;
	s_FontResourcePath = basePath + "res" + PATH_SEPARATOR + "fonts" + PATH_SEPARATOR;
	s_SoundResourcePath = basePath + "res" + PATH_SEPARATOR + "sounds" + PATH_SEPARATOR;

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

	LogEngine::Log(LOG_TRACE, s_ComponentName, "Init() called.");

	//Set up Paths
	if (AssetManager::SetUpResourcePaths() != 0)
	{
		LogEngine::Log(LOG_ERROR, s_ComponentName, "Init...ERROR.");
		return 1;
	};

	//Create Palette
	s_DefaultPalette = new Palette();
	s_DefaultPalette->CreateDefaultPalette();

	//Create Default Colors
	s_DefaultPenColor = CreateColor(255, 192, 192, 192);
	s_DefaultFillColor = CreateColor(255, 255, 128, 128);

	if (s_DefaultPenColor == nullptr || s_DefaultFillColor == nullptr)
	{
		LogEngine::Log(LOG_ERROR, s_ComponentName, "CreateColor()...ERROR.");
		return 1;
	}

	//Create Default Texture Image
	//s_DefaultTexture = CreateTexture("Button.png");
	//if (s_DefaultTexture == nullptr)
	//{
	//	LogEngine::Log(LOG_ERROR, s_ComponentName, "CreateTexture()...ERROR.");
	//	return 1;
	//}

	//Create Default Font
	//defaultFont = CreateFont("segoeui.ttf", 12);
	//if (defaultFont == nullptr)
	//{
	//	LogEngine::Log(LOG_ERROR, s_ComponentName, "CreateFont()...ERROR.");
	//	return 1;
	//}

	LogEngine::Log(LOG_TRACE, s_ComponentName, "Init()...OK.");

	return 0;
}

Color* AssetManager::GetDefaultPenColor()
{
	return s_DefaultPenColor;
}

Color* AssetManager::GetDefaultFillColor()
{
	return s_DefaultFillColor;
}

Texture* AssetManager::GetDefaultTexture()
{
	return s_DefaultTexture;
}

Font* AssetManager::GetDefaultFont()
{
	return s_DefaultFont;
}

Color* AssetManager::CreateColor(int a, int r, int g, int b)
{
	Color fromColor = new Color(a, r, g, b);
	Color* pFromColor = &fromColor;
	Color* newColor = s_DefaultPalette->CreateCompatibleColor(pFromColor);
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
		LogEngine::SetFilterFlags(LOG_DEBUG);
		LogEngine::Log(LOG_DEBUG, "AssetManager", resourceFileNamePath + ", RefCount=" + std::to_string(resource->GetReferenceCount()));
		LogEngine::SetFilterFlags(LOG_NONE);

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
		LogEngine::SetFilterFlags(LOG_DEBUG);
		LogEngine::Log(LOG_DEBUG, "AssetManager", resourceFileNamePath + ", RefCount=" + std::to_string(resource->GetReferenceCount()));
		LogEngine::SetFilterFlags(LOG_NONE);

		newTextureAtlas = (TextureAtlas*)resource;
		return newTextureAtlas;
	}

	SDL_Surface* sdlSurface = IMG_Load((resourceFileNamePath).c_str());

	if (sdlSurface == nullptr)
	{
		LogEngine::Log(LOG_TRACE, s_ComponentName, "CreateTexture() failed on " + imageFileName);
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

	//Create compatible color texture pixels
	uint8_t* pixelData = new uint8_t[textureWidth * textureHeight];

	for (int y = 0; y < textureHeight; y++)
	{
		for (int x = 0; x < textureWidth; x++)
		{
			int redValue = ((uint8_t*)sdlSurface->pixels)[y*textureWidthInBytes + x * textureBytesPerPixel];
			int greenValue = ((uint8_t*)sdlSurface->pixels)[y*textureWidthInBytes + x * textureBytesPerPixel + 1];
			int blueValue = ((uint8_t*)sdlSurface->pixels)[y*textureWidthInBytes + x * textureBytesPerPixel + 2];

			Color color = Color(255, redValue, greenValue, blueValue);
			Color compatibleColor = s_DefaultPalette->CreateCompatibleColor(&color);

			pixelData[y*textureWidth + x] = compatibleColor.GetIndex();
		}
	}

	newTextureAtlas->SetPixelData((void*)pixelData);

	//32-bit color: copy image data

	AddResourceToCache((LoadableResource*)newTextureAtlas);

	LogEngine::SetFilterFlags(LOG_DEBUG);
	LogEngine::Log(LOG_DEBUG, "AssetManager", resourceFileNamePath + ", RefCount=" + std::to_string(newTextureAtlas->GetReferenceCount()));
	LogEngine::SetFilterFlags(LOG_NONE);

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
