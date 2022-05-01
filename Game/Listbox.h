#pragma once
#include "ShapeNode.h"
#include <vector>
#include "Label.h"
#include "Scrollbar.h"

class Listbox : public ControlNode
{
private:
	SpriteNinePatch* listboxSpriteNinePatch;
	ShapeNode* listboxShape;
	Scrollbar* scrollBar;
	Color* colorSelectedFill;
	Color* colorUnselectedFill;
	Color* colorSelectedStroke;
	Color* colorUnselectedStroke;

	std::vector<std::string>* stringList;
	std::vector<Label*>* labels;

	int listItemHeight;
	int scrollBarWidth;
	int selectedIndex;
	int labelScrollOffset = 0;

	void ResetList();
	void ProcessState();
	void ScrollList(int itemCount);
public:
	Listbox();
	Listbox(Node* parent, std::string name, int x, int y, int width, int height);
	~Listbox();

	void SetList(std::vector<std::string>* stringList);
	int GetSelectedIndex();
	void SetSelectedIndex(int index);
	std::string GetSelectedText();
	

	void Update();
	void Draw(GraphicsContext* g) override;
	//void OnMouseClick(Message* msg) override;
	void ProcessMessage(Message* msg) override;
};
