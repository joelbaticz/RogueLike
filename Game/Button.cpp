#include "Button.h"
#include "AssetManager.h"


Button::Button(): ControlNode("Button")
{
	LogEngine::Log(LOG_DEBUG, "Button", "Constructor called.");

	Init(nullptr, "Button", "Caption", DEFAULT_X, DEFAULT_Y, DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

Button::Button(Node* parent, std::string name, std::string caption, int x, int y, int width, int height): ControlNode("Button")
{
	LogEngine::Log(LOG_DEBUG, "Button", "Constructor called.");

	Init(parent, name, caption, x, y, width, height);
}


Button::~Button()
{
	LogEngine::Log(LOG_DEBUG, "Button", "Destructor called.");

	delete buttonSpriteNinePatch;
	delete captionTextNode;
}

void Button::Init(Node* parent, std::string name, std::string caption, int x, int y, int width, int height)
{
	SetName(name);
	SetParent(parent);
	SetX(x);
	SetY(y);
	SetSize(new Size(width, height));

	componentLocation = new Location(0, 0);
	labelLocation = new Location(0, 0);

	TextureAtlas* buttonTextureAtlas = AssetManager::CreateTextureAtlas(Configuration::UIPath + "Button.png");
	buttonTextureAtlas->SetHorizontalCount(1);
	buttonTextureAtlas->SetVerticalCount(5); //Possible states: Normal, Hover, Pressed, KeyboardFocus, Disabled

	//buttonShape = new ShapeNode();
	//buttonShape->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	//buttonShape->SetComponentName("ToolWindowFramed");

	buttonSpriteNinePatch = new SpriteNinePatch();
	buttonSpriteNinePatch->SetName("ButtonSprite");
	buttonSpriteNinePatch->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	buttonSpriteNinePatch->SetX(componentLocation->GetX());
	buttonSpriteNinePatch->SetY(componentLocation->GetY());
	buttonSpriteNinePatch->SetTextureAtlas(buttonTextureAtlas);
	buttonSpriteNinePatch->SetTextureIndex(0);
	buttonSpriteNinePatch->SetCornerSize(5);
	this->AddChild(buttonSpriteNinePatch);

	captionTextNode = new TextNode();
	captionTextNode->SetName("CaptionTextNode");
	captionTextNode->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	captionTextNode->SetX(labelLocation->GetX());
	captionTextNode->SetY(labelLocation->GetY());
	captionTextNode->SetAlign(AlignCenterCenter);
	captionTextNode->SetText(caption);
	Color* textColor = AssetManager::CreateColor(255, 255, 255, 255);
	captionTextNode->SetTextColor(textColor);
	this->AddChild(captionTextNode);

	SetComponentSizes();

	EventManager::Subscribe(this); // To receive Update messages
}

void Button::SetComponentSizes()
{
	//Pass it on to our basic shapes
	if (buttonSpriteNinePatch != nullptr)
	{
		buttonSpriteNinePatch->SetSize(this->GetSize());
	}
	if (captionTextNode != nullptr)
	{
		captionTextNode->SetSize(this->GetSize());
	}
}

std::string Button::GetCaption()
{
	return captionTextNode->GetText();
}

void Button::SetCaption(std::string value)
{
	captionTextNode->SetText(value);
}

void Button::SetSize(Size* value)
{
	ControlNode::SetSize(value);
	SetComponentSizes();
}

void Button::SetTextureAtlas(TextureAtlas* textureAtlas)
{
	buttonSpriteNinePatch->SetTextureAtlas(textureAtlas);
}

void Button::SetTextOffset(int offset)
{
	captionTextNode->SetX(componentLocation->GetX() + offset);
	captionTextNode->SetY(componentLocation->GetY() + offset);
}

void Button::ProcessState()
{
	int textOffset = 0;
	int textureIndex = 0;

	if (!GetIsEnabled())
	{
		// Disabled
		textureIndex= 4;
	}
	else
	{
		// Enabled
		if (GetIsHover())
		{
			textureIndex = 1;
		}

		if (GetIsPressed())
		{
			textOffset = 2;
			textureIndex = 2;
		}
	}

	/*if (GetIsKeyboardFocused())
	{
		buttonSprite->SetTextureIndex(3);
		return;
	}*/

	SetTextOffset(textOffset);
	buttonSpriteNinePatch->SetTextureIndex(textureIndex);
}

void Button::Update()
{
	ProcessState();

	//Bubble up
	ControlNode::Update();
}

void Button::Draw(GraphicsContext* g)
{
	//LogEngine::Log(LOG_DEBUG, "Button", "Draw() called on " + this->GetName());

	//Visible?
	if (GetIsVisible() == false) return;

	//if (GetIsEnabled())
	//{
	//	//Enabled
	//	buttonSpriteNinePatch->SetTextureIndex(0);

	//	if (GetIsHover())
	//	{
	//		//OnHover
	//		buttonSpriteNinePatch->SetTextureIndex(1);
	//	}

	//	if (GetIsPressed())
	//	{
	//		buttonSpriteNinePatch->SetTextureIndex(2);
	//	}
	//}
	//else
	//{
	//	//Disabled
	//	buttonSpriteNinePatch->SetTextureIndex(4);
	//}

	//THE BUTTONSPRITENODE GETS DRAWN ON TOP OF THE BUTTON

	//if (buttonSprite != nullptr)
	//{
	//	buttonSprite->Draw();
	//}
	//if (captionTextNode != nullptr)
	//{
	//	captionTextNode->Draw();
	//}

	//Don't bubble upwards
	//ControlNode::Draw();
}

void Button::OnMouseClick(Message* msg)
{
	//Node* parent = this->GetParent();
	//parent->ProcessMessage(msg);

	Message newMsg = Message();
	Message* pNewMsg = &newMsg;
	
	pNewMsg->type = MSG_BUTTON_CLICKED;
	pNewMsg->sender = this;

	EventManager::Send(this->GetParent(), pNewMsg);

	//delete newMsg;
}