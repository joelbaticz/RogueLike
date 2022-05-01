#pragma once

#include "LogEngine.h"
#include "Message.h"
#include <string>

class Node
{
private:
	std::string name;
	Node*		parent;
	Node*		firstChild;
	Node*		nextSibling;

	void Init(std::string name);
public:
	// Constructors / Destructors
	Node();
	Node(std::string name);
	virtual ~Node();

	// Accessors
	std::string GetName();
	Node* GetParent();
	Node* GetFirstChild();
	Node* GetFirstSibling();
	Node* GetLastSibling();
	Node* GetNextSibling();
	Node* GetPreviousSibling();
	Node* GetTopmostNode();
	//Node* GetTopmostNode();

	// Mutators
	void SetName(std::string name);
	virtual Node* SetParent(Node* value);
	void SetFirstChild(Node* value);
	void SetNextSibling(Node* value);
	void SetPreviousSibling(Node* value);

	// Methods
	virtual void ProcessMessage(Message* msg);
	virtual void Update(); //Called at every frame
	virtual void AddChild(Node* nodeToAdd);
	virtual void RemoveChild(Node* noteToRemove);
};