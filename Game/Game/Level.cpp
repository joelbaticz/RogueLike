#include "Level.h"

Level::Level()
{
	listCubes.push_back(new Cube(Math::Vec4(0, 0, 0), 30));

	listCubes.push_back(new Cube(Math::Vec4(-50, -50, -50), 20));

	listCubes.push_back(new Cube(Math::Vec4(+50, +50, +50), 40));
}

Level::~Level()
{

}
