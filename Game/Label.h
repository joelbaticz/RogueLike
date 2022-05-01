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
	ShapeNode*	m_BackgroundNode;
	TextNode*	m_TextNode;

	bool m_IsBackgroundNodeVisible;

	void SetSubComponentSizes();
	void Init(Node* parent, std::string name, std::string text, int x, int y, int width, int height);
public:
	//Constructors, destructor
	Label();
	Label(Node* parent, std::string name, std::string text, int x, int y, int width, int height);
	~Label();

	//Accessor methods
	void SetSize(Size* value);
	std::string GetText();
	void SetText(std::string text);
	Color* GetFillColor();
	void SetFillColor(Color* color);
	Color* GetStrokeColor();
	void SetStrokeColor(Color* color);
	Color* GetTextColor();
	void SetTextColor(Color* color);
	Align GetTextAlign();
	void SetTextAlign(Align);
	
	void SetIsBackgroundVisible(bool value);
	void SetIsVisible(bool value) override;

	//Overridable methods
	virtual void Draw(GraphicsContext* g);
	void OnMouseClick(Message* msg) override;
};
