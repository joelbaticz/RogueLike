#include "ControlNode.h"
#include "RenderingEngine.h"
#include "EventManager.h"

ControlNode::ControlNode(std::string name) : CanvasNode(name)
{
	LogEngine::Log(LOG_TRACE, "ControlNode", "Constructor called.");

	isEnabled = true;
	isHover = false;
	isPressed = false;
	
	//m_MinSize = nullptr;
	//m_MaxSize = nullptr;
	//m_Anchor = AnchorNone;
	//m_Margin = 0;

}

ControlNode::~ControlNode()
{
	LogEngine::Log(LOG_TRACE, "ControlNode", "Destructor called.");
}

bool ControlNode::GetIsEnabled()
{
	return isEnabled;
}

void ControlNode::SetIsEnabled(bool value)
{
	isEnabled = value;
}

bool ControlNode::GetIsHover()
{
	return isHover;
}

void ControlNode::SetIsHover(bool value)
{
	isHover = value;
}

bool ControlNode::GetIsPressed()
{
	return isPressed;
}

void ControlNode::SetIsPressed(bool value)
{
	isPressed = value;
}

bool ControlNode::GetIsFocused()
{
	return isFocused;
}

void ControlNode::SetIsFocused(bool value)
{
	isFocused = value;
}

void ControlNode::ProcessMessage(Message* msg)
{
	return;



	//NOT BEING USED!!!




	bool isMessageConsumed = false;

	//Do not process, neighter children if not visible
	if (this->GetIsVisible() == false) return;
	//Do not process, neighter children if not enabled
	if (this->GetIsEnabled() == false) return;

	//if (msg->m_Type == MSG_MOUSEINPUT)
	{
		//CREATE HITBOX FOR CHECKING

		//Create Zero-based (local) coordinate hitbox
		Rectangle rectHitBox = Rectangle(0, 0, this->GetSize()->GetWidth(), this->GetSize()->GetHeight());
		Rectangle* pRectHitBox = &rectHitBox;
		
		//Perform Local to Global coord transformation
		pRectHitBox = RenderingEngine::ClipToParentRectangle(this, pRectHitBox);

		if (msg->sdlEvent->type == SDL_MOUSEMOTION)
		{
			//Grab mouse coordinates from event
			int mouseX = msg->sdlEvent->motion.x;
			int mouseY = msg->sdlEvent->motion.y;

			//Actual HitBox check
			if (isHover)
			{
				//OnMouseEnter message was already sent
				//Check if mouse is outside
				if (mouseX < pRectHitBox->GetX()
					|| mouseX > pRectHitBox->GetX() + pRectHitBox->GetWidth()
					|| mouseY < pRectHitBox->GetY()
					|| mouseY > pRectHitBox->GetY() + pRectHitBox->GetHeight())
				{
					//Mouse found to be outside of HitBox
					isHover = false;

					//Create new message type with same data 
					Message newMsg = Message();
					Message* pNewMsg = &newMsg;
					pNewMsg->type = MSG_MOUSELEAVE;
					pNewMsg->sdlEvent = msg->sdlEvent;
					this->OnMouseLeave(pNewMsg);
					//delete newMsg;

					
				}
				else
				{
					//Do nothing (mouse is still inside the control, MouseEnter was already sent)
				}
			}
			else
			{
				//OnMouseEnter was not sent yet. Shall we send it?
				if (mouseX >= pRectHitBox->GetX()
					&& mouseX <= pRectHitBox->GetX() + pRectHitBox->GetWidth()
					&& mouseY >= pRectHitBox->GetY()
					&& mouseY <= pRectHitBox->GetY() + pRectHitBox->GetHeight())
				{
					//HitBox test positive -> send OnMouseEnter
					isHover = true;

					//Mouse found to be inside of HitBox
					//Create new message type with same data 

					Message newMsg = Message();
					Message* pNewMsg = &newMsg;
					pNewMsg->type = MSG_MOUSEENTER;
					pNewMsg->sdlEvent = msg->sdlEvent;
					this->OnMouseEnter(pNewMsg);
					//delete newMsg;

					
				}
				else
				{
					//Do nothing (mouse is still OUTSIDE of the control
				}
			}
		}
		else if (msg->sdlEvent->type == SDL_MOUSEBUTTONDOWN)
		{
			//Grab mouse coordinates from event
			int mouseX = msg->sdlEvent->motion.x;
			int mouseY = msg->sdlEvent->motion.y;

			//Actual HitBox check
			if (isHover)
			{
				//Mouse is already atop of control
				if (!isPressed)
				{
					//Pressed signal was not sent yet
					isPressed = true;
					
					Message newMsg = Message();
					Message* pNewMsg = &newMsg;
					pNewMsg->type = MSG_MOUSEBUTTONDOWN;
					pNewMsg->sdlEvent = msg->sdlEvent;
					this->OnMouseDown(pNewMsg);
					//delete newMsg;

					
				}
				else
				{
					//Signal was already sent (do nothing)
				}
			}
			else
			{
					//Do nothing (mouse is outside of the control
			}
		}
		else if (msg->sdlEvent->type == SDL_MOUSEBUTTONUP)
		{
			//Grab mouse coordinates from event
			int mouseX = msg->sdlEvent->motion.x;
			int mouseY = msg->sdlEvent->motion.y;

			//Actual HitBox check
			if (isHover)
			{
				//Mouse is already atop of control
				if (isPressed)
				{
					//Pressed signal was already sent: send Up singal
					isPressed = false;

					Message newMsg = Message();
					Message* pNewMsg = &newMsg;
					pNewMsg->type = MSG_MOUSEBUTTONUP;
					pNewMsg->sdlEvent = msg->sdlEvent;
					this->OnMouseUp(pNewMsg);
					//delete newMsg;

					//Actually that's a click

					Message newMsg2 = Message();
					Message* pNewMsg2 = &newMsg2;
					pNewMsg2->type = MSG_MOUSECLICK;
					pNewMsg2->sdlEvent = msg->sdlEvent;
					this->OnMouseClick(pNewMsg2);
					//delete newMsg2;
				
				}
				else
				{
					//Signal was already sent (do nothing)
				}
			}
			else
			{
				//Mouse is outside of the control
				isPressed = false;

				Message newMsg = Message();
				Message* pNewMsg = &newMsg;
				pNewMsg->type = MSG_MOUSEBUTTONUP;
				pNewMsg->sdlEvent = msg->sdlEvent;
				this->OnMouseUp(pNewMsg);
				//delete newMsg;
			}
		}
		//delete rectHitBox;

		////Bubble Down
		//Node* node = this->GetFirstChild();
		//while (node != nullptr)
		//{
		//	if (dynamic_cast<ControlNode*>(node))
		//	{
		//		((ControlNode*)node)->Draw();
		//	}
		//	node = node->GetNextSibling();
		//}
		////Message was bubbled down
		//return;
	}

	////Bubble Down
	//Node* node = this->GetFirstChild();
	//while (node != nullptr)
	//{
	//	//if (dynamic_cast<ControlNode*>(node))
	//	//{
	//		//((ControlNode*)node)->Draw();
	//	//}
	//	node->ProcessMessage(msg);
	//	node = node->GetNextSibling();
	//}
	//Message was bubbled down
	//return;

	//Bubble up: Dispatch message to CanvasNode's ProcessMessage
	//CanvasNode::ProcessMessage(msg);
}

