#pragma once


#include <string>
struct Vector3
{
public:

	float x;
	float y;
	float z;

	static void Test();

	std::string toString();

	Vector3();

	Vector3(float x, float y);

	Vector3(float x, float y, float z);

	Vector3 operator-() const;

	Vector3 operator+(const Vector3 & b) const;

	Vector3 operator-(const Vector3 & b) const;

	Vector3 operator *(float d) const;

	Vector3 operator /(float d) const;

	bool operator == (const Vector3 & b) const;

	bool operator != (const Vector3 & b) const;

	static Vector3 back();

	static Vector3 forward();

	static Vector3 up();

	static Vector3 down();

	static Vector3 right();

	static Vector3 left();

	static Vector3 zero();

	static Vector3 one();

	float magnitude();

	float sqrMagnitude();

	Vector3 normalized();

	float& operator[](int i);

	static float Angle(Vector3 from, Vector3 to);

	static Vector3 ClampMagnitude(Vector3 vector, float maxLength);

	static Vector3 Cross(Vector3 lhs, Vector3 rhs);

	static float Distance(Vector3 a, Vector3 b);

	static float Dot(Vector3 lhs, Vector3 rhs);

	static Vector3 Lerp(Vector3 from, Vector3 to, float t);

	static float Magnitude(Vector3 a);

	static Vector3 Max(Vector3 lhs, Vector3 rhs);

	static Vector3 Min(Vector3 lhs, Vector3 rhs);

	static Vector3 MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta);

	void Normalize();

	static Vector3 Normalize(Vector3 value);

	static Vector3 Project(Vector3 vector, Vector3 onNormal);

	static Vector3 ProjectOnPlane(Vector3 vector, Vector3 planeNormal);

	// 潜规则 inNormal 需要为单位向量
	static Vector3 Reflect(Vector3 inDirection, Vector3 inNormal);

	void Scale(Vector3 scale);

	static Vector3 Scale(Vector3 a, Vector3 b);

	void Set(float new_x, float new_y, float new_z);

	static float SqrMagnitude(Vector3 a);

	// todo 需要补充。。不过依赖矩阵和四元数 先去写其他的了。。
	static Vector3 Slerp(Vector3 a, Vector3 b, float t);

	static Vector3 RotateTo(Vector3 from, Vector3 to, float angle);


	//friend Vector3 operator *(const float d, Vector3 & b);
	friend Vector3 operator *(const float d, Vector3 b);
};

//Vector3 operator *(const float d, Vector3 & b);
Vector3 operator *(const float d, Vector3 b);