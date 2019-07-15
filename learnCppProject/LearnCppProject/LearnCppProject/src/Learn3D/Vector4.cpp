#include "pch.h"

#include "./Vector4.h"

Vector4 operator*(const float d, Vector4 & b)
{
	Vector4 ret = Vector4();
	ret.x = b.x * d;
	ret.y = b.y * d;
	ret.z = b.z * d;
	ret.w = b.w * d;
	return ret;
}