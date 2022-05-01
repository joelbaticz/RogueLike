#pragma once
#include <vector>
#include "Cube.h"

class Level
{
public:
	std::vector<Cube*> listCubes;

	Level();
	~Level();

	void LoadLevelFromFile();
};
