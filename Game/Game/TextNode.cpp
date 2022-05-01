#include "TextNode.h"
#include "AssetManager.h"

TextNode::TextNode()
{
	this->SetName("TextNode");
	this->text = "Text";
	this->font = AssetManager::CreateFont("Arial16p.fnt");
	this->textColor = AssetManager::GetDefaultPenColor();
	this->align = AlignLeftTop;
}

TextNode::~TextNode()
{}

std::string TextNode::GetText()
{
	return text;
}

void TextNode::SetText(std::string value)
{
	text = value;
}

Font* TextNode::GetFont()
{
	return font;
}

void TextNode::SetFont(Font* value)
{
	font = value;
}

Align TextNode::GetAlign()
{
	return align;
}

void TextNode::SetAlign(Align value)
{
	align = value;
}

Color* TextNode::GetTextColor()
{
	return textColor;
}

void TextNode::SetTextColor(Color* value)
{
	textColor = value;
}

void TextNode::Draw(GraphicsContext* g)
{
	LogEngine::Log(LOG_DEBUG, "TextNode", "Draw() called on " + this->GetName());

	if (GetIsVisible())
	{
		//RenderingEngine::SetPenColor(textColor);
		//RenderingEngine::DrawText(this, text, font, 0, 0);

		TextureAtlas* fontTextureAtlas = font->GetTextureAtlas();

		int fontTop = font->GetTop();
		int fontBottom = font->GetBottom();
		int fontHeight = fontBottom - fontTop;

		Rectangle rectSource = Rectangle();
		Rectangle* pRectSource = &rectSource;

		Rectangle rectTarget = Rectangle();
		Rectangle* pRectTarget = &rectTarget;

		int textWidth = GetTextWidth();
		int textHeight = GetTextHeight();

		//Modify target rectangle on Alignment
		if (align & AlignHorizontalCenter)
		{
			pRectTarget->SetX(pRectTarget->GetX() + ((this->GetSize()->GetWidth() - textWidth) / 2));
		}
		else if (align & AlignRight)
		{
			pRectTarget->SetX(pRectTarget->GetX() + (this->GetSize()->GetWidth() - textWidth));
		}
		if (align & AlignVerticalCenter)
		{
			pRectTarget->SetY(pRectTarget->GetY() + ((this->GetSize()->GetHeight() - textHeight) / 2));
		}
		else if (align & AlignBottom)
		{
			pRectTarget->SetY(pRectTarget->GetY() + (this->GetSize()->GetHeight() - textHeight));
		}


		g->BeginDraw();

		for (int i = 0; i < text.length(); i++)
		{
			int asciiCode = text[i];
			
			fontTextureAtlas->GetTextureRectangle(asciiCode, pRectSource);
		
			pRectSource->SetY(pRectSource->GetY() + fontTop);
			pRectSource->SetWidth(font->GetCharacterWidth(asciiCode));
			pRectSource->SetHeight(fontHeight);

			pRectTarget->SetWidth(font->GetCharacterWidth(asciiCode));
			pRectTarget->SetHeight(fontHeight);

			g->DrawTexture(fontTextureAtlas, pRectSource, pRectTarget);

			pRectTarget->SetX(pRectTarget->GetX() + font->GetCharacterWidth(asciiCode));
		}
		g->EndDraw();
	}

	//Don't bubble upwards
	//super::Draw();
}

int TextNode::GetTextWidth()
{
	int width = 0;

	for (int i = 0; i < text.length(); i++)
	{
		int asciiCode = text[i];
		width += font->GetCharacterWidth(asciiCode);
	}

	return width;
}

int TextNode::GetTextHeight()
{
	return font->GetBottom() - font->GetTop();
}
