#pragma once

#include "ControlNode.h"
#include "ToolWindow.h"
#include "Label.h"
#include "Button.h"
#include "Checkbox.h"

class InfoPane: public ToolWindow
{
private:
	typedef ToolWindow	super;
	//ToolWindow*		m_Window;
	Label*			m_LabelFPS;
	Label*			m_LabelFPSValue;
	Label*			m_LabelFrameTime;
	Label*			m_LabelFrameTimeValue;
	Label*			m_LabelFrameNo;
	Label*			m_LabelFrameNoValue;
	Button*			m_CloseButton;

	int				m_FPS;
	int				m_FrameTime;
	int				m_FrameNo;
public:
	//Constructors, destructor
	InfoPane();
	~InfoPane();

	//Accessor methods
	//void SetIsShown(bool value);

	//Overridable methods
	void Update();
	//void OnMouseEnter(Message* msg) override;
	//void OnMouseLeave(Message* msg) override;
	void OnMouseClick(Message* msg) override;
	//void Draw();
};
