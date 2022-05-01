#include "CanvasNode.h"
#include "AssetManager.h"
#include "RendererFront.h"

// Constructors / Destructors
CanvasNode::CanvasNode() : Node()
{
	LogEngine::Log(LOG_DEBUG, "CanvasNode", "Constructor called.");

	this->isVisible = true;
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;

	SetGraphicsContext();
}

CanvasNode::CanvasNode(std::string name): Node(name)
{
	LogEngine::Log(LOG_DEBUG, "CanvasNode", "Constructor called.");

	this->isVisible = true;
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;

	SetGraphicsContext();
}

CanvasNode::~CanvasNode()
{
	LogEngine::Log(LOG_DEBUG, "CanvasNode", "Destructor called.");
	
	delete this->graphics;
}

// Accessors
bool CanvasNode::GetIsVisible()
{
	return this->isVisible;
}

int CanvasNode::GetX()
{
	return x;
}

int CanvasNode::GetY()
{
	return y;
}

int CanvasNode::GetWidth()
{
	return width;
}

int CanvasNode::GetHeight()
{
	return height;
}

Size* CanvasNode::GetSize()
{
	return new Size(width, height);
}

Rectangle* CanvasNode::GetRectangle()
{
	return new Rectangle(x, y, width, height);
}

GraphicsContext* CanvasNode::GetGraphics()
{
	return this->graphics;
}

void CanvasNode::GetScreenBoundsLoop(Node* node, Rectangle* boundsRect)
{
	while (node != nullptr)
	{
		if (dynamic_cast<CanvasNode*>(node))
		{
			boundsRect->SetX(boundsRect->GetX() + ((CanvasNode*)node)->GetX());
			boundsRect->SetY(boundsRect->GetY() + ((CanvasNode*)node)->GetY());
		}

		node = node->GetParent();
	}
}

int CanvasNode::GetMinimizedWindows()
{
	return this->minimizedWindows;
}


// Mutators
Node* CanvasNode::SetParent(Node* value)
{
	Node* prevParent = Node::SetParent(value);

	SetGraphicsContext();

	return prevParent;
}

void SetGraphicsContextSubNodes(Node* node)
{
	node = node->GetFirstChild();

	if (node == nullptr)
	{
		return;
	}

	while (node != nullptr)
	{
		if (dynamic_cast<CanvasNode*>(node))
		{
			((CanvasNode*)node)->ResetGraphicsContext();
			
		}

		//SetGraphicsContextSubNodes(node);

		node = node->GetNextSibling();
	}
}

void CanvasNode::SetGraphicsContext()
{
	if (this->graphics == nullptr)
	{
		graphics = new GraphicsContext();
	}

	SetBoundsRect();
	SetClippingRect();
}

void CanvasNode::SetBoundsRect()
{
	Rectangle* pBoundsRect = this->graphics->GetBounds();

	if (pBoundsRect == nullptr)
	{
		pBoundsRect = new Rectangle(0, 0, 0, 0);
	}

	pBoundsRect->SetX(0);
	pBoundsRect->SetY(0);
	pBoundsRect->SetWidth(this->GetWidth());
	pBoundsRect->SetHeight(this->GetHeight());

	this->GetScreenBoundsLoop(this, pBoundsRect);
	this->graphics->SetBoundsRectangle(pBoundsRect);
}

void CanvasNode::SetClippingRect()
{
	Rectangle* pClippingRect = this->graphics->GetClippingRectangle();

	if (pClippingRect == nullptr)
	{
		pClippingRect = new Rectangle(0, 0, 0, 0);
	}

	pClippingRect->SetX(this->GetX());
	pClippingRect->SetY(this->GetY());
	pClippingRect->SetWidth(this->GetWidth());
	pClippingRect->SetHeight(this->GetHeight());

	pClippingRect = RendererFront::ClipToParentRectangle(this->GetParent(), pClippingRect);

	this->graphics->SetClippingRectangle(pClippingRect);
}

void CanvasNode::SetGraphics(GraphicsContext* graphics)
{
	if (this->graphics != nullptr)
	{
		delete this->graphics;
	}

	this->graphics = graphics;
}

