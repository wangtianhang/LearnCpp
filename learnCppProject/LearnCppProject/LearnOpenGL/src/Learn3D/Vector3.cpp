
/*#include "pch.h"*/

#include "Vector3.h"

// Vector3 operator*(const float d, Vector3 & b)
// {
// 	Vector3 ret = Vector3();
// 	ret.x = b.x * d;
// 	ret.y = b.y * d;
// 	ret.z = b.z * d;
// 	return ret;
// }

Vector3 operator*(const float d, Vector3 b)
{
	Vector3 ret = Vector3();
	ret.x = b.x * d;
	ret.y = b.y * d;
	ret.z = b.z * d;
	return ret;
}

