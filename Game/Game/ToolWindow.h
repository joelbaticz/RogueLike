#pragma once

#include "ControlNode.h"
#include "ShapeNode.h"
#include "SpriteNinePatch.h"
#include "TextNode.h"
#include "Button.h"

class ToolWindow : public ControlNode
{
private:
	typedef	ControlNode	super;
	
	SpriteNinePatch*	m_WindowFrame;
	SpriteNinePatch*	m_WindowTitleBar;
	TextNode*			m_TitleTextNode;
	SpriteNinePatch*	m_WindowBackground;
	ShapeNode*			m_WindowBackgroundPlain;

	Button*			m_CloseButton;
	Button*			m_MaximizeButton;
	Button*			m_MinimizeButton;
	Button*			m_ContextMenuButton;

	void SetSubComponentSizes();
	void Init(Node* parent, std::string name, std::string title, int x, int y, int width, int height);
	void ProcessState();
public:
	//Constructors, destructor
	ToolWindow();
	ToolWindow(Node* parent, std::string name, std::string title, int x, int y, int width, int height);
	~ToolWindow();

	//Accessor methods
	std::string GetTitle();
	void SetTitle(std::string value);
	void SetSize(Size* value);

	Button* GetCloseButton();
	Button* GetMaximizeButton();
	Button* GetMinimizeButton();
	Button* GetContextMenuButton();

	//Overridable methods
	void ProcessMessage(Message* msg);
	void Update();
	void Draw(GraphicsContext* g) override;
	void SetRectangle(Rectangle* rectangle) override;
	void AddChild(Node* node) override;
	/*
	void OnMouseEnter(Message* msg) override;
	void OnMouseLeave(Message* msg) override;
	void OnMouseDown(Message* msg) override;
	void OnMouseUp(Message* msg) override;
	*/
	void OnMouseClick(Message* msg) override;
};