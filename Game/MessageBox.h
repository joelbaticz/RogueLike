#pragma once
#include "ToolWindow.h"
#include "Label.h"

enum MessageBoxButton
{
	Ok = 1,
	Cancel = 2,
	Yes = 4,
	No = 8
};

class MessageBox: public ToolWindow
{
protected:
	Label* labelMessage;
	Button* buttonOk;
	Button* buttonCancel;
	Button* buttonYes;
	Button* buttonNo;

	MessageBox(std::string title, std::string message, MessageBoxButton buttons);
	~MessageBox();

public:
	// Should have a pointed to a handler method which gets called when one of the buttons are clicked on with the MessageBoxResult
	static MessageBoxButton ShowMessage(std::string title, std::string message, MessageBoxButton buttons);
	void ProcessMessage(Message* msg) override;
};
