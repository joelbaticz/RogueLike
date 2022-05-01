#include "RendererFactory.h"
#include "RendererSoftware8Bits.h"
#include "RendererSoftware16Bits.h"
#include "RendererSoftware32Bits.h"
#include "RendererHardwareSDL.h"

RendererFactory::RendererFactory() = default;
RendererFactory::~RendererFactory() = default;

Renderer* RendererFactory::CreateRenderer(RendererOptions* rendererOptions)
{
	if (rendererOptions->rendererType == RendererType::Software)
	{
		if (rendererOptions->colorDepthBits == 8)
		{
			return new RendererSoftware8Bits(rendererOptions);
		}
		else if (rendererOptions->colorDepthBits == 16)
		{
			return new RendererSoftware16Bits(rendererOptions);
		}
		else if (rendererOptions->colorDepthBits == 32)
		{
			return new RendererSoftware32Bits(rendererOptions);
		}
	}
	else if (rendererOptions->rendererType == RendererType::SDL)
	{
		if (rendererOptions->colorDepthBits == 32)
		{
			return new RendererHardwareSDL(rendererOptions);
		}
	}

	return nullptr;
}
