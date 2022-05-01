#include "TextNode.h"
#include "AssetManager.h"

TextNode::TextNode()
{
	this->SetName("TextNode");
	this->text = "Text";
	this->font = AssetManager::CreateFont("Arial16p.fnt");
	this->textColor = AssetManager::GetDefaultPenColor();
	this->align = AlignLeftTop;

	ResetAlignmentRectangle();
}

TextNode::~TextNode()
{}

void TextNode::ResetAlignmentRectangle()
{
	int textWidth = GetTextWidth();
	int textHeight = GetTextHeight();

	textBeginX = 0;
	textBeginY = 0;

	if (align & AlignHorizontalCenter)
	{
		textBeginX = (this->GetWidth() - textWidth) / 2;
	}
	else if (align & AlignRight)
	{
		textBeginX = this->GetWidth() - textWidth;
	}

	if (align & AlignVerticalCenter)
	{
		textBeginY =  (this->GetHeight() - textHeight) / 2;
	}
	else if (align & AlignBottom)
	{
		textBeginY = this->GetHeight() - textHeight;
	}
}


std::string TextNode::GetText()
{
	return text;
}

void TextNode::SetText(std::string value)
{
	text = value;
	ResetAlignmentRectangle();
}

Font* TextNode::GetFont()
{
	return font;
}

void TextNode::SetFont(Font* value)
{
	font = value;
	ResetAlignmentRectangle();
}

void TextNode::SetFont(std::string fontFileNamePath)
{
	font = AssetManager::CreateFont(fontFileNamePath);
	ResetAlignmentRectangle();
}

Align TextNode::GetAlign()
{
	return align;
}

void TextNode::SetAlign(Align value)
{
	align = value;
	ResetAlignmentRectangle();
}

Color* TextNode::GetTextColor()
{
	return textColor;
}

void TextNode::SetTextColor(Color* value)
{
	textColor = value;
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

void TextNode::ResetGraphicsContext()
{
	CanvasNode::ResetGraphicsContext();
	ResetAlignmentRectangle();
}

void TextNode::Draw(GraphicsContext* g)
{
	if (GetIsVisible())
	{
		g->BeginDraw();

		g->DrawText(text, font, textBeginX, textBeginY);

		g->EndDraw();
	}
}
