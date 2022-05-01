#include "ToolWindow.h"
#include "AssetManager.h"

int windowState=2;
Rectangle* restoreRectangle;

ToolWindow::ToolWindow() : ControlNode("ToolWindow")
{
	LogEngine::Log(LOG_DEBUG, "ToolWindow", "Constructor called.");

	Init(nullptr, "ToolWindow", "ToolWindowTitle", DEFAULT_X, DEFAULT_Y, DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

ToolWindow::ToolWindow(Node* parent, std::string name, std::string title, int x, int y, int width, int height) : ControlNode("ToolWindow")
{
	LogEngine::Log(LOG_DEBUG, "ToolWindow", "Constructor called.");

	Init(parent, name, title, x, y, width, height);
}

ToolWindow::~ToolWindow()
{
	LogEngine::Log(LOG_DEBUG, "ToolWindow", "Destructor called.");

	delete m_WindowFrame;
	delete m_WindowTitleBar;
	delete m_TitleTextNode;
	delete m_CloseButton;
	delete m_MaximizeButton;
	delete m_MinimizeButton;
	delete m_ContextMenuButton;
}

void ToolWindow::SetSubComponentSizes()
{
	Size* sizeFrame = this->GetSize();
	Size* sizeTitleBar = new Size(sizeFrame->GetWidth(), 20);
	Size* sizeBackground = new Size(sizeFrame->GetWidth() - 8, sizeFrame->GetHeight() - 24);
	Location* locationCloseButton = new Location(sizeFrame->GetWidth() - 20, 3);
	Location* locationMaximizeButton = new Location(sizeFrame->GetWidth() - 38, 3);
	Location* locationMinimizeButton = new Location(sizeFrame->GetWidth() - 56, 3);
	Location* locationContextMenuButton = new Location(3, 3);
	Location* locationTitleTextNode = new Location(5, 1);

	//Pass it on to our basic shapes
	if (m_WindowFrame != nullptr)
	{
		m_WindowFrame->SetSize(sizeFrame);
	}
	if (m_WindowTitleBar != nullptr)
	{
		m_WindowTitleBar->SetSize(sizeTitleBar);
	}
	if (m_TitleTextNode != nullptr)
	{
		m_TitleTextNode->SetSize(sizeTitleBar);
	}
	if (m_WindowBackground != nullptr)
	{
		m_WindowBackground->SetSize(sizeBackground);
	}
	if (m_WindowBackgroundPlain != nullptr)
	{
		m_WindowBackgroundPlain->SetSize(sizeBackground);
	}
	if (m_CloseButton != nullptr)
	{
		m_CloseButton->SetX(locationCloseButton->GetX());
		m_CloseButton->SetY(locationCloseButton->GetY());
	}
	if (m_MaximizeButton != nullptr)
	{
		m_MaximizeButton->SetX(locationMaximizeButton->GetX());
		m_MaximizeButton->SetY(locationMaximizeButton->GetY());
	}
	if (m_MinimizeButton != nullptr)
	{
		m_MinimizeButton->SetX(locationMinimizeButton->GetX());
		m_MinimizeButton->SetY(locationMinimizeButton->GetY());
	}
	if (m_ContextMenuButton != nullptr)
	{
		m_ContextMenuButton->SetX(locationContextMenuButton->GetX());
		m_ContextMenuButton->SetY(locationContextMenuButton->GetY());
		
	}
	if (m_TitleTextNode != nullptr)
	{
		if (m_ContextMenuButton->GetIsVisible())
		{
			locationTitleTextNode->SetX(locationTitleTextNode->GetX() + 16);
		}
		
		m_TitleTextNode->SetX(locationTitleTextNode->GetX());
		m_TitleTextNode->SetY(locationTitleTextNode->GetY());
	}

	//this->ResetGraphicsContext();
}

void ToolWindow::Init(Node* parent, std::string name, std::string title, int x, int y, int width, int height)
{
	Location* locationFrame = new Location(0, 0);
	Location* locationTitleBar = new Location(0, 0);// Location(3, 3);
	Location* locationBackground = new Location(4, 20);// Location(3, 23);
	
	//Component
	SetName(name);
	SetParent(parent);
	SetX(x);
	SetY(x);
	CanvasNode::SetSize(new Size(width, height));

	//SubComponent - WindowFrame
	TextureAtlas* frameTextureAtlas = AssetManager::CreateTextureAtlas(Configuration::UIPath + "ToolWindowFrame.png");
	frameTextureAtlas->SetHorizontalCount(1);
	frameTextureAtlas->SetVerticalCount(2); //Possible states: Active, Inactive

	m_WindowFrame = new SpriteNinePatch();
	m_WindowFrame->SetName("ToolWindowFrame");
	m_WindowFrame->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_WindowFrame->SetX(locationFrame->GetX());
	m_WindowFrame->SetY(locationFrame->GetY());
	m_WindowFrame->SetTextureAtlas(frameTextureAtlas);
	m_WindowFrame->SetTextureIndex(0);
	m_WindowFrame->SetCornerSize(5);
	this->AddChild(m_WindowFrame);

	//SubComponent - TitleBar
	TextureAtlas* titlebarTextureAtlas = AssetManager::CreateTextureAtlas(Configuration::UIPath + "ToolWindowTitle.png");
	titlebarTextureAtlas->SetHorizontalCount(1);
	titlebarTextureAtlas->SetVerticalCount(2); //Possible states: Active, Inactive

										  //m_WindowTitleBar = new ShapeNode();
										  //m_WindowTitleBar->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
										  //m_WindowTitleBar->SetComponentName("ToolWindowFramed");
	m_WindowTitleBar = new SpriteNinePatch();
	m_WindowTitleBar->SetName("ToolWindowTitleBar");
	m_WindowTitleBar->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_WindowTitleBar->SetX(locationTitleBar->GetX());
	m_WindowTitleBar->SetY(locationTitleBar->GetY());
	m_WindowTitleBar->SetTextureAtlas(titlebarTextureAtlas);
	m_WindowTitleBar->SetTextureIndex(1);
	m_WindowTitleBar->SetCornerSize(5);
	this->AddChild(m_WindowTitleBar);


	//SubComponent - TitleText
	m_TitleTextNode = new TextNode();
	m_TitleTextNode->SetName("ToolWindowTitle");
	m_TitleTextNode->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_TitleTextNode->SetX(locationTitleBar->GetX());
	m_TitleTextNode->SetY(locationTitleBar->GetY());
	m_TitleTextNode->SetAlign(AlignLeftCenter);
	m_TitleTextNode->SetFont("Arial16pWhite.fnt");
	m_TitleTextNode->SetText(title);
	Color* textColor = AssetManager::CreateColor(255, 255, 255, 255);
	m_TitleTextNode->SetTextColor(textColor);
	this->AddChild(m_TitleTextNode);

	//SUBCOMPONENT - BACKGROUND
	TextureAtlas* backgroundTextureAtlas = AssetManager::CreateTextureAtlas(Configuration::UIPath + "ToolWindowBackground.png");
	backgroundTextureAtlas->SetHorizontalCount(1);
	backgroundTextureAtlas->SetVerticalCount(2); //Possible states: Active, Inactive

	m_WindowBackground = new SpriteNinePatch();
	m_WindowBackground->SetName("ToolWindowBackground");
	m_WindowBackground->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_WindowBackground->SetX(locationBackground->GetX());
	m_WindowBackground->SetY(locationBackground->GetY());
	m_WindowBackground->SetTextureAtlas(backgroundTextureAtlas);
	m_WindowBackground->SetTextureIndex(0);
	m_WindowBackground->SetCornerSize(5);
	this->AddChild(m_WindowBackground);

	//m_WindowBackgroundPlain = new ShapeNode();
	//m_WindowBackgroundPlain->SetName("ToolWindowBackgroundPlain");
	//m_WindowBackgroundPlain->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	//m_WindowBackgroundPlain->SetLocation(locationBackground);
	//m_WindowBackgroundPlain->SetFillColor(AssetManager::CreateColor(255, 192, 192, 192));
	//m_WindowBackgroundPlain->SetStrokeColor(AssetManager::CreateColor(255, 192, 192, 192));
	//this->AddChild(m_WindowBackgroundPlain);

	//BUTTONS
	TextureAtlas* buttonTextureAtlas = AssetManager::CreateTextureAtlas(Configuration::UIPath + "ToolWindowButton.png");
	buttonTextureAtlas->SetHorizontalCount(1);
	buttonTextureAtlas->SetVerticalCount(8); //Possible states: 

	TextureAtlas* closeButtonTextureAtlas = AssetManager::CreateTextureAtlas(Configuration::UIPath + "ToolWindowButtonClose.png");
	closeButtonTextureAtlas->SetHorizontalCount(1);
	closeButtonTextureAtlas->SetVerticalCount(8); //Possible states: 

	//CONTEXT MENU BUTTON
	m_ContextMenuButton = new Button();
	m_ContextMenuButton->SetName("ToolWindowContextMenuButton");
	m_ContextMenuButton->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_ContextMenuButton->SetX(locationTitleBar->GetX());
	m_ContextMenuButton->SetY(locationTitleBar->GetY());
	m_ContextMenuButton->SetSize(new Size(15, 15));
	m_ContextMenuButton->SetCaption("");
	m_ContextMenuButton->SetIsVisible(false);
	m_ContextMenuButton->SetTextureAtlas(buttonTextureAtlas);
	this->AddChild(m_ContextMenuButton);

	//MINIMIZE BUTTON
	m_MinimizeButton = new Button();
	m_MinimizeButton->SetName("ToolWindowMinimizeButton");
	m_MinimizeButton->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_MinimizeButton->SetX(locationTitleBar->GetX());
	m_MinimizeButton->SetY(locationTitleBar->GetY());
	m_MinimizeButton->SetSize(new Size(15, 15));
	m_MinimizeButton->SetCaption("");
	m_MinimizeButton->SetIsVisible(false);
	m_MinimizeButton->SetTextureAtlas(buttonTextureAtlas);
	this->AddChild(m_MinimizeButton);

	//MAXIMIZE BUTTON
	m_MaximizeButton = new Button();
	m_MaximizeButton->SetName("ToolWindowMaximizeButton");
	m_MaximizeButton->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_MaximizeButton->SetX(locationTitleBar->GetX());
	m_MaximizeButton->SetY(locationTitleBar->GetY());
	m_MaximizeButton->SetSize(new Size(15, 15));
	m_MaximizeButton->SetCaption("");
	m_MaximizeButton->SetIsVisible(false);
	m_MaximizeButton->SetTextureAtlas(buttonTextureAtlas);
	this->AddChild(m_MaximizeButton);

	//CLOSE BUTTON
	m_CloseButton = new Button();
	m_CloseButton->SetName("ToolWindowCloseButton");
	m_CloseButton->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_CloseButton->SetX(locationTitleBar->GetX());
	m_CloseButton->SetY(locationTitleBar->GetY());
	m_CloseButton->SetSize(new Size(15, 15));
	m_CloseButton->SetCaption("");
	m_CloseButton->SetTextureAtlas(closeButtonTextureAtlas);
	this->AddChild(m_CloseButton);

	SetSubComponentSizes();
	ProcessState();
}

std::string ToolWindow::GetTitle()
{
	if (m_TitleTextNode != nullptr)
		return m_TitleTextNode->GetText();
	else
		return nullptr;
}

void ToolWindow::SetTitle(std::string value)
{
	if (m_TitleTextNode != nullptr)
		m_TitleTextNode->SetText(value);
}

void ToolWindow::SetSize(Size* value)
{
	CanvasNode::SetSize(value);
	SetSubComponentSizes();
}

void ToolWindow::SetSize(int width, int height)
{
	CanvasNode::SetSize(width, height);
	SetSubComponentSizes();
}

void ToolWindow::SetRectangle(Rectangle* rectangle)
{
	CanvasNode::SetRectangle(rectangle);
	SetSubComponentSizes();
}

void ToolWindow::AddChild(Node* node)
{
	if (node == m_WindowTitleBar || node == m_TitleTextNode || node == m_WindowFrame || node == m_WindowBackground || node == m_WindowBackgroundPlain ||
		node == m_CloseButton || node == m_MaximizeButton || node == m_MinimizeButton || node == m_ContextMenuButton)
	{
		Node::AddChild(node);
		return;
	}

	if (m_WindowBackground != nullptr)
	{
		m_WindowBackground->AddChild(node);
	}
	if (m_WindowBackgroundPlain != nullptr)
	{
		m_WindowBackgroundPlain->AddChild(node);
	}
}

Button* ToolWindow::GetCloseButton()
{
	return m_CloseButton;
}

Button* ToolWindow::GetMaximizeButton()
{
	return m_MaximizeButton;
}

Button* ToolWindow::GetMinimizeButton()
{
	return m_MinimizeButton;
}

Button* ToolWindow::GetContextMenuButton()
{
	return m_ContextMenuButton;
}

void ToolWindow::ProcessState()
{
	if (GetIsFocused())
	{
		m_WindowFrame->SetTextureIndex(1);
		m_WindowTitleBar->SetTextureIndex(1);

		if (m_WindowBackground != nullptr)
		{
			m_WindowBackground->SetTextureIndex(0);
		}
		//Leaks memory:
		//m_TitleTextNode->SetTextColor(AssetManager::CreateColor(255, 255, 255, 255));
		return;
	}

	m_WindowFrame->SetTextureIndex(0);
	m_WindowTitleBar->SetTextureIndex(0);

	if (m_WindowBackground != nullptr)
	{
		m_WindowBackground->SetTextureIndex(0);
	}
	//Leaks memory:
	//m_TitleTextNode->SetTextColor(AssetManager::CreateColor(255, 80, 80, 80));
	return;
}

void ToolWindow::ProcessMessage(Message* msg)
{
	if (msg->type == MSG_BUTTON_CLICKED)
	{
		if (msg->sender == m_CloseButton)
		{
			this->SetIsVisible(false);
			return;
		}

		if (msg->sender == m_MaximizeButton)
		{
			Node* parent = this->GetParent();
			Rectangle* maxRectangle;
			if (dynamic_cast<CanvasNode*>(parent))
			{
				CanvasNode* canvasParent = (CanvasNode*)this->GetParent();

				maxRectangle = canvasParent->GetRectangle();
				maxRectangle->SetX(0);
				maxRectangle->SetY(0);
			}
			else
			{
				maxRectangle = &Rectangle(0, 0, 800, 600);
			}

			if (windowState == 2)
			{
				restoreRectangle = this->GetRectangle();

				this->SetRectangle(maxRectangle);
				windowState = 3;
				return;
			}
			else
			{
				if (restoreRectangle == nullptr)
				{
					this->SetRectangle(maxRectangle);
					windowState = 3;
					m_MinimizeButton->SetIsVisible(true);
					return;
				}

				this->SetRectangle(restoreRectangle);
				windowState = 2;
				m_MinimizeButton->SetIsVisible(true);
				return;
			}
		}

		if (msg->sender == m_MinimizeButton)
		{
			Node* parent = this->GetParent();

			if (dynamic_cast<CanvasNode*>(parent))
			{
				CanvasNode* canvasParent = (CanvasNode*)this->GetParent();

				Rectangle* parentRectangle = canvasParent->GetRectangle();
			
				int x = canvasParent->GetMinimizedWindows() * 50;
				int y = parentRectangle->GetHeight() - 20;

				this->SetRectangle(new Rectangle(x, y, 200, 20));
				m_MinimizeButton->SetIsVisible(false);

				canvasParent->SetMinimizedWindows(canvasParent->GetMinimizedWindows() + 1);

				windowState = 1;
			}	
			return;
		}
	}

	//if (m_CloseButton != nullptr)
	//{
	//	m_CloseButton->ProcessMessage(msg);
	//}

	//Bubble up
	super::ProcessMessage(msg);
}

void ToolWindow::Update()
{
	ProcessState();

	//Bubble up
	super::Update();
}

void ToolWindow::Draw(GraphicsContext* g)
{
	//LogEngine::Log(LOG_DEBUG, "ToolWindow", "Draw() called on " + this->GetName());

	if (GetIsVisible())
	{
		if (m_WindowFrame != nullptr)
		{
			//m_WindowFrame->Draw();

			//if (GetIsFocused())
			//{
			//	g->BeginDraw();
			//	g->SetPenColor(AssetManager::CreateColor(255, 255, 0, 0));
			//	g->DrawRectangle(0, 0, 50, 50);
			//	g->EndDraw();
			//}
		}
		//if (m_WindowTitleBar != nullptr)
		//{
		//	m_WindowTitleBar->Draw();
		//}
		//if (m_TitleTextNode != nullptr)
		//{
		//	m_TitleTextNode->Draw();
		//}
		//if (m_CloseButton != nullptr)
		//{
		//	m_CloseButton->Draw();
		//}
	}

	//Don't bubble upwards
	//super::Draw();
}




/*
void ToolWindow::OnMouseEnter(Message* msg)
{
	ProcessState();
}

void ToolWindow::OnMouseLeave(Message* msg)
{
	ProcessState();
}

void ToolWindow::OnMouseDown(Message* msg)
{
	ProcessState();
}

void ToolWindow::OnMouseUp(Message* msg)
{
	ProcessState();
}
*/

//void ToolWindow::OnMouseMove(Message* msg)
//{
//	ControlNode::OnMouseMove(msg);
//
//	//if (this->GetIsPressed())
//	{
//		int mouseDeltaX = mouseXPrev - msg->sdlEvent->motion.x;
//		int mouseDeltaY = mouseYPrev - msg->sdlEvent->motion.y;
//
//		Location* location = this->GetLocation();
//		location->SetX(location->GetX() + mouseDeltaX);
//		location->SetY(location->GetY() + mouseDeltaY);
//		this->SetLocation(location);
//
//		//mouseXPrev = msg->sdlEvent->motion.x;
//		//mouseYPrev = msg->sdlEvent->motion.y;
//
//	}
//}
//
//void ToolWindow::OnMouseEnter(Message* msg)
//{
//	mouseXPrev = msg->sdlEvent->motion.x;
//	mouseYPrev = msg->sdlEvent->motion.y;
//}

void ToolWindow::OnMouseClick(Message* msg)
{
	//m_CloseButton->SetIsVisible(false);

	//Bubble up
	super::OnMouseClick(msg);
}