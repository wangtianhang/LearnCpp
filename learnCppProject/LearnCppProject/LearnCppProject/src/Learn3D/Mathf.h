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

	static float Ceil(float f)
	{
		return ceil(f);
	}

	static int CeilToInt(float f)
	{
		return (int)ceil(f);
	}

	static float Clamp(float value, float min, float max)
	{
		if (value < min)
		{
			value = min;
		}
		else if (value > max)
		{
			value = max;
		}
		return value;
	}

	static double Clamp(double value, double min, double max)
	{
		if (value < min)
		{
			value = min;
		}
		else if (value > max)
		{
			value = max;
		}
		return value;
	}

	static int Clamp(int value, int min, int max)
	{
		if (value < min)
		{
			value = min;
		}
		else if (value > max)
		{
			value = max;
		}
		return value;
	}

	static float Clamp01(float value)
	{
		if (value < 0)
		{
			return 0;
		}
		if (value > 1)
		{
			return 1;
		}
		return value;
	}

	static double Clamp01(double value)
	{
		if (value < 0)
		{
			return 0;
		}
		if (value > 1)
		{
			return 1;
		}
		return value;
	}

	static float Cos(float f)
	{
		return cos(f);
	}

	static float Max(float a, float b)
	{
		return (a <= b) ? b : a;
	}
};