#pragma once

//#include <iostream>
//#include <cmath>

struct Mathf
{
public:
	static float Deg2Rad;
	static float Epsilon;
	static float Infinity;
	static float NegativeInfinity;
	static float PI;
	static float Rad2Deg;

	static void Test();

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

	static float Gamma(float value, float absmax, float gamma);

	static float InverseLerp(float from, float to, float value);

	static float Lerp(float from, float to, float t);

	static float LerpAngle(float a, float b, float t);

	static float Log(float f);

	static float Log(float f, float p);

	static float Log10(float f);

	static float Max(float a, float b);

	static float Max(float values[], int n);

	static int Max(int a, int b);

	static int Max(int values[], int n);

	static float Min(float a, float b);

	static float Min(float values[], int n);

	static int Min(int a, int b);

	static int Min(int values[], int n);

	static float MoveTowards(float current, float target, float maxDelta);

	static float MoveTowardsAngle(float current, float target, float maxDelta);

	static float PingPong(float t, float length);

	static float Pow(float f, float p);

	static float Repeat(float t, float length);

	static float Round(float f);

	static int RoundToInt(float f);

	static float Sign(float f);

	static float Sin(float f);

	static float SmoothDamp(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed, float deltaTime);

	static float SmoothDampAngle(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed, float deltaTime);

	static float SmoothStep(float from, float to, float t);

	static float Sqrt(float f);

	static float Tan(float f);

	static int ClosestPowerOfTwo(int n);

	static bool IsPowerOfTwo(int n);






};