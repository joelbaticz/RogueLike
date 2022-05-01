#pragma once

#include "LoadableResource.h"
#include "TextureAtlas.h"
#include <string>

class Font: public LoadableResource
{
private:
	std::string m_FontTextureFileName;
	int m_FontSize;
	int m_Top;
	int m_Baseline;
	int m_Bottom;
	int m_DefaultCharWidth;
	TextureAtlas* m_FontTextureAtlas;
	int m_CharacterWidths[256];

public:
	Font();
	~Font();

	void SetFontFile(std::string fileNamePath);

	std::string GetFontTextureFileName();
	int GetFontSize();
	int GetTop();
	int GetBaseline();
	int GetBottom();
	int GetDefaultCharWidth();
	int GetCharacterWidth(int asciiCode);
	TextureAtlas* GetTextureAtlas();
};