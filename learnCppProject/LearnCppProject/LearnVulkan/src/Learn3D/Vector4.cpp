/*#include "pch.h"*/

#include "../DebugMemory.h"

#include <exception>

#include "./Mathf.h"
#include "./Vector4.h"

Vector4 operator*(const float d, Vector4 b)
{
	Vector4 ret = Vector4();
	ret.x = b.x * d;
	ret.y = b.y * d;
	ret.z = b.z * d;
	ret.w = b.w * d;
	return ret;
}

void Vector4::Test()
{

}

Vector4::Vector4()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4::Vector4(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = 0;
}

Vector4::Vector4(float x, float y)
{
	this->x = x;
	this->y = y;
	this->z = 0;
	this->w = 0;
}

void Vector4::Set(float new_x, float new_y, float new_z, float new_w)
{
	x = new_x;
	y = new_y;
	z = new_z;
	w = new_w;
}

Vector4 Vector4::Lerp(Vector4 from, Vector4 to, float t)
{
	t = Mathf::Clamp01(t);
	return Vector4(from.x + (to.x - from.x) * t, from.y + (to.y - from.y) * t, from.z + (to.z - from.z) * t, from.w + (to.w - from.w) * t);
}

Vector4 Vector4::MoveTowards(Vector4 current, Vector4 target, float maxDistanceDelta)
{
	Vector4 a = target - current;
	float magnitude = a.magnitude();
	if (magnitude <= maxDistanceDelta || magnitude == 0)
	{
		return target;
	}
	return current + a / magnitude * maxDistanceDelta;
}

Vector4 Vector4::Scale(Vector4 a, Vector4 b)
{
	return Vector4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

void Vector4::Scale(Vector4 scale)
{
	x *= scale.x;
	y *= scale.y;
	z *= scale.z;
	w *= scale.w;
}

Vector4 Vector4::Normalize(Vector4 a)
{
	float num = Vector4::Magnitude(a);
	if (num > 1E-05f)
	{
		return a / num;
	}
	return Vector4::zero();
}

void Vector4::Normalize()
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

float Vector4::Dot(Vector4 a, Vector4 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Vector4 Vector4::Project(Vector4 a, Vector4 b)
{
	return b * Vector4::Dot(a, b) / Vector4::Dot(b, b);
}

float Vector4::Distance(Vector4 a, Vector4 b)
{
	return Vector4::Magnitude(a - b);
}

float Vector4::Magnitude(Vector4 a)
{
	return Mathf::Sqrt(Vector4::Dot(a, a));
}

float Vector4::SqrMagnitude(Vector4 a)
{
	return Vector4::Dot(a, a);
}

float Vector4::SqrMagnitude()
{
	return Vector4::Dot(*this, *this);
}

Vector4 Vector4::Min(Vector4 lhs, Vector4 rhs)
{
	return Vector4(Mathf::Min(lhs.x, rhs.x), Mathf::Min(lhs.y, rhs.y), Mathf::Min(lhs.z, rhs.z), Mathf::Min(lhs.w, rhs.w));
}

Vector4 Vector4::Max(Vector4 lhs, Vector4 rhs)
{
	return Vector4(Mathf::Max(lhs.x, rhs.x), Mathf::Max(lhs.y, rhs.y), Mathf::Max(lhs.z, rhs.z), Mathf::Max(lhs.w, rhs.w));
}

Vector4 Vector4::operator+(const Vector4 & b) const
{
	Vector4 ret = Vector4();
	ret.x = this->x + b.x;
	ret.y = this->y + b.y;
	ret.z = this->z + b.z;
	ret.w = this->w + b.w;
	return ret;
}

Vector4 Vector4::operator-(const Vector4 & b) const
{
	Vector4 ret = Vector4();
	ret.x = this->x - b.x;
	ret.y = this->y - b.y;
	ret.z = this->z - b.z;
	ret.w = this->w - b.w;
	return ret;
}

Vector4 Vector4::operator-() const
{
	Vector4 ret = Vector4();
	ret.x = -this->x;
	ret.y = -this->y;
	ret.z = -this->z;
	ret.w = -this->w;
	return ret;
}

bool Vector4::operator!=(const Vector4 & b) const
{
	return this->x != b.x
		|| this->y != b.y
		|| this->z != b.z
		|| this->z != b.z;
}

bool Vector4::operator==(const Vector4 & b) const
{
	return this->x == b.x
		&& this->y == b.y
		&& this->z == b.z
		&& this->w == b.w;
}

Vector4 Vector4::operator/(float d) const
{
	Vector4 ret = Vector4();
	ret.x = this->x / d;
	ret.y = this->y / d;
	ret.z = this->z / d;
	ret.w = this->w / d;
	return ret;
}

Vector4 Vector4::operator*(float d) const
{
	Vector4 ret = Vector4();
	ret.x = this->x * d;
	ret.y = this->y * d;
	ret.z = this->z * d;
	ret.w = this->w * d;
	return ret;
}

float& Vector4::operator[](int i)
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

Vector4 Vector4::normalized()
{
	return Vector4::Normalize(*this);
}

float Vector4::magnitude()
{
	return Mathf::Sqrt(Vector4::Dot(*this, *this));
}

float Vector4::sqrMagnitude()
{
	return Vector4::Dot(*this, *this);
}

Vector4 Vector4::zero()
{
	return Vector4(0, 0, 0, 0);
}

Vector4 Vector4::one()
{
	return Vector4(1, 1, 1, 1);
}
