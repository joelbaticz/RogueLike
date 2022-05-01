#pragma once
#include "ControlNode.h"
#include "Button.h"

class Scrollbar: public ControlNode
{
private:
	SpriteNinePatch* scrollBarSpriteNinePatch;
	Button* buttonUp;
	Button* buttonDown;
	Button* buttonThumb;

	int value;
	int maxValue;

	void ResetThumb();
public:
	Scrollbar(Node* parent, std::string name, int x, int y, int width, int height);
	~Scrollbar();

	Button* GetButtonUp();
	Button* GetButtonDown();

	void SetValue(int value);
	void SetMaxValue(int value);

	void ProcessMessage(Message* msg) override;
};
