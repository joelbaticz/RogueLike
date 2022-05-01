#pragma once

#include "GameEngine.h"
#include "Palette.h"
#include "Color.h"
#include "Font.h"
#include "Texture.h"
#include "TextureAtlas.h"
#include <vector>

class AssetManager
{
private:
	static std::string						s_ComponentName;
	static std::string						s_ImageResourcePath;
	static std::string						s_FontResourcePath;
	static std::string						s_SoundResourcePath;
											
	static Palette*							s_DefaultPalette;
	static Color*							s_DefaultPenColor;
	static Color*							s_DefaultFillColor;
	static Texture*							s_DefaultTexture;
	static Font*							s_DefaultFont;
	
	
	static Color*							s_ColorAssets;
	static int								s_ColorAssetsCount;
	static Texture*							s_TextureAssets;
	static int								s_TextureAssetCount;
	static Font*							s_FontAssets;
	static int								s_FontAssetCount;
											
	static int								s_LastResourceIdGiven;
	
	static std::vector<LoadableResource*>	s_ResourceCache;

	AssetManager();
	~AssetManager();
	
	static int SetUpResourcePaths();
	static LoadableResource* GetResourceFromCache(std::string imageFileName);
	static void AddResourceToCache(LoadableResource* resource);

public:
	static int Init(std::string resourcePath);
	static void UnInit();

	static Color* GetDefaultPenColor();
	static Color* GetDefaultFillColor();
	static Texture* GetDefaultTexture();
	static Font* GetDefaultFont();

	static Color* CreateColor(int a, int r, int g, int b);
	//static Texture* CreateTexture(std::string imageFileName);
	static TextureAtlas* CreateTextureAtlas(std::string imageFileName);
	static Font* CreateFont(std::string fontFileName);
};