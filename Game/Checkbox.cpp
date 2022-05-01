#include "Checkbox.h"
#include "AssetManager.h"

void Checkbox::SetSubComponentSizes()
{
	Size* checkboxSize = new Size(16, 16);
	Size* textSize = new Size();
	textSize->SetWidth(this->GetWidth() - 22);
	textSize->SetHeight(16);

	//Pass it on to our basic shapes
	if (m_CheckboxSprite != nullptr)
	{
		m_CheckboxSprite->SetSize(checkboxSize);
	}
	if (m_CaptionTextNode != nullptr)
	{
		m_CaptionTextNode->SetSize(textSize);
	}
}

void Checkbox::Init(Node* parent, std::string name, std::string caption, int x, int y, int width, int height)
{
	SetName(name);
	SetParent(parent);
	SetX(x);
	SetY(y);
	SetSize(new Size(width, height));

	EventManager::Subscribe(this);

	Location* checkboxLocation = new Location(0, 0);
	Location* textLocation = new Location(22, 1);

	TextureAtlas* checkboxTextureAtlas = AssetManager::CreateTextureAtlas(Configuration::UIPath + "Checkbox.png");
	checkboxTextureAtlas->SetHorizontalCount(1);
	checkboxTextureAtlas->SetVerticalCount(8); //Possible states: Normal, Hover, Pressed, KeyboardFocus, Disabled
	
	m_CheckboxSprite = new SpriteNinePatch();
	m_CheckboxSprite->SetName("CheckboxSprite");
	//m_CheckboxSprite->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_CheckboxSprite->SetX(checkboxLocation->GetX());
	m_CheckboxSprite->SetY(checkboxLocation->GetY());
	m_CheckboxSprite->SetTextureAtlas(checkboxTextureAtlas);
	m_CheckboxSprite->SetTextureIndex(0);
	m_CheckboxSprite->SetCornerSize(1);
	this->AddChild(m_CheckboxSprite);

	m_CaptionTextNode = new TextNode();
	m_CaptionTextNode->SetName("CaptionTextNode");
	//m_CaptionTextNode->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_CaptionTextNode->SetX(textLocation->GetX());
	m_CaptionTextNode->SetY(textLocation->GetY());
	m_CaptionTextNode->SetText(caption);
	Color* textColor = AssetManager::CreateColor(255, 0, 0, 0);
	m_CaptionTextNode->SetTextColor(textColor);
	this->AddChild(m_CaptionTextNode);

	SetSubComponentSizes();
}

Checkbox::Checkbox(): super("Checkbox")
{
	LogEngine::Log(LOG_DEBUG, "Checkbox", "Constructor called.");

	Init(nullptr, "Checkbox", "Caption", DEFAULT_X, DEFAULT_Y, DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

Checkbox::Checkbox(Node* parent, std::string name, std::string caption, int x, int y, int width, int height) : super("Checkbox")
{
	LogEngine::Log(LOG_DEBUG, "Checkbox", "Constructor called.");

	Init(parent, name, caption, x, y, width, height);
}


Checkbox::~Checkbox()
{
	LogEngine::Log(LOG_DEBUG, "Checkbox", "Destructor called.");

	delete m_CheckboxSprite;
	delete m_CaptionTextNode;
}

std::string Checkbox::GetCaption()
{
	return m_CaptionTextNode->GetText();
}

void Checkbox::SetCaption(std::string value)
{
	m_CaptionTextNode->SetText(value);
}

void Checkbox::SetSize(Size* value)
{
	CanvasNode::SetSize(value);
	SetSubComponentSizes();
}

void Checkbox::ProcessState()
{
	int index = 0;

/*	if (GetIsFocused())
	{
		index = 3;
	}*/

	if (GetIsHover())
	{
		index = 1;
	}

	if (GetIsPressed())
	{
		index = 2;
	}

	//if (!GetIsEnabled())
	//{
	//	index = 4;
	//}

	if (GetIsChecked())
	{
		index += 4;

	}

	m_CheckboxSprite->SetTextureIndex(index);
}

bool Checkbox::GetIsChecked()
{
	return m_IsChecked;
}

void Checkbox::SetIsChecked(bool value)
{
	m_IsChecked = value;
}


void Checkbox::Update()
{
	ProcessState();

	//Bubble up
	super::Update();
}

//void Checkbox::Draw()
//{
//	LogEngine::Log(LOG_DEBUG, "Button", "Draw() called on " + this->GetName());
//
//	//Visible?
//	if (GetIsVisible() == false) return;
//
//	//if (GetIsEnabled())
//	//{
//	//	//Enabled
//	//	m_ButtonSprite->SetTextureIndex(0);
//
//	//	if (GetIsHover())
//	//	{
//	//		//OnHover
//	//		m_ButtonSprite->SetTextureIndex(2);
//	//	}
//	//}
//	//else
//	//{
//	//	//Disabled
//	//	m_ButtonSprite->SetTextureIndex(1);
//	//}
//
//	//if (m_ButtonSprite != nullptr)
//	//{
//	//	m_ButtonSprite->Draw();
//	//}
//	//if (m_CaptionTextNode != nullptr)
//	//{
//	//	m_CaptionTextNode->Draw();
//	//}
//
//	//Don't bubble upwards
//	super::Draw();
//}

void Checkbox::OnMouseClick(Message* msg)
{
	SetIsChecked(!GetIsChecked());
	//super::OnMouseClick(msg);

	if (GetIsChecked())
	{
		SetCaption("Checked! =)");
	}
	else
	{
		SetCaption("Unchecked. =(");
	}


	Message newMsg = Message();
	Message* pNewMsg = &newMsg;

	pNewMsg->type = MSG_CHECKBOX_CLICKED;
	pNewMsg->sender = this;

	EventManager::Send(this->GetParent(), pNewMsg);
}