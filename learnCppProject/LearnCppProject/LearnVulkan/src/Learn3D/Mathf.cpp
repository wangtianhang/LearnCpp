/*#include "pch.h"*/
#include "../DebugMemory.h"

#include "./Mathf.h"

float Mathf::Deg2Rad = 0.0174533f;
float Mathf::Epsilon = 1.4013e-045f;
float Mathf::Infinity = 1.0f / 0.0f;
float Mathf::NegativeInfinity = -1.0f / 0.0f;
float Mathf::PI = 3.14159f;
float Mathf::Rad2Deg = 57.2958f;

void Mathf::Test()
{
	std::cout << "acos " << Acos(0.5) << std::endl;
}

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

float Mathf::Gamma(float value, float absmax, float gamma)
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

float Mathf::InverseLerp(float from, float to, float value)
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

float Mathf::Lerp(float from, float to, float t)
{
	return from + (to - from) * Mathf::Clamp01(t);
}

float Mathf::LerpAngle(float a, float b, float t)
{
	float num = Mathf::Repeat(b - a, 360);
	if (num > 180)
	{
		num -= 360;
	}
	return a + num * Mathf::Clamp01(t);
}

float Mathf::Log(float f)
{
	return log(f);
}

float Mathf::Log(float f, float p)
{
	return log(f) / log(p);
}

float Mathf::Log10(float f)
{
	return log10(f);
}

float Mathf::Max(float a, float b)
{
	return (a <= b) ? b : a;
}

float Mathf::Max(float values[], int n)
{
	int num = n;
	if (num == 0)
	{
		return 0;
	}
	float num2 = values[0];
	for (int i = 1; i < num; i++)
	{
		if (values[i] > num2)
		{
			num2 = values[i];
		}
	}
	return num2;
}

int Mathf::Max(int a, int b)
{
	return (a <= b) ? b : a;
}

int Mathf::Max(int values[], int n)
{
	int num = n;
	if (num == 0)
	{
		return 0;
	}
	int num2 = values[0];
	for (int i = 1; i < num; i++)
	{
		if (values[i] > num2)
		{
			num2 = values[i];
		}
	}
	return num2;
}

float Mathf::Min(float a, float b)
{
	return (a >= b) ? b : a;
}

float Mathf::Min(float values[], int n)
{
	int num = n;
	if (num == 0)
	{
		return 0;
	}
	float num2 = values[0];
	for (int i = 1; i < num; i++)
	{
		if (values[i] < num2)
		{
			num2 = values[i];
		}
	}
	return num2;
}

int Mathf::Min(int a, int b)
{
	return (a >= b) ? b : a;
}

int Mathf::Min(int values[], int n)
{
	int num = n;
	if (num == 0)
	{
		return 0;
	}
	int num2 = values[0];
	for (int i = 1; i < num; i++)
	{
		if (values[i] < num2)
		{
			num2 = values[i];
		}
	}
	return num2;
}

float Mathf::MoveTowards(float current, float target, float maxDelta)
{
	if (Mathf::Abs(target - current) <= maxDelta)
	{
		return target;
	}
	return current + Mathf::Sign(target - current) * maxDelta;
}

float Mathf::MoveTowardsAngle(float current, float target, float maxDelta)
{
	target = current + Mathf::DeltaAngle(current, target);
	return Mathf::MoveTowards(current, target, maxDelta);
}

float Mathf::PingPong(float t, float length)
{
	t = Mathf::Repeat(t, length * 2);
	return length - Mathf::Abs(t - length);
}

float Mathf::Pow(float f, float p)
{
	return pow(f, p);
}

float Mathf::Repeat(float t, float length)
{
	return t - Mathf::Floor(t / length) * length;
}

float Mathf::Round(float f)
{
	return round(f);
}

int Mathf::RoundToInt(float f)
{
	return (int)round(f);
}

float Mathf::Sign(float f)
{
	return (f < 0) ? (float)-1 : (float)1;
}

float Mathf::Sin(float f)
{
	return sin(f);
}

float Mathf::SmoothDamp(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed, float deltaTime)
{
	smoothTime = Mathf::Max(0.0001f, smoothTime);
	float num = 2 / smoothTime;
	float num2 = num * deltaTime;
	float num3 = 1 / (1 + num2 + 0.48f * num2 * num2 + 0.235f * num2 * num2 * num2);
	float num4 = current - target;
	float num5 = target;
	float num6 = maxSpeed * smoothTime;
	num4 = Mathf::Clamp(num4, -num6, num6);
	target = current - num4;
	float num7 = (currentVelocity + num * num4) * deltaTime;
	currentVelocity = (currentVelocity - num * num7) * num3;
	float num8 = target + (num4 + num7) * num3;
	if (num5 - current > 0 == num8 > num5)
	{
		num8 = num5;
		currentVelocity = (num8 - num5) / deltaTime;
	}
	return num8;
}

float Mathf::SmoothDampAngle(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed, float deltaTime)
{
	target = current + Mathf::DeltaAngle(current, target);
	return Mathf::SmoothDamp(current, target, currentVelocity, smoothTime, maxSpeed, deltaTime);
}

float Mathf::SmoothStep(float from, float to, float t)
{
	t = Mathf::Clamp01(t);
	t = -2 * t * t * t + 3 * t * t;
	return to * t + from * (1 - t);
}

float Mathf::Sqrt(float f)
{
	return sqrt(f);
}

float Mathf::Tan(float f)
{
	return tan(f);
}

int Mathf::ClosestPowerOfTwo(int n)
{
	int v = n;
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;

	int x = v >> 1;
	return (v - n) > (n - x) ? x : v;
}

bool Mathf::IsPowerOfTwo(int n)
{
	if (n <= 0)
	{
		return false;
	}
	else
	{
		return (n & (n - 1)) == 0;
	}
}

