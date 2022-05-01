#include "CanvasNode.h"

#include "Color.h"
#include "AssetManager.h"
#include "RenderingEngine.h"

CanvasNode::CanvasNode() : Node()
{
	LogEngine::Log(LOG_TRACE, "CanvasNode", "Constructor called.");

	this->isVisible = true;
	this->location = new Location();
	this->size = new Size();
}

CanvasNode::CanvasNode(std::string name): Node(name)
{
	LogEngine::Log(LOG_TRACE, "CanvasNode", "Constructor called.");

	this->isVisible = true;
	this->location = new Location();
	this->size = new Size();

	SetGraphicsContext();
}

CanvasNode::~CanvasNode()
{
	LogEngine::Log(LOG_TRACE, "CanvasNode", "Destructor called.");
	
	delete this->graphics;
}

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

void CanvasNode::AddChild(Node* nodeToAdd)
{
	Node::AddChild(nodeToAdd);
	ResetGraphicsContext();

	//if (dynamic_cast<CanvasNode*>(nodeToAdd))
	//{
	//	((CanvasNode*)nodeToAdd)->SetGraphicsContext();

	//	//Fix up subcontrols too (some controls like the button use other nodes to paint it's work area and text
	//	//for which the GraphicsContext (which is kind of like a cache of Bounds and ClippingRect) needs to updated too
	//	SetGraphicsContextSubNodes(nodeToAdd);
	//}	
}

void CanvasNode::ResetGraphicsContext()
{
	this->SetGraphicsContext();
	SetGraphicsContextSubNodes(this);
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
	Rectangle* pBoundsRect = new Rectangle(0, 0, this->GetSize()->GetWidth(), this->GetSize()->GetHeight());
	this->GetScreenBoundsLoop(this, pBoundsRect);

	this->graphics->SetBoundsRectangle(pBoundsRect);
}

void CanvasNode::GetScreenBoundsLoop(Node* node, Rectangle* boundsRect)
{	
	while (node != nullptr)
	{
		if (dynamic_cast<CanvasNode*>(node))
		{
			boundsRect->SetX(boundsRect->GetX() + ((CanvasNode*)node)->GetLocation()->GetX());
			boundsRect->SetY(boundsRect->GetY() + ((CanvasNode*)node)->GetLocation()->GetY());
		}

		node = node->GetParent();
	}
}

void CanvasNode::SetClippingRect()
{
	Rectangle* pClippingRect = new Rectangle(this->GetLocation()->GetX(), this->GetLocation()->GetY(), this->GetSize()->GetWidth(), this->GetSize()->GetHeight());
	pClippingRect = RenderingEngine::ClipToParentRectangle(this->GetParent(), pClippingRect);

	this->graphics->SetClippingRectangle(pClippingRect);
}

GraphicsContext* CanvasNode::GetGraphics()
{
	return this->graphics;
}

void CanvasNode::SetGraphics(GraphicsContext* graphics)
{
	if (this->graphics != nullptr)
	{
		delete this->graphics;
	}

	this->graphics = graphics;
}

bool CanvasNode::GetIsVisible()
{
	return this->isVisible;
}

void CanvasNode::SetIsVisible(bool value)
{
	this->isVisible = value;
	
	//Bubble Down???
	Node* node = this->GetFirstChild();
	while (node != nullptr)
	{
		if (dynamic_cast<CanvasNode*>(node)) ((CanvasNode*)node)->SetIsVisible(value);
		node = node->GetNextSibling();
	}
}

Location* CanvasNode::GetLocation()
{
	return this->location;
}

void CanvasNode::SetLocation(Location* location)
{
	this->location = location;
	ResetGraphicsContext();
}

Size* CanvasNode::GetSize()
{
	return this->size;
}

void CanvasNode::SetSize(Size* size)
{
	if (size->GetWidth() < 0)
	{
		size->SetWidth(0);
	}

	if (size->GetHeight() < 0)
	{
		size->SetHeight(0);
	}

	this->size = size;
	ResetGraphicsContext();
}

Rectangle* CanvasNode::GetRectangle()
{
	return new Rectangle(this->location->GetX(), this->location->GetY(), this->size->GetWidth(), this->size->GetHeight());
}

void CanvasNode::SetRectangle(Rectangle* rect)
{
	this->location->SetX(rect->GetX());
	this->location->SetY(rect->GetY());
	this->size->SetWidth(rect->GetWidth());
	this->size->SetHeight(rect->GetHeight());

	ResetGraphicsContext();
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

void CanvasNode::SetMinimizedWindows(int value)
{
	this->minimizedWindows = value;
}

int CanvasNode::GetMinimizedWindows()
{
	return this->minimizedWindows;
}

void CanvasNode::ProcessMessage(Message* msg)
{
	LogEngine::Log(LOG_DEBUG, "CanvasNode", "ProcessMessage() called on " + this->GetName());

	//switch (msg->type)
	//{
	//case MSG_DRAW:
	//	//this->Draw();


	//	//return;
	//	////Bubble Down
	//	//Node* node = this->GetFirstChild();
	//	//while (node != nullptr)
	//	//{
	//	//	if (dynamic_cast<CanvasNode*>(node))
	//	//	{
	//	//		((CanvasNode*)node)->Draw();
	//	//	}
	//	//	node = node->GetNextSibling();
	//	//}
	//	////Message was bubbled down
	//	//return;
	//}

	//Bubble up: Dispatch message to Node's ProcessMessage
	Node::ProcessMessage(msg);
}

//void CanvasNode::Update()
//{
//	LogEngine::Log(LOG_DEBUG, "CanvasNode", "Update() called on " + this->GetName());
//
//	//Bubble up
//	super::Update();
//}

void CanvasNode::Draw(GraphicsContext* g)
{	
	LogEngine::Log(LOG_DEBUG, "CanvasNode", "Draw() called on " + this->GetName());

	//EventMan BroadcastDraw already checked visibility
	//if (this->isVisible)
	{
		RenderingEngine::SetFillColor(AssetManager::GetDefaultFillColor());
		//RenderingEngine::DrawRectangle(this, 0, 0, size->GetWidth(), size->GetHeight());
	}

	//Don't bubble upwards
	//super::Draw();

	//Bubble Down
	//Node* node = this->GetFirstChild();
	//while (node != nullptr)
	//{
	//	if (dynamic_cast<CanvasNode*>(node))
	//	{
	//		((CanvasNode*)node)->Draw();
	//	}
	//	node = node->GetNextSibling();
	//}
	////Message was bubbled down
	//return;

}
