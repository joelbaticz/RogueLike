#pragma once

class DrawMode
{
public:
	enum DrawModeValue
	{
		Points = 1 << 0, // 1
		Lines = 1 << 1, // 2
		Filled = 1 << 2, // 4
		Textured = 1 << 3  // 8
	};

	DrawModeValue value;

	DrawMode(DrawModeValue value)
	{
		this->value = value;
	}

	bool HasFlag(DrawModeValue flag)
	{
		if ((this->value & flag) == flag)
		{
			return true;
		}

		return false;
	}
};


