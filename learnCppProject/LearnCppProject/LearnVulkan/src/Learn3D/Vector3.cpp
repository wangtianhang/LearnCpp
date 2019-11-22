
/*#include "pch.h"*/
#include "../DebugMemory.h"


#include "./Mathf.h"

#include "Vector3.h"
#include "Matrix4x4.h"

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

void Vector3::Test()
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

	float g = 2;
	Vector3 h = g * Vector3::one();
}

std::string Vector3::toString()
{
	return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")";
}

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float x, float y)
{
	this->x = x;
	this->y = y;
	this->z = 0;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3 Vector3::operator-() const
{
	Vector3 ret = Vector3();
	ret.x = -this->x;
	ret.y = -this->y;
	ret.z = -this->z;
	return ret;
}

Vector3 Vector3::operator-(const Vector3 & b) const
{
	Vector3 ret = Vector3();
	ret.x = this->x - b.x;
	ret.y = this->y - b.y;
	ret.z = this->z - b.z;
	return ret;
}

Vector3 Vector3::back()
{
	return Vector3(0, 0, -1);
}

Vector3 Vector3::forward()
{
	return Vector3(0, 0, +1);
}

Vector3 Vector3::up()
{
	return Vector3(0, 1, 0);
}

Vector3 Vector3::down()
{
	return Vector3(0, -1, 0);
}

Vector3 Vector3::right()
{
	return Vector3(1, 0, 0);
}

Vector3 Vector3::left()
{
	return Vector3(-1, 0, 0);
}

Vector3 Vector3::zero()
{
	return Vector3(0, 0, 0);
}

Vector3 Vector3::one()
{
	return Vector3(1, 1, 1);
}

float Vector3::magnitude()
{
	return Mathf::Sqrt(sqrMagnitude());
}

float Vector3::sqrMagnitude()
{
	return x * x + y * y + z * z;
}

Vector3 Vector3::normalized()
{
	return Vector3::Normalize(*this);
}

float Vector3::Angle(Vector3 from, Vector3 to)
{
	return Mathf::Acos(Mathf::Clamp(Vector3::Dot(from.normalized(), to.normalized()), (float)-1, (float)1)) * 57.29578f;
}

Vector3 Vector3::ClampMagnitude(Vector3 vector, float maxLength)
{
	if (vector.sqrMagnitude() > maxLength * maxLength)
	{
		return vector.normalized() * maxLength;
	}
	return vector;
}

Vector3 Vector3::Cross(Vector3 lhs, Vector3 rhs)
{
	return Vector3(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x);
}

float Vector3::Distance(Vector3 a, Vector3 b)
{
	Vector3 vector = Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
	return Mathf::Sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

float Vector3::Dot(Vector3 lhs, Vector3 rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vector3 Vector3::Lerp(Vector3 from, Vector3 to, float t)
{
	t = Mathf::Clamp01(t);
	return Vector3(from.x + (to.x - from.x) * t, from.y + (to.y - from.y) * t, from.z + (to.z - from.z) * t);
}

float Vector3::Magnitude(Vector3 a)
{
	return Mathf::Sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

Vector3 Vector3::Max(Vector3 lhs, Vector3 rhs)
{
	return Vector3(Mathf::Max(lhs.x, rhs.x), Mathf::Max(lhs.y, rhs.y), Mathf::Max(lhs.z, rhs.z));
}

Vector3 Vector3::Min(Vector3 lhs, Vector3 rhs)
{
	return Vector3(Mathf::Min(lhs.x, rhs.x), Mathf::Min(lhs.y, rhs.y), Mathf::Min(lhs.z, rhs.z));
}

Vector3 Vector3::MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta)
{
	Vector3 a = target - current;
	float magnitude = a.magnitude();
	if (magnitude <= maxDistanceDelta || magnitude == 0)
	{
		return target;
	}
	return current + a / magnitude * maxDistanceDelta;
}

void Vector3::Normalize()
{
	float num = Vector3::Magnitude(*this);
	if (num > 1E-05f)
	{
		*this = *this / num;
	}
	else
	{
		*this = Vector3::zero();
	}
}

Vector3 Vector3::Normalize(Vector3 value)
{
	float num = Vector3::Magnitude(value);
	if (num > 1E-05f)
	{
		return value / num;
	}
	return Vector3::zero();
}

Vector3 Vector3::Project(Vector3 vector, Vector3 onNormal)
{
	float num = Vector3::Dot(onNormal, onNormal);
	if (num < 1.401298E-45f)
	{
		return Vector3::zero();
	}
	return onNormal * Vector3::Dot(vector, onNormal) / num;
}

Vector3 Vector3::ProjectOnPlane(Vector3 vector, Vector3 planeNormal)
{
	return vector - Vector3::Project(vector, planeNormal);
}

Vector3 Vector3::Reflect(Vector3 inDirection, Vector3 inNormal)
{
	return -2 * Vector3::Dot(inNormal, inDirection) * inNormal + inDirection;
}

void Vector3::Scale(Vector3 scale)
{
	x *= scale.x;
	y *= scale.y;
	z *= scale.z;
}

Vector3 Vector3::Scale(Vector3 a, Vector3 b)
{
	return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
}

void Vector3::Set(float new_x, float new_y, float new_z)
{
	x = new_x;
	y = new_y;
	z = new_z;
}

float Vector3::SqrMagnitude(Vector3 a)
{
	return a.x * a.x + a.y * a.y + a.z * a.z;
}

Vector3 Vector3::Slerp(Vector3 a, Vector3 b, float t)
{
	//         Quaternion fromQua = Quaternion.LookRotation(from, Vector3.up);
	//         Quaternion toQua = Quaternion.LookRotation(to, Vector3.up);
	//         Quaternion endQua = Quaternion.Slerp(fromQua, toQua, t);
	// 
	//         Vector3 endDir = endQua * Vector3.forward;
	//         endDir.Normalize();
	// 
	//         float length = Mathf3d.Lerp(from.magnitude, to.magnitude, t);
	//         return endDir.normalized * length;
	if (t <= 0)
	{
		return a;
	}
	else if (t >= 1)
	{
		return b;
	}

	Vector3 v = RotateTo(a, b, Vector3::Angle(a, b) * t);

	//向量的长度，跟线性插值一样计算
	float length = b.magnitude() * t + a.magnitude() * (1 - t);
	return v.normalized() * length;
}

bool Vector3::operator!=(const Vector3 & b) const
{
	return this->x != b.x
		|| this->y != b.y
		|| this->z != b.z;
}

bool Vector3::operator==(const Vector3 & b) const
{
	return this->x == b.x
		&& this->y == b.y
		&& this->z == b.z;
}

Vector3 Vector3::operator/(float d) const
{
	Vector3 ret = Vector3();
	ret.x = this->x / d;
	ret.y = this->y / d;
	ret.z = this->z / d;
	return ret;
}

Vector3 Vector3::operator+(const Vector3 & b) const
{
	Vector3 ret = Vector3();
	ret.x = this->x + b.x;
	ret.y = this->y + b.y;
	ret.z = this->z + b.z;
	return ret;
}

float& Vector3::operator[](int i)
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

Vector3 Vector3::RotateTo(Vector3 from, Vector3 to, float angle)
{
	//如果两向量角度为0
	if (Vector3::Angle(from, to) == 0)
	{
		return from;
	}

	//旋转轴
	Vector3 n = Vector3::Cross(from, to);

	//旋转轴规范化
	n.Normalize();

	//旋转矩阵
	Matrix4x4 rotateMatrix = Matrix4x4();

	//旋转的弧度
	double radian = angle * Mathf::PI / 180;
	float cosAngle = Mathf::Cos(radian);
	float sinAngle = Mathf::Sin(radian);

	//矩阵的数据
	//这里看不懂的自行科普矩阵知识
	rotateMatrix.SetRow(0, Vector4(n.x * n.x * (1 - cosAngle) + cosAngle, n.x * n.y * (1 - cosAngle) + n.z * sinAngle, n.x * n.z * (1 - cosAngle) - n.y * sinAngle, 0));
	rotateMatrix.SetRow(1, Vector4(n.x * n.y * (1 - cosAngle) - n.z * sinAngle, n.y * n.y * (1 - cosAngle) + cosAngle, n.y * n.z * (1 - cosAngle) + n.x * sinAngle, 0));
	rotateMatrix.SetRow(2, Vector4(n.x * n.z * (1 - cosAngle) + n.y * sinAngle, n.y * n.z * (1 - cosAngle) - n.x * sinAngle, n.z * n.z * (1 - cosAngle) + cosAngle, 0));
	rotateMatrix.SetRow(3, Vector4(0, 0, 0, 1));

	//Vector4 v = Vector3.ToVector4(from);
	Vector4 v = Vector4(from.x, from.y, from.z, 0);
	Vector3 vector = Vector3();
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; j++)
		{
			vector[i] += v[j] * rotateMatrix[j, i];
		}
	}
	return vector;
}

Vector3 Vector3::operator*(float d) const
{
	Vector3 ret = Vector3();
	ret.x = this->x * d;
	ret.y = this->y * d;
	ret.z = this->z * d;
	return ret;
}

