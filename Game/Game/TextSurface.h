#pragma once

#include <string>
#include "Font.h"

class TextSuface
{
	std::string		m_Text; //the text that was rendered
	Font*			m_Font;
	Rect*			m_Rect; //this rect contains the width and height of the text
							//and the last x, y position that the renderer used
};