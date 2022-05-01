#include "Singleton.h"

//Declare instance as non existing
Singleton* Singleton::instance = nullptr;

//Private constructor - hidden from usage
Singleton::Singleton()
{}

//Acquire the singleton instance
Singleton* Singleton::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Singleton();
	}

	return instance;
}

