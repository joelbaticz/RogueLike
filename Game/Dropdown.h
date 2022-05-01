#pragma once
#include "Button.h"
#include <vector>
#include "ShapeNode.h"

class Dropdown : public Button
{
private:
	std::vector<std::string>* stringList;
	ShapeNode* dropdownListShape;

	void ShowDropdownList();
public:
	Dropdown();
	Dropdown(Node* parent, std::string name, std::string caption, int x, int y, int width, int height);
	~Dropdown();

	void SetList(std::vector<std::string>* stringList);
	void OnMouseClick(Message* msg) override;
};
