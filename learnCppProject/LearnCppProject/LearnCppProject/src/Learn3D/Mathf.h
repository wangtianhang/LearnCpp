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

	static bool Approximately(float a, float b)
	{
		return Mathf::Abs(b - a) < Mathf::Max(1E-06f * Mathf::Max(Mathf::Abs(a), Mathf::Abs(b)), 1.121039E-44f);
	}

	static float Asin(float f)
	{
		return asin(f);
	}

	static float Atan(float f)
	{
		return atan(f);
	}

	static float Atan2(float y, float x)
	{
		return atan2(y, x);
	}











	static float Max(float a, float b)
	{
		return (a <= b) ? b : a;
	}
};