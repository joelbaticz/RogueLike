#pragma once

#include "ControlNode.h"
#include "Align.h"
#include "CanvasNode.h"
#include "TextNode.h"
#include "ShapeNode.h"
#include "SpriteNinePatch.h"

class Label : public ControlNode
{
private:
	typedef ControlNode	super;
	CanvasNode*			m_BackgroundNode;
	TextNode*			m_TextNode;

	void SetSubComponentSizes();
	void Init(Node* parent, std::string name, std::string text, int x, int y, int width, int height);
public:
	//Constructors, destructor
	Label();
	Label(Node* parent, std::string name, std::string text, int x, int y, int width, int height);
	~Label();

	//Accessor methods
	std::string GetText();
	void SetText(std::string text);
	Color* GetTextColor();
	void SetTextColor(Color* color);
	void SetSize(Size* value);

	//Overridable methods
	virtual void Draw(GraphicsContext* g);
};
