#include "Font.h"
#include "IniFileParser.h"
#include "AssetManager.h"

Font::Font()
{
	m_FontTextureAtlas = nullptr;
}

Font::~Font()
{
	if (m_FontTextureAtlas != nullptr)
	{
		//delete m_FontTextureAtlas;
	}	
}

void Font::SetFontFile(std::string fileNamePath)
{
	IniFileParser* parser = new IniFileParser();
	parser->OpenFile(fileNamePath);

	m_FontTextureFileName = parser->GetString("fonttexturefilename");
	m_FontSize = parser->GetInt("fontsize");
	m_Top = parser->GetInt("top");
	m_Baseline = parser->GetInt("baseline");
	m_Bottom = parser->GetInt("bottom");
	m_DefaultCharWidth = parser->GetInt("defaultcharwidth");

	for (int i = 0; i < 255; i++)
	{
		std::string propertyName = "charwidth" + std::to_string(i);

		int propertyValue = parser->GetInt(propertyName);

		if (propertyValue == -1)
		{
			m_CharacterWidths[i] = m_DefaultCharWidth;
		}
		else
		{
			m_CharacterWidths[i] = propertyValue;
		}
	}

	m_FontTextureAtlas = AssetManager::CreateTextureAtlas(m_FontTextureFileName);
	m_FontTextureAtlas->SetHorizontalCount(16);
	m_FontTextureAtlas->SetVerticalCount(16);

	delete parser;
}

std::string Font::GetFontTextureFileName()
{
	return m_FontTextureFileName;
}

int Font::GetFontSize()
{
	return m_FontSize;
}

int Font::GetTop()
{
	return m_Top;
}

int Font::GetBaseline()
{
	return m_Baseline;
}

int Font::GetBottom()
{
	return m_Bottom;
}

int Font::GetDefaultCharWidth()
{
	return m_DefaultCharWidth;
}

int Font::GetCharacterWidth(int asciiCode)
{
	return m_CharacterWidths[asciiCode];
}

TextureAtlas* Font::GetTextureAtlas()
{
	return m_FontTextureAtlas;
}
