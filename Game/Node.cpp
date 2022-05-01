#include "Node.h"
#include "GameEngine.h"

Node::Node()
{
	LogEngine::Log(LOG_DEBUG, "Node", "Creating node");

	Init("Node");
}

Node::Node(std::string name)
{
	LogEngine::Log(LOG_DEBUG, "Node", "Creating node " + name);

	Init(name);
}

Node::~Node()
{
	LogEngine::Log(LOG_DEBUG, "Node", "Destroying node");

	this->parent = nullptr;

	//TODO: Call delete for every child node
}

void Node::Init(std::string name)
{
	this->name = name;
	this->parent = nullptr;
	this->firstChild = nullptr;
	this->nextSibling = nullptr;
	//EventManager::Subscribe(this);

	//TODO: Register at ResourceManager
}

// Accessors
std::string Node::GetName()
{
	return this->name;
}

Node* Node::GetParent()
{
	if (GameEngine::IsRootNode(this->parent))
	{
		//return nullptr;
	}

	return this->parent;
}

Node* Node::GetFirstChild()
{
	return this->firstChild;
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

	while (true)
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

// Mutators

void Node::SetName(std::string name)
{
	this->name = name;
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

void Node::SetFirstChild(Node* value)
{
	this->firstChild = value;
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

// Methods
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

void Node::RemoveChild(Node* nodeToRemove)
{
	Node* node = this->firstChild;

	while (node == nodeToRemove || node == nullptr)
	{
		node->GetNextSibling();
	}

	if (node != nullptr)
	{
		// Unlink the found node

		Node* prevNode = node->GetPreviousSibling();
		Node* nextNode = node->GetNextSibling();
		prevNode->SetNextSibling(nextNode);
	}
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
	case MSG_LISTBOX_SELECTIONCHANGED:
		//Pass message to parents so they have a chance to act on it too
		Node* parent = this->GetParent();

		if (parent != nullptr)
		{
			parent->ProcessMessage(msg);
		}
	}
}

void Node::Update()
{
	LogEngine::Log(LOG_DEBUG, "Node", "Update() called on " + this->GetName());
}
