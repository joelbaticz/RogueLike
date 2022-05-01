#include "EventManager.h"


//Init static members
Node**	EventManager::s_SubscriberList;
int		EventManager::s_SubscriberCount;
Node*	EventManager::s_NodeHit;
Node*	EventManager::s_NodeHitPrev;
Node*	EventManager::s_NodeMouseButtonDown;
Node*	EventManager::s_NodeMouseButtonUp;
Node*	EventManager::s_NodeFocused;

EventManager::EventManager()
{}

EventManager::~EventManager()
{}

int EventManager::Init()
{
	s_SubscriberCount = 0;
	s_SubscriberList = nullptr;
	return 0;  //SUCCESS
}

void EventManager::UnInit()
{
	s_SubscriberCount = 0;
	s_SubscriberList = nullptr;
}

void EventManager::Subscribe(Node* node)
{
	Node** newList = new Node*[s_SubscriberCount + 1];

	if (s_SubscriberCount != 0)
	{
		for (int i = 0; i < s_SubscriberCount; i++)
		{
			newList[i] = s_SubscriberList[i];
		}
	}
	if (s_SubscriberList != nullptr)
	{
		delete s_SubscriberList;
	}
	newList[s_SubscriberCount] = node;
	s_SubscriberList = newList;
	s_SubscriberCount++;	
}

void EventManager::Broadcast(Message* msg)
{
	switch (msg->type)
	{
	case MSG_UPDATE:
		BroadcastUpdate();
		break;
	case MSG_DRAW:
		BroadcastDraw();
		break;
	case MSG_MOUSEMOTION:
	case MSG_MOUSEBUTTONDOWN:
	case MSG_MOUSEBUTTONUP:
	case MSG_MOUSEWHEEL:
		BroadcastMouse(msg);
		break;
	default:
		//BroadcastObscure(msg);
		break;
	}
}

void EventManager::BroadcastUpdate()
{
	for (int i = 0; i < s_SubscriberCount; i++)
	{
		s_SubscriberList[i]->Update();
	}
}

void EventManager::BroadcastDraw()
{
	Node* root = GameEngine::GetRootNode();

	BroadcastDrawSubNode(root);	
}

void EventManager::BroadcastDrawSubNode(Node* node)
{
	node = node->GetFirstChild();

	while (node != nullptr)
	{
		CanvasNode* canvasNode = dynamic_cast<CanvasNode*>(node);
		if (canvasNode != nullptr)
		{
			if (canvasNode->GetIsVisible())
			{
				//If node is not visible children are hidden as well.
				GraphicsContext* graphics = canvasNode->GetGraphics();
				
				canvasNode->Draw(graphics);
				BroadcastDrawSubNode(node);
			}
		}
		node = node->GetNextSibling();
	}
}

void EventManager::BroadcastMouse(Message* msg)
{
	s_NodeHit = nullptr;
	Node* root = GameEngine::GetRootNode();

	BroadcastMouseSubNode(root, msg);



	if (s_NodeHitPrev != s_NodeHit)
	{
		//Check if mouse being pressed on something
		//if (nodeMouseButtonDown == nullptr)
		{
			if (s_NodeHitPrev != nullptr)
			{
				((ControlNode*)s_NodeHitPrev)->OnMouseLeave(msg);
			}
			if (s_NodeHit != nullptr)
			{
				((ControlNode*)s_NodeHit)->OnMouseMove(msg);
			}
			s_NodeHitPrev = s_NodeHit;
		}
		//else if (nodeMouseButtonDown = nodeHit)
		{

		}
	}

	if (msg->type == MSG_MOUSEBUTTONDOWN)
	{
		if (s_NodeHit != nullptr)
		{
			((ControlNode*)s_NodeHit)->OnMouseDown(msg);
		}
		s_NodeMouseButtonDown = s_NodeHit;
	}
	if (msg->type == MSG_MOUSEBUTTONUP)
	{
		if (s_NodeHit != nullptr)
		{
			((ControlNode*)s_NodeHit)->OnMouseUp(msg);
		}
		s_NodeMouseButtonUp = s_NodeHit;
		
		
		if (s_NodeMouseButtonUp == s_NodeMouseButtonDown)
		{
			if (s_NodeMouseButtonDown != nullptr)
			{
				((ControlNode*)s_NodeMouseButtonDown)->OnMouseClick(msg);
			}
		}
		
		s_NodeMouseButtonDown = nullptr;
		s_NodeMouseButtonUp = nullptr;
	}
}

void EventManager::BroadcastMouseSubNode(Node* node, Message* msg)
{
	node = node->GetFirstChild();

	while (node != nullptr)
	{
		//if (msg->m_Type == MSG_MOUSEMOTION)
		{
			ControlNode* controlNode = dynamic_cast<ControlNode*>(node);
			if (controlNode != nullptr
			&& controlNode->GetIsVisible() == true
			&& controlNode->GetIsEnabled() == true)
			{
				Rectangle rectHitBox = Rectangle(0, 0, controlNode->GetSize()->GetWidth(), controlNode->GetSize()->GetHeight());
				Rectangle* pRectHitBox = &rectHitBox;

				//Perform Local to Global coord transformation
				pRectHitBox = RenderingEngine::ClipToParentRectangle(node, pRectHitBox);

				//Grab mouse coordinates from event
				int mouseX = msg->sdlEvent->motion.x;
				int mouseY = msg->sdlEvent->motion.y;

				//Check if mouse is inside the control (node)
				if (mouseX >= pRectHitBox->GetX()
					&& mouseX <= pRectHitBox->GetX() + pRectHitBox->GetWidth()
					&& mouseY >= pRectHitBox->GetY()
					&& mouseY <= pRectHitBox->GetY() + pRectHitBox->GetHeight())
				{
					s_NodeHit = controlNode;
				}

			}
		}
		BroadcastMouseSubNode(node, msg); //SHOULD WE BROADCAST DOWN EVERY TIME? IT PROBS SHOULD BE DONE IF WE ARE INSIDE THE ORIGINAL NODE
		node = node->GetNextSibling();
	}
}

void EventManager::BroadcastObscure(Message* msg)
{
	for (int i = 0; i < s_SubscriberCount; i++)
	{
		s_SubscriberList[i]->ProcessMessage(msg);
	}
}

void EventManager::Send(Node* node, Message* msg)
{
	if (node != nullptr)
	{
		node->ProcessMessage(msg);
	}
}

void EventManager::GrabFocus(Node* node)
{
	//Defocus previous
	UnFocusTree(s_NodeFocused);
	//Make focused
	FocusTree(node);
	s_NodeFocused = node;
}

void EventManager::UnFocusTree(Node* node)
{
	while (node != nullptr)
	{
		ControlNode* controlNode = dynamic_cast<ControlNode*>(node);
		if (controlNode != nullptr)
		{
			controlNode->SetIsFocused(false);
		}
		node = node->GetParent();
	}
}

void EventManager::FocusTree(Node* node)
{
	while (node != nullptr)
	{
		ControlNode* controlNode = dynamic_cast<ControlNode*>(node);
		if (controlNode != nullptr)
		{
			controlNode->SetIsFocused(true);
		}
		node = node->GetParent();
	}
}
