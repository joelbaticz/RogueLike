#pragma once
#include "Node.h"

//#include "GameEngine.h"

class EventManager
{
private:
	static int		s_SubscriberCount;
	static Node**	s_SubscriberList;
	static Node*	s_NodeHit;
	static Node*	s_NodeHitPrev;
	static Node*	s_NodeMouseButtonDown;
	static Node*	s_NodeMouseButtonUp;					
	static Node*	s_NodeFocused;
	
	static void BroadcastUpdate();
	static void BroadcastDraw();
	static void BroadcastDrawSubNode(Node* node);
	static void BroadcastMouse(Message* msg);
	static void BroadcastMouseSubNode(Node* node, Message* msg);
	static void BroadcastObscure(Message* msg);

	static void UnFocusTree(Node* node);
	static void FocusTree(Node* node);

	EventManager();
	~EventManager();
public:
	static int Init();
	static void UnInit();

	static void Subscribe(Node* node);
	static void Unsubscribe(Node* node);

	static void Broadcast(Message* msg);
	static void Send(Node* node, Message* msg);

	static void GrabFocus(Node* node);
};