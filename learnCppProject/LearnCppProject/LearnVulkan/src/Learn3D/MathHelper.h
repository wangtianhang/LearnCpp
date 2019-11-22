#pragma once

// #include "./Vector3.h"
// #include "./Quaternion.h"
// #include "./Matrix4x4.h"
// #include "./Mathf.h"

struct Vector3;
struct Quaternion;
struct Matrix4x4;
struct MathHelper
{
public:
	static Vector3 GetPosition(Matrix4x4 m);

	static Vector3 GetScale(Matrix4x4 m);

	static Quaternion GetRotation(Matrix4x4 m);

	static float Modulo(float a, int b);

	static float Module2(float a, float b);
};