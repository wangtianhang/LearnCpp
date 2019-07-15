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

	static float DeltaAngle(float current, float target)
	{
		float num = Mathf::Repeat(target - current, 360);
		if (num > 180)
		{
			num -= 360;
		}
		return num;
	}

	static float Exp(float power)
	{
		return exp(power);
	}

	static float Floor(float f)
	{
		return floor(f);
	}

	static int FloorToInt(float f)
	{
		return (int)floor(f);
	}

	static float Gamma(float value, float absmax, float gamma)
	{
		bool flag = false;
		if (value < 0)
		{
			flag = true;
		}
		float num = Mathf::Abs(value);
		if (num > absmax)
		{
			return (!flag) ? num : (-num);
		}
		float num2 = Mathf::Pow(num / absmax, gamma) * absmax;
		return (!flag) ? num2 : (-num2);
	}

	static float InverseLerp(float from, float to, float value)
	{
		if (from < to)
		{
			if (value < from)
			{
				return 0;
			}
			if (value > to)
			{
				return 1;
			}
			value -= from;
			value /= to - from;
			return value;
		}
		else
		{
			if (from <= to)
			{
				return 0;
			}
			if (value < to)
			{
				return 1;
			}
			if (value > from)
			{
				return 0;
			}
			return 1 - (value - to) / (from - to);
		}
	}

	static float Lerp(float from, float to, float t)
	{
		return from + (to - from) * Mathf::Clamp01(t);
	}

	static float LerpAngle(float a, float b, float t)
	{
		float num = Mathf::Repeat(b - a, 360);
		if (num > 180)
		{
			num -= 360;
		}
		return a + num * Mathf::Clamp01(t);
	}

	static float Log(float f)
	{
		return log(f);
	}

	static float Pow(float f, float p)
	{
		return pow(f, p);
	}

	static float Repeat(float t, float length)
	{
		return t - Mathf::Floor(t / length) * length;
	}

	static float Max(float a, float b)
	{
		return (a <= b) ? b : a;
	}
};