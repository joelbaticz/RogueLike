#include "Node.h"
#include "GameEngine.h"
#include "EventManager.h"

Node::Node()
{
	LogEngine::Log(LOG_TRACE, "Node", "Creating node");

	Init("Node");
}

Node::Node(std::string name)
{
	LogEngine::Log(LOG_TRACE, "Node", "Creating node " + name);

	Init(name);
}

Node::~Node()
{
	LogEngine::Log(LOG_TRACE, "Node", "Destroying node");

	this->parent = nullptr;

	//ACTUALLY CALLING DELETE ON CHILD NODES 
}

void Node::Init(std::string name)
{
	this->name = name;
	this->parent = nullptr;
	this->firstChild = nullptr;
	this->nextSibling = nullptr;
//	EventManager::Subscribe(this);

	//Register at ResourceManager
}

std::string Node::GetName()
{
	return this->name;
}

void Node::SetName(std::string name)
{
	this->name = name;
}

Node* Node::GetParent()
{
	if (GameEngine::IsRootNode(this->parent))
	{
		//return nullptr;
	}

	return this->parent;
}

Node* Node::SetParent(Node* value)
{
	Node* prevParent = parent;
	
	if (GameEngine::IsRootNode(prevParent))
	{
		//prevParent = nullptr;
	}

	this->parent = value;
	return prevParent;
}

Node* Node::GetFirstChild()
{
	return this->firstChild;
}

void Node::SetFirstChild(Node* value)
{
	this->firstChild = value;
}

Node* Node::GetNextSibling()
{
	return this->nextSibling;
}

Node* Node::GetPreviousSibling()
{
	//Search for this's previous Node
	Node* parent = this->GetParent();
	Node* firstChild = parent->GetFirstChild();

	if (this == firstChild)
	{
		return nullptr;
	}

	//Loop until this node is found
	Node* previousSibling = firstChild;
	while (previousSibling->GetNextSibling() != this)
	{
		previousSibling = previousSibling->GetNextSibling();
	}

	return previousSibling;
}

void Node::SetNextSibling(Node* value)
{
	this->nextSibling = value;
}

void Node::SetPreviousSibling(Node* value)
{
	Node* previousSibling = this->GetPreviousSibling();
	previousSibling->SetNextSibling(value);
	value->SetNextSibling(this);
}

Node* Node::GetFirstSibling()
{
	Node* parent = this->GetParent();

	Node* node = parent->GetFirstChild();

	while (node->GetNextSibling() != this)
	{
		node = node->GetNextSibling();
	}

	return node;
}

Node* Node::GetLastSibling()
{
	Node* node = this;

	while (node->GetNextSibling() != nullptr)
	{
		node = node->GetNextSibling();
	}

	return node;
}


Node* Node::GetTopmostNode()
{
	Node* result = this;

	while(true)
	{
		if (result->GetParent() == nullptr)
		{
			return result;
		}
		else
		{
			result = result->GetParent();
		}
	}
}

void Node::AddChild(Node* nodeToAdd)
{
	if (this->GetFirstChild() == nullptr)
	{
		//No children yet
		this->SetFirstChild(nodeToAdd);
		nodeToAdd->SetParent(this);
		return;
	}

	//Has children
	Node* node = this->GetFirstChild();
	node = node->GetLastSibling();

	nodeToAdd->SetParent(this);
	node->SetNextSibling(nodeToAdd);
	
	return;
}

void Node::ProcessMessage(Message* msg)
{
	LogEngine::Log(LOG_DEBUG, "Node", "ProcessMessage() called on " + this->GetName());

	switch(msg->type)
	{
	case MSG_UPDATE:
		this->Update();
		return;
		break;
	case MSG_BUTTON_CLICKED:
	case MSG_CHECKBOX_CLICKED:
		//Pass messge to parents so they have a chance to listen for it too
		Node* parent = this->GetParent();

		if (parent != nullptr)
		{
			parent->ProcessMessage(msg);
		}
		////Bubble Down Update
		//Node* node = this->GetFirstChild();
		//while (node != nullptr)
		//{
		//	node->Update();
		//	node = node->GetNextSibling();
		//}
		////Message was bubbled down
		//return;
	}

	////Bubble Down ProcessMessage
	/*Node* node = this->GetFirstChild();
	while (node != nullptr)
	{
		node->ProcessMessage(msg);
		node = node->GetNextSibling();
	}*/



	//Call Node.Draw:
	//Node::Draw();
	//Anything else calls CanvasNode
	//Draw(), this->Draw(), dynacast, cast...
}

void Node::Update()
{
	LogEngine::Log(LOG_DEBUG, "Node", "Update() called on " + this->GetName());

	//Bubble Down Update
	//Node* node = this->GetFirstChild();
	//while (node != nullptr)
	//{
	//	node->Update();
	//	node = node->GetNextSibling();
	//}
	////Message was bubbled down
	//return;
}
