#pragma once

#include "CanvasNode.h"
#include "Anchor.h"
#include "Margin.h"

class ControlNode : public CanvasNode
{
private:
	bool				isEnabled;
	bool				isHover;
	bool				isPressed;
	bool				isFocused;
	
	//bool				TabStop;
	//int				TabIndex;
	//Size*				MaxSize;
	//Size*				MinSize;
	//Anchor*			Anchor;
	//Margin*			Margin;
	//Padding*			Padding;
	//bool				IsAutoSize;
	//AutoSizeStyle*	AutoSizeStyle;
	
public:
	ControlNode(std::string name);
	~ControlNode();
		
	bool GetIsEnabled();
	void SetIsEnabled(bool value);
	bool GetIsHover();
	void SetIsHover(bool value);
	bool GetIsPressed();
	void SetIsPressed(bool value);
	bool GetIsFocused();
	void SetIsFocused(bool value);

	//virtual void Update(); //Called at every frame
	virtual void ProcessMessage(Message* msg);
	virtual void OnMouseMove(Message* msg);
	virtual void OnMouseEnter(Message* msg);
	virtual void OnMouseLeave(Message* msg);
	virtual void OnMouseDown(Message* msg);
	virtual void OnMouseUp(Message* msg);
	virtual void OnMouseClick(Message* msg);
	virtual void Draw(GraphicsContext* g) override;
};