void ControlNode::OnMouseMove(Message* msg)
{
	if (!isHover)
	{
		this->OnMouseEnter(msg);
	}
}

void ControlNode::OnMouseEnter(Message* msg)
{
	this->SetIsHover(true);
}

void ControlNode::OnMouseLeave(Message* msg)
{
	this->SetIsHover(false);
	this->SetIsPressed(false);
}

void ControlNode::OnMouseDown(Message* msg)
{
	this->BringToFront();
	EventManager::GrabFocus(this);
	this->SetIsPressed(true);
	this->SetIsFocused(true);
}

void ControlNode::OnMouseUp(Message* msg)
{
	this->SetIsPressed(false);
}

void ControlNode::OnMouseClick(Message* msg)
{
	this->SetIsFocused(true);	
}

void ControlNode::Draw(GraphicsContext* g)
{
	LogEngine::Log(LOG_DEBUG, "ControlNode", "Draw() called on " + this->GetName());

	if (GetIsVisible())
	{
		//Color* fillColor = AssetManager::CreateColor(80, 0, 0, 80);
		//RenderingEngine::SetFillColor(fillColor);
		//RenderingEngine::DrawRectangle(this, 0, 0, this->GetSize()->GetWidth(), this->GetSize()->GetHeight());
	}

	//Don't bubble upwards
	//CanvasNode::Draw(g);
}

