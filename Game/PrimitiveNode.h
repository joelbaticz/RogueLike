#pragma once

#include "CanvasNode.h"

//The parent of Primitive Objects like Shapes, Text, Sprites
class PrimitiveNode : public CanvasNode
{
public:
	PrimitiveNode();
	~PrimitiveNode();
};