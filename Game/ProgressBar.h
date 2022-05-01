#pragma once

#include "ControlNode.h"
#include "SpriteNinePatch.h"
#include "ShapeNode.h"
#include "TextNode.h"

class ProgressBar: public ControlNode
{
private:
	SpriteNinePatch*	progressBarSpriteNinePatch;
	TextNode*			captionTextNode;
	ShapeNode*			progressBarShapeNode;

	int					maxValue;
	int					value;

	void Init(Node* parent, std::string name, int x, int y, int width, int height);
	void SetComponentSizes();
	void SetShapeNodeSize();

public:
	//Constructors, destructor
	ProgressBar();
	ProgressBar(Node* parent, std::string name, int x, int y, int width, int height);
	~ProgressBar() = default;

	//Accessor methods
	void SetSize(Size* value);
	int GetMaxValue();
	void SetMaxValue(int value);
	int GetValue();
	void SetValue(int value);

	//Overridable methods
	void Update();
	void Draw(GraphicsContext* g) override;
};