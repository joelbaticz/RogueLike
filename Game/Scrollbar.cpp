#include "Scrollbar.h"
#include "AssetManager.h"

Scrollbar::Scrollbar(Node* parent, std::string name, int x, int y, int width, int height): ControlNode(name)
{
	this->SetParent(parent);
	this->SetName(name);
	this->SetIsEnabled(true);
	this->SetX(x);
	this->SetY(y);
	this->SetSize(new Size(width, height));
	this->SetIsVisible(true);

	TextureAtlas* scrollBarTextureAtlas = AssetManager::CreateTextureAtlas(Configuration::UIPath + "Listbox.png");
	scrollBarTextureAtlas->SetHorizontalCount(1);
	scrollBarTextureAtlas->SetVerticalCount(5);

	TextureAtlas* scrollBarButtonUpTextureAtlas = AssetManager::CreateTextureAtlas(Configuration::UIPath + "ScrollBarButtonUp.png");
	scrollBarButtonUpTextureAtlas->SetHorizontalCount(1);
	scrollBarButtonUpTextureAtlas->SetVerticalCount(5);

	TextureAtlas* scrollBarButtonDownTextureAtlas = AssetManager::CreateTextureAtlas(Configuration::UIPath + "ScrollBarButtonDown.png");
	scrollBarButtonDownTextureAtlas->SetHorizontalCount(1);
	scrollBarButtonDownTextureAtlas->SetVerticalCount(5);

	TextureAtlas* scrollBarButtonThumbTextureAtlas = AssetManager::CreateTextureAtlas(Configuration::UIPath + "ScrollBarButtonThumb.png");
	scrollBarButtonThumbTextureAtlas->SetHorizontalCount(1);
	scrollBarButtonThumbTextureAtlas->SetVerticalCount(5);

	Location* componentLocation = new Location(0, 0);

	scrollBarSpriteNinePatch = new SpriteNinePatch();
	scrollBarSpriteNinePatch->SetName("ListboxSprite");
	scrollBarSpriteNinePatch->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	scrollBarSpriteNinePatch->SetX(componentLocation->GetX());
	scrollBarSpriteNinePatch->SetY(componentLocation->GetY());
	scrollBarSpriteNinePatch->SetTextureAtlas(scrollBarTextureAtlas);
	scrollBarSpriteNinePatch->SetTextureIndex(0);
	scrollBarSpriteNinePatch->SetCornerSize(5);
	scrollBarSpriteNinePatch->SetIsVisible(true);
	scrollBarSpriteNinePatch->SetSize(this->GetSize());
	this->AddChild(scrollBarSpriteNinePatch);

	int buttonSize = width;

	Location* buttonUpLocation = new Location(0, 0);
	Location* buttonDownLocation = new Location(0, height - buttonSize);
	Location* buttonThumbLocation = new Location(0, buttonSize);
	Size* buttonThumbSize = new Size(buttonSize, 5);

	buttonUp = new Button(this, "buttonUp", "", buttonUpLocation->GetX(), buttonUpLocation->GetY(), buttonSize, buttonSize);
	buttonUp->SetTextureAtlas(scrollBarButtonUpTextureAtlas);
	buttonDown = new Button(this, "buttonDown", "", buttonDownLocation->GetX(), buttonDownLocation->GetY(), buttonSize, buttonSize);
	buttonDown->SetTextureAtlas(scrollBarButtonDownTextureAtlas);
	buttonThumb = new Button(this, "buttonThumb", "", buttonThumbLocation->GetX(), buttonThumbLocation->GetY(), buttonSize, buttonThumbSize->GetHeight());
	buttonThumb->SetTextureAtlas(scrollBarButtonThumbTextureAtlas);

	this->AddChild(buttonUp);
	this->AddChild(buttonDown);
	this->AddChild(buttonThumb);
}

Scrollbar::~Scrollbar() = default;

Button* Scrollbar::GetButtonUp()
{
	return buttonUp;
}

Button* Scrollbar::GetButtonDown()
{
	return buttonDown;
}

void Scrollbar::ResetThumb()
{
	//int buttonSize = this->GetWidth();
	//int scrollableHeight = this->GetHeight() - (3 * buttonSize);

	//Size* thumbSize = buttonThumb->GetSize();
	//thumbSize->SetHeight(buttonSize);
	//buttonThumb->SetSize(thumbSize);

	//Location* thumbLocation = buttonThumb->GetLocation();
	//thumbLocation->SetY(buttonSize + (value * scrollableHeight / maxValue));
	//buttonThumb->SetLocation(thumbLocation);

	// With scaling Thumb

	int buttonSize = this->GetWidth();
	int maxScrollableHeight = this->GetHeight() - 2 * buttonSize;

	int thumbSize = maxScrollableHeight / maxValue;
	int remainingHeight = maxScrollableHeight - thumbSize;

	Size* buttonTumbSize = buttonThumb->GetSize();
	buttonTumbSize->SetHeight(thumbSize);
	buttonThumb->SetSize(buttonTumbSize);

	int maxThumbPosition = remainingHeight;// -thumbSize;
	int thumbPosition =  + (value * thumbSize);

	if (thumbPosition > maxThumbPosition) thumbPosition = maxThumbPosition;

	buttonThumb->SetY(buttonSize + thumbPosition);
}

void Scrollbar::SetValue(int value)
{
	this->value = value;
	ResetThumb();
}

void Scrollbar::SetMaxValue(int value)
{
	this->maxValue = value;
	ResetThumb();
}

void Scrollbar::ProcessMessage(Message* msg)
{
	if (msg->type == MSG_BUTTON_CLICKED)
	{
		if (msg->sender == this->GetButtonUp())
		{
			value--;
			if (value < 0) value = 0;

			ResetThumb();

			this->GetParent()->ProcessMessage(msg);
		}
		if (msg->sender == this->GetButtonDown())
		{
			value++;
			if (value > maxValue) value = maxValue;

			ResetThumb();

			this->GetParent()->ProcessMessage(msg);
		}
	}
}



