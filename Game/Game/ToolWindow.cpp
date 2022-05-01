#include "ToolWindow.h"
#include "AssetManager.h"

int windowState=2;
Rectangle* restoreRectangle;

ToolWindow::ToolWindow() : ControlNode("ToolWindow")
{
	LogEngine::Log(LOG_TRACE, "ToolWindow", "Constructor called.");

	Init(nullptr, "ToolWindow", "ToolWindowTitle", DEFAULT_X, DEFAULT_Y, DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

ToolWindow::ToolWindow(Node* parent, std::string name, std::string title, int x, int y, int width, int height) : ControlNode("ToolWindow")
{
	LogEngine::Log(LOG_TRACE, "ToolWindow", "Constructor called.");

	Init(parent, name, title, x, y, width, height);
}

ToolWindow::~ToolWindow()
{
	LogEngine::Log(LOG_TRACE, "ToolWindow", "Destructor called.");

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
		m_CloseButton->SetLocation(locationCloseButton);
	}
	if (m_MaximizeButton != nullptr)
	{
		m_MaximizeButton->SetLocation(locationMaximizeButton);
	}
	if (m_MinimizeButton != nullptr)
	{
		m_MinimizeButton->SetLocation(locationMinimizeButton);
	}
	if (m_ContextMenuButton != nullptr)
	{
		m_ContextMenuButton->SetLocation(locationContextMenuButton);
	}
	if (m_TitleTextNode != nullptr)
	{
		if (m_ContextMenuButton->GetIsVisible())
		{
			locationTitleTextNode->SetX(locationTitleTextNode->GetX() + 16);
		}
		
		m_TitleTextNode->SetLocation(locationTitleTextNode);
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
	SetLocation(new Location(x, y));
	CanvasNode::SetSize(new Size(width, height));

	//SubComponent - WindowFrame
	TextureAtlas* frameTextureAtlas = AssetManager::CreateTextureAtlas("ToolWindowFrame.png");
	frameTextureAtlas->SetHorizontalCount(1);
	frameTextureAtlas->SetVerticalCount(2); //Possible states: Active, Inactive

	m_WindowFrame = new SpriteNinePatch();
	m_WindowFrame->SetName("ToolWindowFrame");
	m_WindowFrame->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_WindowFrame->SetLocation(locationFrame);
	m_WindowFrame->SetTextureAtlas(frameTextureAtlas);
	m_WindowFrame->SetTextureIndex(0);
	m_WindowFrame->SetCornerSize(5);
	this->AddChild(m_WindowFrame);

	//SubComponent - TitleBar
	//TextureAtlas* titlebarTextureAtlas = AssetManager::CreateTextureAtlas("ToolWindowTitle.png");
	TextureAtlas* titlebarTextureAtlas = AssetManager::CreateTextureAtlas("xp_toolwindowtitle.png");
	titlebarTextureAtlas->SetHorizontalCount(1);
	titlebarTextureAtlas->SetVerticalCount(2); //Possible states: Active, Inactive

										  //m_WindowTitleBar = new ShapeNode();
										  //m_WindowTitleBar->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
										  //m_WindowTitleBar->SetComponentName("ToolWindowFramed");
	m_WindowTitleBar = new SpriteNinePatch();
	m_WindowTitleBar->SetName("ToolWindowTitleBar");
	m_WindowTitleBar->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_WindowTitleBar->SetLocation(locationTitleBar);
	m_WindowTitleBar->SetTextureAtlas(titlebarTextureAtlas);
	m_WindowTitleBar->SetTextureIndex(1);
	m_WindowTitleBar->SetCornerSize(5);
	this->AddChild(m_WindowTitleBar);


	//SubComponent - TitleText
	m_TitleTextNode = new TextNode();
	m_TitleTextNode->SetName("ToolWindowTitle");
	m_TitleTextNode->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_TitleTextNode->SetLocation(locationTitleBar);
	m_TitleTextNode->SetAlign(AlignLeftCenter);
	m_TitleTextNode->SetText(title);
	Color* textColor = AssetManager::CreateColor(255, 255, 255, 255);
	m_TitleTextNode->SetTextColor(textColor);
	this->AddChild(m_TitleTextNode);

	//SUBCOMPONENT - BACKGROUND
	//TextureAtlas* backgroundTextureAtlas = AssetManager::CreateTextureAtlas("ToolWindowBackground.png");
	//backgroundTextureAtlas->SetHorizontalCount(1);
	//backgroundTextureAtlas->SetVerticalCount(2); //Possible states: Active, Inactive

	//m_WindowBackground = new SpriteNinePatch();
	//m_WindowBackground->SetName("ToolWindowBackground");
	//m_WindowBackground->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	//m_WindowBackground->SetLocation(locationBackground);
	//m_WindowBackground->SetTextureAtlas(backgroundTextureAtlas);
	//m_WindowBackground->SetTextureIndex(0);
	//m_WindowBackground->SetCornerSize(5);
	//this->AddChild(m_WindowBackground);


	m_WindowBackgroundPlain = new ShapeNode();
	m_WindowBackgroundPlain->SetName("ToolWindowBackgroundPlain");
	m_WindowBackgroundPlain->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_WindowBackgroundPlain->SetLocation(locationBackground);
	m_WindowBackgroundPlain->SetFillColor(AssetManager::CreateColor(255, 192, 192, 192));
	m_WindowBackgroundPlain->SetStrokeColor(AssetManager::CreateColor(255, 192, 192, 192));
	this->AddChild(m_WindowBackgroundPlain);

	//CONTEXT MENU BUTTON
	m_ContextMenuButton = new Button();
	m_ContextMenuButton->SetName("ToolWindowContextMenuButton");
	m_ContextMenuButton->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_ContextMenuButton->SetLocation(locationTitleBar);
	m_ContextMenuButton->SetSize(new Size(15, 15));
	m_ContextMenuButton->SetCaption("");
	this->AddChild(m_ContextMenuButton);

	//MINIMIZE BUTTON
	m_MinimizeButton = new Button();
	m_MinimizeButton->SetName("ToolWindowMinimizeButton");
	m_MinimizeButton->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_MinimizeButton->SetLocation(locationTitleBar);
	m_MinimizeButton->SetSize(new Size(15, 15));
	m_MinimizeButton->SetCaption("");
	this->AddChild(m_MinimizeButton);

	//MAXIMIZE BUTTON
	m_MaximizeButton = new Button();
	m_MaximizeButton->SetName("ToolWindowMaximizeButton");
	m_MaximizeButton->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_MaximizeButton->SetLocation(locationTitleBar);
	m_MaximizeButton->SetSize(new Size(15, 15));
	m_MaximizeButton->SetCaption("");
	this->AddChild(m_MaximizeButton);

	//CLOSE BUTTON
	m_CloseButton = new Button();
	m_CloseButton->SetName("ToolWindowCloseButton");
	m_CloseButton->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_CloseButton->SetLocation(locationTitleBar);
	m_CloseButton->SetSize(new Size(15, 15));
	m_CloseButton->SetCaption("");

	TextureAtlas* closeButtonTextureAtlas = AssetManager::CreateTextureAtlas("xp_toolwindowclosebutton.png");
	closeButtonTextureAtlas->SetHorizontalCount(1);
	closeButtonTextureAtlas->SetVerticalCount(8); //Possible states: 
	this->AddChild(m_CloseButton);

	m_CloseButton->SetTextureAtlas(closeButtonTextureAtlas);

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
		m_WindowFrame->SetTextureIndex(0);
		m_WindowTitleBar->SetTextureIndex(1);

		if (m_WindowBackground != nullptr)
		{
			m_WindowBackground->SetTextureIndex(0);
		}
		//Leaks memory:
		//m_TitleTextNode->SetTextColor(AssetManager::CreateColor(255, 255, 255, 255));
		return;
	}

	m_WindowFrame->SetTextureIndex(1);
	m_WindowTitleBar->SetTextureIndex(0);

	if (m_WindowBackground != nullptr)
	{
		m_WindowBackground->SetTextureIndex(1);
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
	LogEngine::Log(LOG_DEBUG, "ToolWindow", "Draw() called on " + this->GetName());

	if (GetIsVisible())
	{
		//if (m_WindowFrame != nullptr)
		//{
		//	m_WindowFrame->Draw();
		//}
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
void ToolWindow::OnMouseClick(Message* msg)
{
	//m_CloseButton->SetIsVisible(false);

	//Bubble up
	super::OnMouseClick(msg);
}