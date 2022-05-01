#include "Listbox.h"
#include "EventManager.h"
#include "Configuration.h"
#include "AssetManager.h"

Listbox::Listbox() : ControlNode("Listbox")
{

}

Listbox::Listbox(Node* parent, std::string name, int x, int y, int width, int height) : ControlNode("Listbox")
{
	listItemHeight = 20;
	scrollBarWidth = 24;

	TextureAtlas* listboxTextureAtlas = AssetManager::CreateTextureAtlas(Configuration::UIPath + "ListBox.png");
	listboxTextureAtlas->SetHorizontalCount(1);
	listboxTextureAtlas->SetVerticalCount(5);

	this->SetParent(parent);
	this->SetName(name);
	this->SetIsEnabled(true);
	this->SetX(x);
	this->SetY(y);
	this->SetSize(new Size(width, height));
	this->SetIsVisible(true);

	Location* componentLocation = new Location(0, 0);

	listboxSpriteNinePatch = new SpriteNinePatch();
	listboxSpriteNinePatch->SetName("ListboxSprite");
	listboxSpriteNinePatch->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	listboxSpriteNinePatch->SetX(componentLocation->GetX());
	listboxSpriteNinePatch->SetY(componentLocation->GetY());
	listboxSpriteNinePatch->SetTextureAtlas(listboxTextureAtlas);
	listboxSpriteNinePatch->SetTextureIndex(0);
	listboxSpriteNinePatch->SetCornerSize(5);
	listboxSpriteNinePatch->SetIsVisible(true);
	listboxSpriteNinePatch->SetSize(this->GetSize());
	this->AddChild(listboxSpriteNinePatch);

	scrollBar = new Scrollbar(this, "scrollBar", width - scrollBarWidth - 1, 1, scrollBarWidth, height - 2);
	this->AddChild(scrollBar);

	labels = new std::vector<Label*>();

	colorSelectedFill = AssetManager::CreateColor(255, 20, 210, 40);
	colorUnselectedFill = AssetManager::CreateColor(255, 60, 60, 60);
	colorSelectedStroke = AssetManager::CreateColor(255, 160, 255, 40);
	colorUnselectedStroke = AssetManager::CreateColor(255, 60, 60, 60);

	EventManager::Subscribe(this); // To receive Update messages
}

Listbox::~Listbox() = default;

void Listbox::ResetList()
{
	int listItemPadding = 2;
	int listItemX = listItemPadding;
	int listItemY = listItemPadding + (labelScrollOffset * listItemHeight);
	int listItemWidth = this->GetWidth() - (listItemPadding * 2) - scrollBarWidth;

	int maxItemsCanBeDisplayed = this->GetHeight() / listItemHeight;
	bool isScrollBarVisible = true;

	if (maxItemsCanBeDisplayed > stringList->size())
	{
		listItemWidth += scrollBarWidth;
		isScrollBarVisible = false;
	}

	// Clear list
	for(int i = 0; i < labels->size(); i++)
	{
		Label* nextLabel = labels->at(i);
		nextLabel->SetIsVisible(false);

		// Remove from child collection
		this->RemoveChild(nextLabel);

		delete nextLabel;
	}

	labels->clear();

	// Fill list
	for(int i = 0; i < stringList->size(); i++)
	{
		std::string listItemText = stringList->at(i);

		Label* newLabel = new Label(this, "Label", listItemText, listItemX, listItemY, listItemWidth, listItemHeight);

		labels->push_back(newLabel);
		this->AddChild(newLabel);

		listItemY += listItemHeight;
	}

	// Display and bring scrollbar back to top

	scrollBar->SetMaxValue(labels->size() - maxItemsCanBeDisplayed);
	scrollBar->SetValue(0);
	scrollBar->SetIsVisible(isScrollBarVisible);
	scrollBar->BringToFront();
}


void Listbox::SetList(std::vector<std::string> * stringList)
{
	this->stringList = stringList;

	ResetList();
}

int Listbox::GetSelectedIndex()
{
	return selectedIndex;
}

std::string Listbox::GetSelectedText()
{
	std::string result;

	return labels->at(selectedIndex)->GetText();
}


void Listbox::SetSelectedIndex(int index)
{
	if (index < 0 || index > labels->size())
	{
		return;
	}

	labels->at(selectedIndex)->SetFillColor(colorUnselectedFill);
	labels->at(selectedIndex)->SetStrokeColor(colorUnselectedStroke);
	labels->at(selectedIndex)->SetIsBackgroundVisible(false);

	selectedIndex = index;

	labels->at(selectedIndex)->SetFillColor(colorSelectedFill);
	labels->at(selectedIndex)->SetStrokeColor(colorSelectedStroke);
	labels->at(selectedIndex)->SetIsBackgroundVisible(true);
}

void Listbox::ProcessState()
{
	int textureIndex = 0;

	if (!GetIsEnabled())
	{
		// Disabled
		textureIndex = 4;
	}
	else
	{
		// Enabled
		if (GetIsHover())
		{
			textureIndex = 3;
		}

		if (GetIsPressed())
		{
			textureIndex = 2;
		}
	}

	/*if (GetIsKeyboardFocused())
	{
		buttonSprite->SetTextureIndex(3);
		return;
	}*/

	listboxSpriteNinePatch->SetTextureIndex(textureIndex);
}

void Listbox::Update()
{
	ProcessState();

	//Bubble up
	ControlNode::Update();
}

void Listbox::Draw(GraphicsContext* g)
{
	//LogEngine::Log(LOG_DEBUG, "Listbox", "Draw() called on " + this->GetName());

	//Visible?
	if (GetIsVisible() == false) return;
}

//void Listbox::OnMouseClick(Message * msg)
//{
//	Message newMsg = Message();
//	Message* pNewMsg = &newMsg;
//
//	pNewMsg->type = MSG_LISTBOX_CLICKED;
//	pNewMsg->sender = this;
//
//	EventManager::Send(this->GetParent(), pNewMsg);
//}

void Listbox::ScrollList(int itemCount)
{
	labelScrollOffset += itemCount;

	int minOffset = 0;
	int maxOffset = labels->size() - this->GetHeight() / listItemHeight;

	if (labelScrollOffset < minOffset) labelScrollOffset = minOffset;
	if (labelScrollOffset > maxOffset) labelScrollOffset = maxOffset;

	for (int i = 0; i < labels->size(); i++)
	{
		Label* label = labels->at(i);

		label->SetY((i - labelScrollOffset) * listItemHeight + 2);
	}

	//// Force recalc boundaries
	//ResetGraphicsContext();
	//ResetList();
}


void Listbox::ProcessMessage(Message* msg)
{
 	if (msg->type == MSG_LABEL_CLICKED)
	{
		for(int i = 0; i < labels->size(); i++)
		{
			if (msg->sender == labels->at(i))
			{
				SetSelectedIndex(i);

				msg->type = MSG_LISTBOX_SELECTIONCHANGED;
				msg->sender = this;
				this->GetParent()->ProcessMessage(msg);

				return;
			}
		}
	}

	if (msg->type == MSG_BUTTON_CLICKED)
	{
		if (msg->sender == scrollBar->GetButtonUp())
		{
			ScrollList(-1);
		}
		if (msg->sender == scrollBar->GetButtonDown())
		{
			ScrollList(1);
		}
	}
}




