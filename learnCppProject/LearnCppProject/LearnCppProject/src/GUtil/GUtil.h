#pragma once

#include <iostream>
#include <string>

struct GUtil
{
public:
	static void Log(std::string log)
	{
		std::cout << log << std::endl;
	}
};
