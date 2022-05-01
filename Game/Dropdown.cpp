#include "Dropdown.h"
#include "EventManager.h"
#include "GameEngine.h"

Dropdown::Dropdown()
{
	
}

Dropdown::Dropdown(Node* parent, std::string name, std::string caption, int x, int y, int width, int height): Button(parent, name, caption, x, y, width, height)
{
	
}

Dropdown::~Dropdown() = default;

void Dropdown::SetList(std::vector<std::string>* stringList)
{
	this->stringList = stringList;
}

void Dropdown::ShowDropdownList()
{
	int itemCount = stringList->size();
	Rectangle* bounds = this->GetGraphics()->GetBounds();
	int lineHeight = 20;
	int dropdownX = bounds->GetX();
	int dropdownY = bounds->GetY() + this->GetHeight();
	int dropdownWidth = bounds->GetWidth();
	int dropdownHeight = 10 * lineHeight;

	dropdownListShape = new ShapeNode();
	dropdownListShape->SetX(dropdownX);
	dropdownListShape->SetY(dropdownY);
	dropdownListShape->SetSize(new Size(dropdownWidth, dropdownHeight));

	GameEngine::AddToRootScene(dropdownListShape);

	dropdownListShape->BringToFront();
}

void Dropdown::OnMouseClick(Message* msg)
{
	ShowDropdownList();

	Message newMsg = Message();
	Message* pNewMsg = &newMsg;

	pNewMsg->type = MSG_DROPDOWN_CLICKED;
	pNewMsg->sender = this;

	EventManager::Send(this->GetParent(), pNewMsg);
}





