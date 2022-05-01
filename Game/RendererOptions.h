#pragma once

enum RendererType
{
	Software = 1,
	SDL = 2,
	OpenGL = 3
};

class RendererOptions
{
public:
	std::string windowTitle;
	bool windowIsFullScreen;
	int windowX;
	int windowY;
	int windowWidth;
	int windowHeight;
	int colorDepthBits;
	int refreshRate;

	RendererType rendererType;
};
