#include "MessageBox.h"
#include "GameEngine.h"
#include "Label.h"
#include "RendererFront.h"

MessageBox::MessageBox(std::string title, std::string message, MessageBoxButton buttons)
{
	int messageBoxWidth = 275;
	int messageBoxHeight = 100;
	int messageBoxX = (RendererFront::GetWindowWidth() - messageBoxWidth) / 2;
	int messageBoxY = (RendererFront::GetWindowHeight() - messageBoxHeight) / 2;

	int buttonWidth = 80;
	int buttonHeight = 23;
	int buttonX = messageBoxWidth - buttonWidth - 10;
	int buttonY = messageBoxHeight - buttonHeight - 25;

	this->SetName("MessageBox");
	this->SetTitle(title);
	this->SetX(messageBoxX);
	this->SetY(messageBoxY);
	this->SetSize(new Size(messageBoxWidth, messageBoxHeight));
	this->GetContextMenuButton()->SetIsVisible(false);
	this->GetMinimizeButton()->SetIsVisible(false);
	this->GetMaximizeButton()->SetIsVisible(false);

	labelMessage = new Label(this, "labelMessage", message, 20, 20, RendererFront::ScreenDrawTextGetTextWidth(message, AssetManager::GetDefaultFont()) + 10, 20);
	this->AddChild(labelMessage);

	if ((buttons & MessageBoxButton::No) == MessageBoxButton::No)
	{
		buttonNo = new Button(this, "buttonNo", "No", buttonX, buttonY, buttonWidth, buttonHeight);
		this->AddChild(buttonNo);
		buttonX -= buttonWidth + 10;
	}

	if ((buttons & MessageBoxButton::Yes) == MessageBoxButton::Yes)
	{
		buttonYes = new Button(this, "buttonYes", "Yes", buttonX, buttonY, buttonWidth, buttonHeight);
		this->AddChild(buttonYes);
		buttonX -= buttonWidth + 10;
	}

	if ((buttons & MessageBoxButton::Cancel) == MessageBoxButton::Cancel)
	{
		buttonCancel = new Button(this, "buttonCancel", "Cancel", buttonX, buttonY, buttonWidth, buttonHeight);
		this->AddChild(buttonCancel);
		buttonX -= buttonWidth + 10;
	}

	if ((buttons & MessageBoxButton::Ok) == MessageBoxButton::Ok)
	{
		buttonOk = new Button(this, "buttonOk", "Ok", buttonX, buttonY, buttonWidth, buttonHeight);
		this->AddChild(buttonOk);
	}
	
	GameEngine::AddToRootScene(this);
}

MessageBox::~MessageBox() = default;

MessageBoxButton MessageBox::ShowMessage(std::string title, std::string message, MessageBoxButton buttons)
{
	MessageBoxButton result = MessageBoxButton::Cancel;


	MessageBox* messageBox = new MessageBox(title, message, buttons);

	return result;
}

void MessageBox::ProcessMessage(Message* msg)
{
	if (msg->type == MSG_BUTTON_CLICKED)
	{
		if (msg->sender == this->GetCloseButton())
		{
			this->SetIsVisible(false);
		}
		if (msg->sender == buttonOk)
		{
			this->SetIsVisible(false);
		}
		if (msg->sender == buttonCancel)
		{
		}
		if (msg->sender == buttonYes)
		{
		}
		if (msg->sender == buttonNo)
		{
		}
	}
}



