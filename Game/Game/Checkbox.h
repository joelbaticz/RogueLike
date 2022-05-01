#pragma once

#include "ControlNode.h"
#include "ShapeNode.h"
#include "SpriteNinePatch.h"
#include "TextNode.h"

class Checkbox : public ControlNode
{
private:
	typedef ControlNode	super;
	SpriteNinePatch*			m_CheckboxSprite;
	TextNode*			m_CaptionTextNode;
	bool				m_IsChecked;

	void SetSubComponentSizes();
	void Init(Node* parent, std::string name, std::string caption, int x, int y, int width, int height);
	void ProcessState();
public:
	//Constructors, destructor
	Checkbox();
	Checkbox(Node* parent, std::string name, std::string caption, int x, int y, int width, int height);
	~Checkbox();

	//Accessor methods
	std::string GetCaption();
	void SetCaption(std::string value);
	void SetSize(Size* value);
	bool GetIsChecked();
	void SetIsChecked(bool value);
	
	//Overridable methods
	void Update();
	//void Draw() override;
	void OnMouseClick(Message* msg);
};