void CanvasNode::SetIsVisible(bool isVisible)
{
	this->isVisible = isVisible;

	//Bubble Down???
	Node* node = this->GetFirstChild();
	while (node != nullptr)
	{
		if (dynamic_cast<CanvasNode*>(node)) ((CanvasNode*)node)->SetIsVisible(isVisible);
		node = node->GetNextSibling();
	}
}

void CanvasNode::SetX(int x)
{
	this->x = x;
	ResetGraphicsContext();
}

void CanvasNode::SetY(int y)
{
	this->y = y;
	ResetGraphicsContext();
}

void CanvasNode::SetLocation(int x, int y)
{
	this->x = x;
	this->y = y;
	ResetGraphicsContext();
}

void CanvasNode::SetLocation(Location* location)
{
	this->x = location->GetX();
	this->y = location->GetY();
	ResetGraphicsContext();
}

void CanvasNode::SetWidth(int width)
{
	if (width < 0)
	{
		width = 0;
	}

	this->width = width;
	ResetGraphicsContext();

}

void CanvasNode::SetHeight(int height)
{
	if (height < 0)
	{
		height = 0;
	}

	this->height = height;
	ResetGraphicsContext();
}

void CanvasNode::SetSize(int width, int height)
{
	if (width < 0)
	{
		width = 0;
	}

	if (height < 0)
	{
		height = 0;
	}

	this->width = width;
	this->height = height;
	ResetGraphicsContext();
}

void CanvasNode::SetSize(Size* size)
{
	int width = size->GetWidth();
	int height = size->GetHeight();

	if (width < 0)
	{
		width = 0;
	}

	if (height < 0)
	{
		height = 0;
	}

	this->width = width;
	this->height = height;
	ResetGraphicsContext();
}

void CanvasNode::SetRectangle(Rectangle* rect)
{
	this->SetLocation(rect->GetX(), rect->GetX());
	this->SetSize(rect->GetWidth(), rect->GetHeight());
}

void CanvasNode::SetMinimizedWindows(int value)
{
	this->minimizedWindows = value;
}

// Methods
void CanvasNode::AddChild(Node* nodeToAdd)
{
	Node::AddChild(nodeToAdd);
	ResetGraphicsContext();
}

void CanvasNode::ResetGraphicsContext()
{
	this->SetGraphicsContext();
	SetGraphicsContextSubNodes(this);
}

void CanvasNode::BringToFront()
{
	Node* parent = this->GetParent();
	
	//Is this the RootNode?
	if (parent != nullptr)
	{
		Node* lastSibling = (Node*)this->GetLastSibling();

		//If lastSibling is this it means this is the Top node already
		if (lastSibling != this)
		{
			//This is not the Top node, Swap nodes
			Node* previousSibling = this->GetPreviousSibling();
			Node* nextSibling = this->GetNextSibling();

			if (previousSibling != nullptr && nextSibling != nullptr)
			{
				//The window is not the first or the last child of the parent
				previousSibling->SetNextSibling(nextSibling);
			}
			else if (previousSibling == nullptr)
			{
				parent->SetFirstChild(nextSibling);
			}
			else if (nextSibling == nullptr)
			{
				previousSibling->SetNextSibling(nullptr);
			}

			lastSibling->SetNextSibling(this);			
			this->SetNextSibling(nullptr);

			//Broadcase Z-Order changed message (so the node can recalculate it's clienrect)

			//Tell parent that Z-Order changed too
		}

		//Bring Parent window to top too
		if (parent != nullptr)
		{
			if (dynamic_cast<CanvasNode*>(this))
			{
				((CanvasNode*)parent)->BringToFront();
			}
		}
	}	
}

void CanvasNode::ProcessMessage(Message* msg)
{
	LogEngine::Log(LOG_DEBUG, "CanvasNode", "ProcessMessage() called on " + this->GetName());

	Node::ProcessMessage(msg);
}

void CanvasNode::Draw(GraphicsContext* g)
{	
	//LogEngine::Log(LOG_DEBUG, "CanvasNode", "Draw() called on " + this->GetName());

	//RendererFront::SetFillColor(AssetManager::GetDefaultFillColor());
	//RendererFront::DrawRectangle(this, 0, 0, size->GetWidth(), size->GetHeight());
}
