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
	int						textBeginX;
	int						textBeginY;

	int GetTextWidth();
	int GetTextHeight();
	void ResetAlignmentRectangle();
public:
	// Constructors / Destructors
	TextNode();
	~TextNode();

	// Accessors
	std::string GetText();
	Font* GetFont();
	Align GetAlign();
	Color* GetTextColor();

	// Mutators
	void SetFont(Font* value);
	void SetFont(std::string fontFileNamePath);
	void SetAlign(Align value);
	void SetText(std::string value);
	void SetTextColor(Color* value);

	// Methods
	void Draw(GraphicsContext* g) override;
	void ResetGraphicsContext() override;
};