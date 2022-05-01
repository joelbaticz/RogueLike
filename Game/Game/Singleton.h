#pragma once

class Singleton
{
	//Stored instance
	static Singleton* instance;

	//Private constructor to prevent instancing
	Singleton();

public:

	static Singleton* getInstance();
};