#pragma once

#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>

#include <iostream>
#include <string>

struct GUtil
{
public:
	static void Log(std::string log)
	{
		//std::cout << log << std::endl;
		OutputDebugStringA(log.c_str());
	}
};
