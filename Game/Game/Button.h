#pragma once

#include "ControlNode.h"
#include "SpriteNinePatch.h"
#include "TextNode.h"
#include "TextureAtlas.h"

class Button : public ControlNode
{
private:
	SpriteNinePatch*	buttonSpriteNinePatch;
	TextNode*			captionTextNode;

	void SetComponentSizes();
	void Init(Node* parent, std::string name, std::string caption, int x, int y, int width, int height);
	void ProcessState();

public:
	//Constructors, destructor
	Button();
	Button(Node* parent, std::string name, std::string caption, int x, int y, int width, int height);
	~Button();

	//Accessor methods
	std::string GetCaption();
	void SetCaption(std::string value);
	void SetSize(Size* value);
	void SetTextureAtlas(TextureAtlas* textureAtlas);

	//Overridable methods
	void Update();
	void Draw(GraphicsContext* g) override;
	void OnMouseClick(Message* msg) override;
};