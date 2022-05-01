#pragma once
#include "Renderer.h"
#include "RendererOptions.h"

class RendererFactory
{
private:
	RendererOptions* rendererOptions;
public:
	RendererFactory();
	~RendererFactory();
	Renderer* CreateRenderer(RendererOptions* rendererOptions);
};
