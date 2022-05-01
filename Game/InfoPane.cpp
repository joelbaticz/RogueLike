#include "InfoPane.h"
#include "GameEngine.h"

InfoPane::InfoPane()
{
	//It seems it does not really matter if:
	//InfoPane is of Node: just create a toolwindow, alter process message (F9 handling),
	//set up clickevent handlers (closebutton pressed kinda thing)
	//InfoPane is of ControlNode: just use "this" for the parent of everything, set up clickevent handlers...
	//maybe do Get/SetIsVisibile and that's it.
	//INFOPANE should just be initializer code (called once, sets up the stuff and that's it)
	//The OnClick, OnKeyDown events should be set so it can do it's thing???

	//ToolBox: parent, componentname, windowtitle, x, y, width, height
	//m_Window = new ToolWindow(this, "InfoPaneToolWindow", "Information", 100, 100, 150, 300);
	//this->AddChild(m_Window);

	this->SetName("InfoPaneToolWindow");
	this->SetTitle("Information");
	this->SetX(0);
	this->SetY(0);
	this->SetSize(new Size(175, 100));

	Color* textColor = AssetManager::CreateColor(255, 80, 80, 80);

	int buttonX1 = 5;
	int buttonX2 = 125;
	int buttonY = 5;

	m_LabelFrameNo = new Label(this, "LabelFrameNo", "Frame no.:", buttonX1, buttonY, 100, 25);
	m_LabelFrameNo->SetTextColor(textColor);
	m_LabelFrameNoValue = new Label(this, "LabelFrameNoValue", "0", buttonX2, buttonY, 50, 25);
	m_LabelFrameNoValue->SetTextColor(textColor);
	buttonY += 25;

	m_LabelFPS = new Label(this, "LabelFPS", "FPS:", buttonX1, buttonY, 100, 25);
	m_LabelFPS->SetTextColor(textColor);
	m_LabelFPSValue = new Label(this, "LabelFPSValue", "0", buttonX2, buttonY, 50, 25);
	m_LabelFPSValue->SetTextColor(textColor);
	buttonY += 25;
	
	m_LabelFrameTime = new Label(this, "LabelFrameTime", "Frame time [ms]:", buttonX1, buttonY, 100, 25);
	m_LabelFrameTime->SetTextColor(textColor);
	m_LabelFrameTimeValue = new Label(this, "LabelFrameTimeValue", "0", buttonX2, buttonY, 50, 25);
	m_LabelFrameTimeValue->SetTextColor(textColor);
	buttonY += 25;

	//m_CloseButton = new Button(this, "CloseButton", "Close", 40, 200, 80, 25);
	//this->AddChild(m_CloseButton);

	//Button* m_CloseButton2 = new Button(this, "CloseButton2", "Close2", 60, 210, 80, 25);
	//this->AddChild(m_CloseButton2);

	//Checkbox* m_Checkbox = new Checkbox(this, "Checkbox", "Checkbox", 10, 240, 120, 25);
	//this->AddChild(m_Checkbox);

	//GameEngine::AddToRootNode(this);
	//GameEngine::AddToRootScene(this);

	this->AddChild(m_LabelFPS);
	this->AddChild(m_LabelFPSValue);
	this->AddChild(m_LabelFrameTime);
	this->AddChild(m_LabelFrameTimeValue);
	this->AddChild(m_LabelFrameNo);
	this->AddChild(m_LabelFrameNoValue);

	m_FPS = 0;
	m_FrameTime = 0;
	m_FrameNo = 0;

	EventManager::Subscribe(this); // To receive Update messages
}

InfoPane::~InfoPane()
{
	//delete m_Window;
}

void InfoPane::Update()
{
	m_FrameNo = GameEngine::GetFrameCount();
	m_FPS = GameEngine::GetFPS();
	m_FrameTime = GameEngine::GetFrameTime();

	m_LabelFrameNoValue->SetText(std::to_string(m_FrameNo));
	m_LabelFPSValue->SetText(std::to_string(m_FPS));
	m_LabelFrameTimeValue->SetText(std::to_string(m_FrameTime));

	//ToolWindow::Update();
	super::Update();
}

void InfoPane::OnMouseClick(Message* msg)
{
	//SetIsVisible(false);
	super::OnMouseClick(msg);
}

//void InfoPane::Draw()
//{
//	//if (mGetIsShown())
//	//{
//		m_Window->Draw();
//	//}
//}



//void InfoPane::SetIsShown(bool value)
//{
//	m_Window->SetIsShown(value);
//}

//void InfoPane::OnMouseEnter(Message* msg)
//{
//
//}
//
//void InfoPane::OnMouseLeave(Message* msg)
//{
//
//}