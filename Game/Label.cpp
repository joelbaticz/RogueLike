#include "Label.h"
#include "EventManager.h"

void Label::SetSubComponentSizes()
{	
	//Pass it on to our basic shapes
	if (m_BackgroundNode != nullptr)
	{
		m_BackgroundNode->SetSize(this->GetSize());
	}
	if (m_TextNode != nullptr)
	{
		m_TextNode->SetSize(this->GetSize());
	}
}

void Label::Init(Node* parent, std::string name, std::string text, int x, int y, int width, int height)
{
	SetName(name);
	SetParent(parent);
	SetX(x);
	SetY(y);
	SetSize(new Size(width, height));

	Location* locationBackgroundNode = new Location(0, 0);

	Location* locationTextNode = new Location(2, 2);

	//TextureAtlas* backgroundTexture = AssetManager::CreateTextureAtlas(Configuration::UIPath + "Button.png");
	//backgroundTexture->SetHorizontalCount(1);
	//backgroundTexture->SetVerticalCount(5);

	//m_BackgroundNode = new SpriteNode();
	//m_BackgroundNode->SetComponentName("LabelBackground");
	//m_BackgroundNode->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	//m_BackgroundNode->SetLocation(locationSubComponent);
	//((SpriteNode*)m_BackgroundNode)->SetTexture(backgroundTexture);
	//((SpriteNode*)m_BackgroundNode)->SetTextureIndex(0);
	//((SpriteNode*)m_BackgroundNode)->SetCornerSize(10);

	m_BackgroundNode = new ShapeNode();
	m_BackgroundNode->SetName("LabelBackground");
	m_BackgroundNode->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_BackgroundNode->SetX(locationBackgroundNode->GetX());
	m_BackgroundNode->SetY(locationBackgroundNode->GetY());
	m_BackgroundNode->SetIsVisible(false);

	m_TextNode = new TextNode();
	m_TextNode->SetName("LabelText");
	m_TextNode->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_TextNode->SetText(text);
	m_TextNode->SetX(locationTextNode->GetX());
	m_TextNode->SetY(locationTextNode->GetY());

	this->AddChild(m_BackgroundNode);
	this->AddChild(m_TextNode);
	SetSubComponentSizes();
}

Label::Label() : super("Label")
{
	LogEngine::Log(LOG_DEBUG, "Label", "Constructor called.");

	Init(nullptr, "Label", "Label", DEFAULT_X, DEFAULT_Y, DEFAULT_WIDTH, DEFAULT_HEIGHT);

}

Label::Label(Node* parent, std::string name, std::string text, int x, int y, int width, int height) : super("Label")
{
	LogEngine::Log(LOG_DEBUG, "Label", "Constructor called.");

	Init(parent, name, text, x, y, width, height);
}


Label::~Label()
{
	LogEngine::Log(LOG_DEBUG, "Label", "Destructor called.");

	delete m_BackgroundNode;
	delete m_TextNode;
}

std::string Label::GetText()
{
	return m_TextNode->GetText();
}

void Label::SetText(std::string text)
{
	m_TextNode->SetText(text);
}

Color* Label::GetTextColor()
{
	return m_TextNode->GetTextColor();
}

void Label::SetTextColor(Color* color)
{
	m_TextNode->SetTextColor(color);
}

class Color* Label::GetFillColor()
{
	return m_BackgroundNode->GetFillColor();
}

void Label::SetFillColor(Color* color)
{
	m_BackgroundNode->SetFillColor(color);
}

Color* Label::GetStrokeColor()
{
	return m_BackgroundNode->GetStrokeColor();
}

void Label::SetStrokeColor(Color* color)
{
	m_BackgroundNode->SetStrokeColor(color);
}

void Label::SetSize(Size* value)
{
	super::SetSize(value);
	SetSubComponentSizes();
}

void Label::SetIsBackgroundVisible(bool value)
{
	m_IsBackgroundNodeVisible = value;
	m_BackgroundNode->SetIsVisible(value);
}

void Label::SetIsVisible(bool value)
{
	CanvasNode::SetIsVisible(value);
	m_BackgroundNode->SetIsVisible(m_IsBackgroundNodeVisible);
}

Align Label::GetTextAlign()
{
	return m_TextNode->GetAlign();
}

void Label::SetTextAlign(Align align)
{
	m_TextNode->SetAlign(align);
}

void Label::Draw(GraphicsContext* g)
{
	//LogEngine::Log(LOG_DEBUG, "Label", "Draw() called on " + this->GetName());

	if (GetIsVisible())
	{
		//if (m_BackgroundNode != nullptr)
		//{
		//	m_BackgroundNode->Draw();
		//}
		//if (m_TextNode != nullptr)
		//{
		//	m_TextNode->Draw();
		//}
	}

	//Don't bubble upwards
	//super::Draw(g);
}

void Label::OnMouseClick(Message* msg)
{
	//Node* parent = this->GetParent();
	//parent->ProcessMessage(msg);

	Message newMsg = Message();
	Message* pNewMsg = &newMsg;

	pNewMsg->type = MSG_LABEL_CLICKED;
	pNewMsg->sender = this;

	EventManager::Send(this->GetParent(), pNewMsg);

	//delete newMsg;
}

