#pragma once

#include "CanvasNode.h"
#include "Font.h"
#include "Color.h"
#include "Align.h"

class TextNode : public CanvasNode
{
private:
	std::string				text;
	Font*					font;
	Color*					textColor;
	Align					align;
	//bool					isWrapped;

	int GetTextWidth();
	int GetTextHeight();
public:
	TextNode();
	~TextNode();

	std::string GetText();
	void SetText(std::string value);
	Font* GetFont();
	void SetFont(Font* value);
	Align GetAlign();
	void SetAlign(Align value);
	Color* GetTextColor();
	void SetTextColor(Color* value);

	void Draw(GraphicsContext* g) override;
};