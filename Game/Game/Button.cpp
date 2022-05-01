#include "Button.h"
#include "AssetManager.h"


Button::Button(): ControlNode("Button")
{
	LogEngine::Log(LOG_TRACE, "Button", "Constructor called.");

	Init(nullptr, "Button", "Caption", DEFAULT_X, DEFAULT_Y, DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

Button::Button(Node* parent, std::string name, std::string caption, int x, int y, int width, int height): ControlNode("Button")
{
	LogEngine::Log(LOG_TRACE, "Button", "Constructor called.");

	Init(parent, name, caption, x, y, width, height);
}


Button::~Button()
{
	LogEngine::Log(LOG_TRACE, "Button", "Destructor called.");

	delete buttonSpriteNinePatch;
	delete captionTextNode;
}

void Button::Init(Node* parent, std::string name, std::string caption, int x, int y, int width, int height)
{
	SetName(name);
	SetParent(parent);
	SetLocation(new Location(x, y));
	SetSize(new Size(width, height));

	Location* componentLocation = new Location(0, 0);

	TextureAtlas* buttonTextureAtlas = AssetManager::CreateTextureAtlas("Button.png");
	buttonTextureAtlas->SetHorizontalCount(1);
	buttonTextureAtlas->SetVerticalCount(5); //Possible states: Normal, Hover, Pressed, KeyboardFocus, Disabled

	//buttonShape = new ShapeNode();
	//buttonShape->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	//buttonShape->SetComponentName("ToolWindowFramed");


	buttonSpriteNinePatch = new SpriteNinePatch();
	buttonSpriteNinePatch->SetName("ButtonSprite");
	buttonSpriteNinePatch->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	buttonSpriteNinePatch->SetLocation(componentLocation);
	buttonSpriteNinePatch->SetTextureAtlas(buttonTextureAtlas);
	buttonSpriteNinePatch->SetTextureIndex(0);
	buttonSpriteNinePatch->SetCornerSize(5);
	this->AddChild(buttonSpriteNinePatch);

	captionTextNode = new TextNode();
	captionTextNode->SetName("CaptionTextNode");
	captionTextNode->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	captionTextNode->SetLocation(componentLocation);
	captionTextNode->SetAlign(AlignCenterCenter);
	captionTextNode->SetText(caption);
	Color* textColor = AssetManager::CreateColor(255, 255, 255, 255);
	captionTextNode->SetTextColor(textColor);
	this->AddChild(captionTextNode);

	SetComponentSizes();
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

void Button::ProcessState()
{
	if (!GetIsEnabled())
	{
		buttonSpriteNinePatch->SetTextureIndex(4);
		return;
	}

	if (GetIsPressed())
	{
		buttonSpriteNinePatch->SetTextureIndex(2);
		return;
	}

	if (GetIsHover())
	{
		buttonSpriteNinePatch->SetTextureIndex(1);
		return;
	}

	/*if (GetIsKeyboardFocused())
	{
		buttonSprite->SetTextureIndex(3);
		return;
	}*/

	buttonSpriteNinePatch->SetTextureIndex(0);
}

void Button::Update()
{
	ProcessState();

	//Bubble up
	ControlNode::Update();
}

void Button::Draw(GraphicsContext* g)
{
	LogEngine::Log(LOG_DEBUG, "Button", "Draw() called on " + this->GetName());

	//Visible?
	if (GetIsVisible() == false) return;

	if (GetIsEnabled())
	{
		//Enabled
		buttonSpriteNinePatch->SetTextureIndex(0);

		if (GetIsHover())
		{
			//OnHover
			buttonSpriteNinePatch->SetTextureIndex(1);
		}

		if (GetIsPressed())
		{
			buttonSpriteNinePatch->SetTextureIndex(2);
		}
	}
	else
	{
		//Disabled
		buttonSpriteNinePatch->SetTextureIndex(4);
	}

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