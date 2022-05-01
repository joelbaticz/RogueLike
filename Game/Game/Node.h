#pragma once

#include <string>
#include "SDL.h"
#include "LogEngine.h"
//#include "GameEngine.h"
#include "Message.h"

class Node
{
private:
	std::string name;
	Node*		parent;
	Node*		firstChild;
	Node*		nextSibling;

	void Init(std::string name);
public:
	//Constructors, destructor
	Node();
	Node(std::string name);
	~Node();

	//Accessor methods
	std::string GetName();
	void SetName(std::string name);
	Node* GetParent();
	Node* GetFirstChild();
	void SetFirstChild(Node* value);
	Node* GetNextSibling();
	void SetNextSibling(Node* value);
	Node* GetPreviousSibling();
	void SetPreviousSibling(Node* value);
	Node* GetFirstSibling();
	Node* GetLastSibling();
	//void RemoveChild(Node* child);
	Node* GetTopmostNode();
	//Node* GetTopmostNode();

	//Overridable methods
	virtual void ProcessMessage(Message* msg);
	virtual void Update(); //Called at every frame
	virtual Node* SetParent(Node* value);
	virtual void AddChild(Node* nodeToAdd);

};