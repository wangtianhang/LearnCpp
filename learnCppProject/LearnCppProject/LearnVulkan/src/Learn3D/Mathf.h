#pragma once

#include <iostream>
#include <cmath>

struct Mathf
{
public:
	static float Deg2Rad;
	static float Epsilon;
	static float Infinity;
	static float NegativeInfinity;
	static float PI;
	static float Rad2Deg;

	static void Test()
	{
		std::cout << "acos " << Acos(0.5) << std::endl;
	}

	static float Abs(float f);

	static int Abs(int value);

	static float Acos(float f);

	static bool Approximately(float a, float b);

	static float Asin(float f);

	static float Atan(float f);

	static float Atan2(float y, float x);

	static float Ceil(float f);

	static int CeilToInt(float f);

	static float Clamp(float value, float min, float max);

	static double Clamp(double value, double min, double max);

	static int Clamp(int value, int min, int max);

	static float Clamp01(float value);

	static double Clamp01(double value);

	static float Cos(float f);

	static float DeltaAngle(float current, float target);

	static float Exp(float power);

	static float Floor(float f);

	static int FloorToInt(float f);

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

	static float Log(float f, float p)
	{
		return log(f) / log(p);
	}

	static float Log10(float f)
	{
		return log10(f);
	}

	static float Max(float a, float b)
	{
		return (a <= b) ? b : a;
	}

	static float Max(float values[], int n)
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

	static int Max(int a, int b)
	{
		return (a <= b) ? b : a;
	}

	static int Max(int values[], int n)
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

	static float Min(float a, float b)
	{
		return (a >= b) ? b : a;
	}

	static float Min(float values[], int n)
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

	static int Min(int a, int b)
	{
		return (a >= b) ? b : a;
	}

	static int Min(int values[], int n)
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

	static float MoveTowards(float current, float target, float maxDelta)
	{
		if (Mathf::Abs(target - current) <= maxDelta)
		{
			return target;
		}
		return current + Mathf::Sign(target - current) * maxDelta;
	}

	static float MoveTowardsAngle(float current, float target, float maxDelta)
	{
		target = current + Mathf::DeltaAngle(current, target);
		return Mathf::MoveTowards(current, target, maxDelta);
	}

	static float PingPong(float t, float length)
	{
		t = Mathf::Repeat(t, length * 2);
		return length - Mathf::Abs(t - length);
	}

	static float Pow(float f, float p)
	{
		return pow(f, p);
	}

	static float Repeat(float t, float length)
	{
		return t - Mathf::Floor(t / length) * length;
	}

	static float Round(float f)
	{
		return round(f);
	}

	static int RoundToInt(float f)
	{
		return (int)round(f);
	}

	static float Sign(float f)
	{
		return (f < 0) ? (float)-1 : (float)1;
	}

	static float Sin(float f)
	{
		return sin(f);
	}

	static float SmoothDamp(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed, float deltaTime)
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

	static float SmoothDampAngle(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed, float deltaTime)
	{
		target = current + Mathf::DeltaAngle(current, target);
		return Mathf::SmoothDamp(current, target, currentVelocity, smoothTime, maxSpeed, deltaTime);
	}

	static float SmoothStep(float from, float to, float t)
	{
		t = Mathf::Clamp01(t);
		t = -2 * t * t * t + 3 * t * t;
		return to * t + from * (1 - t);
	}

	static float Sqrt(float f)
	{
		return sqrt(f);
	}

	static float Tan(float f)
	{
		return tan(f);
	}

	static int ClosestPowerOfTwo(int n)
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

	static bool IsPowerOfTwo(int n)
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






};