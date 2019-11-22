#include "./MathHelper.h"

#include "./Vector3.h"
#include "./Quaternion.h"
#include "./Matrix4x4.h"
#include "./Vector4.h"
#include "./Mathf.h"

Vector3 MathHelper::GetPosition(Matrix4x4 m)
{
	//return Vector3(m[0, 3], m[1, 3], m[2, 3]);
	return Vector3(m.m03, m.m13, m.m23);
}

Vector3 MathHelper::GetScale(Matrix4x4 m)
{
	return Vector3(m.GetColumn(0).magnitude(), m.GetColumn(1).magnitude(), m.GetColumn(2).magnitude());
}

Quaternion MathHelper::GetRotation(Matrix4x4 m)
{
	Vector3 s = GetScale(m);

	// Normalize Scale from Matrix4x4
	float m00 = m.m00 / s.x;
	float m01 = m.m01 / s.y;
	float m02 = m.m02 / s.z;
	float m10 = m.m10 / s.x;
	float m11 = m.m11 / s.y;
	float m12 = m.m12 / s.z;
	float m20 = m.m20 / s.x;
	float m21 = m.m21 / s.y;
	float m22 = m.m22 / s.z;

	Quaternion q = Quaternion();
	q.w = Mathf::Sqrt(Mathf::Max((float)0, 1 + m00 + m11 + m22)) / 2;
	q.x = Mathf::Sqrt(Mathf::Max((float)0, 1 + m00 - m11 - m22)) / 2;
	q.y = Mathf::Sqrt(Mathf::Max((float)0, 1 - m00 + m11 - m22)) / 2;
	q.z = Mathf::Sqrt(Mathf::Max((float)0, 1 - m00 - m11 + m22)) / 2;
	q.x *= Mathf::Sign(q.x * (m21 - m12));
	q.y *= Mathf::Sign(q.y * (m02 - m20));
	q.z *= Mathf::Sign(q.z * (m10 - m01));

	// q.Normalize()
	float qMagnitude = Mathf::Sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
	q.w /= qMagnitude;
	q.x /= qMagnitude;
	q.y /= qMagnitude;
	q.z /= qMagnitude;

	return q;
}

float MathHelper::Modulo(float a, int b)
{
	return a - ((int)a / b) * b;
}

float MathHelper::Module2(float a, float b)
{
	return a - ((int)a / b) * b;
}
