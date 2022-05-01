#include "Label.h"

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
	SetLocation(new Location(x, y));
	SetSize(new Size(width, height));

	Location* locationSubComponent = new Location(0, 0);

	//TextureAtlas* backgroundTexture = AssetManager::CreateTextureAtlas("Button.png");
	//backgroundTexture->SetHorizontalCount(1);
	//backgroundTexture->SetVerticalCount(5);

	//m_BackgroundNode = new SpriteNode();
	//m_BackgroundNode->SetComponentName("LabelBackground");
	//m_BackgroundNode->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	//m_BackgroundNode->SetLocation(locationSubComponent);
	//((SpriteNode*)m_BackgroundNode)->SetTexture(backgroundTexture);
	//((SpriteNode*)m_BackgroundNode)->SetTextureIndex(0);
	//((SpriteNode*)m_BackgroundNode)->SetCornerSize(10);

	m_TextNode = new TextNode();
	m_TextNode->SetName("LabelText");
	m_TextNode->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_TextNode->SetText(text);
	m_TextNode->SetLocation(locationSubComponent);
	this->AddChild(m_TextNode);
	SetSubComponentSizes();
}

Label::Label() : super("Label")
{
	LogEngine::Log(LOG_TRACE, "Label", "Constructor called.");

	Init(nullptr, "Label", "Label", DEFAULT_X, DEFAULT_Y, DEFAULT_WIDTH, DEFAULT_HEIGHT);

}

Label::Label(Node* parent, std::string name, std::string text, int x, int y, int width, int height) : super("Label")
{
	LogEngine::Log(LOG_TRACE, "Label", "Constructor called.");

	Init(parent, name, text, x, y, width, height);
}


Label::~Label()
{
	LogEngine::Log(LOG_TRACE, "Label", "Destructor called.");

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

void Label::SetSize(Size* value)
{
	super::SetSize(value);
	SetSubComponentSizes();
}

void Label::Draw(GraphicsContext* g)
{
	LogEngine::Log(LOG_DEBUG, "Label", "Draw() called on " + this->GetName());

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

