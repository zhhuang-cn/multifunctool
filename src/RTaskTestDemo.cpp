#include "RTaskTestDemo.h"



RTaskTestDemo::RTaskTestDemo()
{
}


RTaskTestDemo::~RTaskTestDemo()
{
}

void RTaskTestDemo::Parse(const std::string msg)
{
	std::cout << "Handle Something -> "<<msg << std::endl;
}

void RTaskTestDemo::ReadHandler(const std::string msg)
{
	std::cout << "demo recv -> " << msg << std::endl;
}
