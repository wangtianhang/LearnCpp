#pragma once

#include "./Mathf.h"

struct Vector3
{
public:
	static void Test()
	{
		Vector3 a = Vector3(1, 0, 0);
		Vector3 b = Vector3(1, 0, 0);
		Vector3 c = a + b;
		Vector3 d = (a + b) + c;

		d = -d;

		Vector3 e = c * 2;
		Vector3 f = 2 * c;
		if (e == f)
		{

		}

		e[0] = 3;
	}

	float x;
	float y;
	float z;

	Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3(float x, float y)
	{
		this->x = x;
		this->y = y;
		this->z = 0;
	}

	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3 operator-() const
	{
		Vector3 ret = Vector3();
		ret.x = -this->x;
		ret.y = -this->y;
		ret.z = -this->z;
		return ret;
	}

	Vector3 operator+(const Vector3 & b) const
	{
		Vector3 ret = Vector3();
		ret.x = this->x + b.x;
		ret.y = this->y + b.y;
		ret.z = this->z + b.z;
		return ret;
	}

	Vector3 operator-(const Vector3 & b) const
	{
		Vector3 ret = Vector3();
		ret.x = this->x - b.x;
		ret.y = this->y - b.y;
		ret.z = this->z - b.z;
		return ret;
	}

	Vector3 operator *(float d) const
	{
		Vector3 ret = Vector3();
		ret.x = this->x * d;
		ret.y = this->y * d;
		ret.z = this->z * d;
		return ret;
	}

	Vector3 operator /(float d) const
	{
		Vector3 ret = Vector3();
		ret.x = this->x / d;
		ret.y = this->y / d;
		ret.z = this->z / d;
		return ret;
	}

	bool operator == (const Vector3 & b) const
	{
		return this->x == b.x
			&& this->y == b.y
			&& this->z == b.z;
	}

	bool operator != (const Vector3 & b) const
	{
		return this->x != b.x
			|| this->y != b.y
			|| this->z != b.z;
	}

	static Vector3 back()
	{
		return Vector3(0, 0, -1);
	}

	static Vector3 forward()
	{
		return Vector3(0, 0, +1);
	}

	static Vector3 up()
	{
		return Vector3(0, 1, 0);
	}

	static Vector3 down()
	{
		return Vector3(0, -1, 0);
	}

	static Vector3 right()
	{
		return Vector3(1, 0, 0);
	}

	static Vector3 left()
	{
		return Vector3(-1, 0, 0);
	}

	static Vector3 zero()
	{
		return Vector3(0, 0, 0);
	}

	static Vector3 one()
	{
		return Vector3(1, 1, 1);
	}

	float magnitude()
	{
		return Mathf::Sqrt(sqrMagnitude());
	}

	float sqrMagnitude()
	{
		return x * x + y * y + z * z;
	}

	Vector3 normalized()
	{
		return Vector3::Normalize(*this);
	}

	float& operator[](int i)
	{
		switch (i)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			throw std::exception("vector3 no index");
			break;
		}
	}

	static float Angle(Vector3 from, Vector3 to)
	{
		return Mathf::Acos(Mathf::Clamp(Vector3::Dot(from.normalized(), to.normalized()), (float)-1, (float)1)) * 57.29578f;
	}

	static Vector3 ClampMagnitude(Vector3 vector, float maxLength)
	{
		if (vector.sqrMagnitude() > maxLength * maxLength)
		{
			return vector.normalized() * maxLength;
		}
		return vector;
	}

	static Vector3 Cross(Vector3 lhs, Vector3 rhs)
	{
		return Vector3(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x);
	}

	static float Distance(Vector3 a, Vector3 b)
	{
		Vector3 vector = Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
		return Mathf::Sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	}

	static float Dot(Vector3 lhs, Vector3 rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	static Vector3 Lerp(Vector3 from, Vector3 to, float t)
	{
		t = Mathf::Clamp01(t);
		return Vector3(from.x + (to.x - from.x) * t, from.y + (to.y - from.y) * t, from.z + (to.z - from.z) * t);
	}

	static float Magnitude(Vector3 a)
	{
		return Mathf::Sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	}

	static Vector3 Max(Vector3 lhs, Vector3 rhs)
	{
		return Vector3(Mathf::Max(lhs.x, rhs.x), Mathf::Max(lhs.y, rhs.y), Mathf::Max(lhs.z, rhs.z));
	}

	static Vector3 Min(Vector3 lhs, Vector3 rhs)
	{
		return Vector3(Mathf::Min(lhs.x, rhs.x), Mathf::Min(lhs.y, rhs.y), Mathf::Min(lhs.z, rhs.z));
	}



















	static Vector3 Normalize(Vector3 value)
	{
		float num = Vector3::Magnitude(value);
		if (num > 1E-05f)
		{
			return value / num;
		}
		return Vector3::zero();
	}

	friend Vector3 operator *(const float d, Vector3 & b);
};

Vector3 operator *(const float d, Vector3 & b);