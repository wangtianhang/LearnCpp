#pragma once


#include <exception>

#include "./Mathf.h"

struct Vector4
{
public:
	static void Test()
	{

	}

	float x;
	float y;
	float z;
	float w;

	Vector4()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
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
		case 3:
			return w;
		default:
			throw std::exception("vector4 no index");
			break;
		}
	}

	Vector4 normalized()
	{
		Vector4::Normalize(*this);
	}

	float magnitude()
	{
		return Mathf::Sqrt(Vector4::Dot(*this, *this));
	}

	float sqrMagnitude()
	{
		return Vector4::Dot(*this, *this);
	}

	static Vector4 zero()
	{
		return Vector4(0, 0, 0, 0);
	}

	static Vector4 one()
	{
		return Vector4(1, 1, 1, 1);
	}

	Vector4(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Vector4(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = 0;
	}

	Vector4(float x, float y)
	{
		this->x = x;
		this->y = y;
		this->z = 0;
		this->w = 0;
	}

	void Set(float new_x, float new_y, float new_z, float new_w)
	{
		x = new_x;
		y = new_y;
		z = new_z;
		w = new_w;
	}

	static Vector4 Lerp(Vector4 from, Vector4 to, float t)
	{
		t = Mathf::Clamp01(t);
		return Vector4(from.x + (to.x - from.x) * t, from.y + (to.y - from.y) * t, from.z + (to.z - from.z) * t, from.w + (to.w - from.w) * t);
	}

	static Vector4 MoveTowards(Vector4 current, Vector4 target, float maxDistanceDelta)
	{
		Vector4 a = target - current;
		float magnitude = a.magnitude();
		if (magnitude <= maxDistanceDelta || magnitude == 0)
		{
			return target;
		}
		return current + a / magnitude * maxDistanceDelta;
	}

	static Vector4 Scale(Vector4 a, Vector4 b)
	{
		return Vector4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
	}

	void Scale(Vector4 scale)
	{
		x *= scale.x;
		y *= scale.y;
		z *= scale.z;
		w *= scale.w;
	}

	static Vector4 Normalize(Vector4 a)
	{
		float num = Vector4::Magnitude(a);
		if (num > 1E-05f)
		{
			return a / num;
		}
		return Vector4::zero();
	}

	void Normalize()
	{
		float num = Vector4::Magnitude(*this);
		if (num > 1E-05f)
		{
			*this = *this / num;
		}
		else
		{
			*this = Vector4::zero();
		}
	}

	static float Dot(Vector4 a, Vector4 b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	static Vector4 Project(Vector4 a, Vector4 b)
	{
		return b * Vector4::Dot(a, b) / Vector4::Dot(b, b);
	}

	static float Distance(Vector4 a, Vector4 b)
	{
		return Vector4::Magnitude(a - b);
	}

	static float Magnitude(Vector4 a)
	{
		return Mathf::Sqrt(Vector4::Dot(a, a));
	}

	static float SqrMagnitude(Vector4 a)
	{
		return Vector4::Dot(a, a);
	}

	float SqrMagnitude()
	{
		return Vector4::Dot(*this, *this);
	}

	static Vector4 Min(Vector4 lhs, Vector4 rhs)
	{
		return Vector4(Mathf::Min(lhs.x, rhs.x), Mathf::Min(lhs.y, rhs.y), Mathf::Min(lhs.z, rhs.z), Mathf::Min(lhs.w, rhs.w));
	}

	static Vector4 Max(Vector4 lhs, Vector4 rhs)
	{
		return Vector4(Mathf::Max(lhs.x, rhs.x), Mathf::Max(lhs.y, rhs.y), Mathf::Max(lhs.z, rhs.z), Mathf::Max(lhs.w, rhs.w));
	}

	Vector4 operator+(const Vector4 & b) const
	{
		Vector4 ret = Vector4();
		ret.x = this->x + b.x;
		ret.y = this->y + b.y;
		ret.z = this->z + b.z;
		ret.w = this->w + b.w;
		return ret;
	}

	Vector4 operator-(const Vector4 & b) const
	{
		Vector4 ret = Vector4();
		ret.x = this->x - b.x;
		ret.y = this->y - b.y;
		ret.z = this->z - b.z;
		ret.w = this->w - b.w;
		return ret;
	}

	Vector4 operator-() const
	{
		Vector4 ret = Vector4();
		ret.x = -this->x;
		ret.y = -this->y;
		ret.z = -this->z;
		ret.w = -this->w;
		return ret;
	}

	Vector4 operator *(float d) const
	{
		Vector4 ret = Vector4();
		ret.x = this->x * d;
		ret.y = this->y * d;
		ret.z = this->z * d;
		ret.w = this->w * d;
		return ret;
	}

	Vector4 operator /(float d) const
	{
		Vector4 ret = Vector4();
		ret.x = this->x / d;
		ret.y = this->y / d;
		ret.z = this->z / d;
		ret.w = this->w / d;
		return ret;
	}

	bool operator == (const Vector4 & b) const
	{
		return this->x == b.x
			&& this->y == b.y
			&& this->z == b.z
			&& this->w == b.w;
	}

	bool operator != (const Vector4 & b) const
	{
		return this->x != b.x
			|| this->y != b.y
			|| this->z != b.z
			|| this->z != b.z;
	}

	friend Vector4 operator *(const float d, Vector4 & b);
};