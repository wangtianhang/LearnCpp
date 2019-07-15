#pragma once

#include <iostream>
#include <cmath>

struct Mathf
{
public:
	static void Test()
	{
		std::cout << "acos " << Acos(0.5) << std::endl;
	}

	static float Abs(float f)
	{
		return abs(f);
	}

	static int Abs(int value)
	{
		return abs(value);
	}

	static float Acos(float f)
	{
		return acos(f);
	}
};