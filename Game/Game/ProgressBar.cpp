#include "AssetManager.h"
#include "ProgressBar.h"

ProgressBar::ProgressBar(): ControlNode("ProgressBar")
{
	Init(nullptr, "ProgressBar", 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

ProgressBar::ProgressBar(Node* parent, std::string name, int x, int y, int width, int height) : ControlNode("ProgressBar")
{
	Init(parent, name, x, y, width, height);
}

void ProgressBar::Init(Node* parent, std::string name, int x, int y, int width, int height)
{
	this->SetParent(parent);
	this->SetName(name);
	this->SetLocation(new Location(x, y));
	this->SetSize(new Size(width, height));
	this->SetMaxValue(100);
	this->SetValue(50);

	TextureAtlas* progressBarTextureAtlas = AssetManager::CreateTextureAtlas("ProgressBar.png");
	progressBarTextureAtlas->SetHorizontalCount(1);
	progressBarTextureAtlas->SetVerticalCount(2);

	progressBarSpriteNinePatch = new SpriteNinePatch();
	progressBarSpriteNinePatch->SetName("ProgressBarSprite");
	progressBarSpriteNinePatch->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	progressBarSpriteNinePatch->SetLocation(new Location(0,0));
	progressBarSpriteNinePatch->SetTextureAtlas(progressBarTextureAtlas);
	progressBarSpriteNinePatch->SetTextureIndex(0);
	progressBarSpriteNinePatch->SetCornerSize(6);

	progressBarShapeNode = new ShapeNode();
	progressBarShapeNode->SetName("ProgressBarShapeNode");
	progressBarShapeNode->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	progressBarShapeNode->SetLocation(new Location(5, 6));
	progressBarShapeNode->SetSize(new Size(0, 0));
	progressBarShapeNode->SetFillColor(AssetManager::CreateColor(255, 180, 230, 30));
	progressBarShapeNode->SetStrokeColor(AssetManager::CreateColor(255, 180, 230, 30));

	this->AddChild(progressBarSpriteNinePatch);
	this->AddChild(progressBarShapeNode);

	SetComponentSizes();
	SetShapeNodeSize();
}

void ProgressBar::SetComponentSizes()
{
	if (progressBarSpriteNinePatch != nullptr)
	{
		progressBarSpriteNinePatch->SetSize(this->GetSize());
	}
	if (captionTextNode != nullptr)
	{
		captionTextNode->SetSize(this->GetSize());
	}
}

void ProgressBar::SetShapeNodeSize()
{
	if (progressBarShapeNode == nullptr)
	{
		return;
	}

	Size* newSize = progressBarShapeNode->GetSize();

	int width = (this->value * (this->GetSize()->GetWidth() - 10)) / (this->maxValue - 10);
	int height = this->GetSize()->GetHeight() - 10;

	newSize->SetWidth(width);
	newSize->SetHeight(height);

	//We reset size to enforce calculating ResetGraphicsContext/ClippingRect
	progressBarShapeNode->SetSize(newSize);
}

void ProgressBar::SetSize(Size* value)
{
	ControlNode::SetSize(value);
	SetShapeNodeSize();
}

int ProgressBar::GetMaxValue()
{
	return this->maxValue;
}

void ProgressBar::SetMaxValue(int value)
{
	this->maxValue = value;
	SetShapeNodeSize();
}

int ProgressBar::GetValue()
{
	return this->value;
}

void ProgressBar::SetValue(int value)
{
	this->value = value;
	SetShapeNodeSize();
}

void ProgressBar::Update()
{
	ControlNode::Update();
}

void ProgressBar::Draw(GraphicsContext* g)
{
	if (GetIsVisible() == false) return;



	//ControlNode::Draw();
}


