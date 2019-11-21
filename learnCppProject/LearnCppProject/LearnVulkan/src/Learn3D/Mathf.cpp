/*#include "pch.h"*/
#include "../DebugMemory.h"

#include "./Mathf.h"

float Mathf::Deg2Rad = 0.0174533f;
float Mathf::Epsilon = 1.4013e-045f;
float Mathf::Infinity = 1.0f / 0.0f;
float Mathf::NegativeInfinity = -1.0f / 0.0f;
float Mathf::PI = 3.14159f;
float Mathf::Rad2Deg = 57.2958f;

float Mathf::Abs(float f)
{
	return abs(f);
}

int Mathf::Abs(int value)
{
	return abs(value);
}

float Mathf::Acos(float f)
{
	return acos(f);
}

bool Mathf::Approximately(float a, float b)
{
	return Mathf::Abs(b - a) < Mathf::Max(1E-06f * Mathf::Max(Mathf::Abs(a), Mathf::Abs(b)), 1.121039E-44f);
}

float Mathf::Asin(float f)
{
	return asin(f);
}

float Mathf::Atan(float f)
{
	return atan(f);
}

float Mathf::Atan2(float y, float x)
{
	return atan2(y, x);
}

float Mathf::Ceil(float f)
{
	return ceil(f);
}

int Mathf::CeilToInt(float f)
{
	return (int)ceil(f);
}

float Mathf::Clamp(float value, float min, float max)
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

double Mathf::Clamp(double value, double min, double max)
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

int Mathf::Clamp(int value, int min, int max)
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

float Mathf::Clamp01(float value)
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

double Mathf::Clamp01(double value)
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

float Mathf::Cos(float f)
{
	return cos(f);
}

float Mathf::DeltaAngle(float current, float target)
{
	float num = Mathf::Repeat(target - current, 360);
	if (num > 180)
	{
		num -= 360;
	}
	return num;
}

float Mathf::Exp(float power)
{
	return exp(power);
}

float Mathf::Floor(float f)
{
	return floor(f);
}

int Mathf::FloorToInt(float f)
{
	return (int)floor(f);
}

