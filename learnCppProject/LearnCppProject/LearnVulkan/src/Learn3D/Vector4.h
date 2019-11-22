#pragma once


struct Vector4
{
public:
	float x;
	float y;
	float z;
	float w;

	static void Test();

	Vector4();

	float& operator[](int i);

	Vector4 normalized();

	float magnitude();

	float sqrMagnitude();

	static Vector4 zero();

	static Vector4 one();

	Vector4(float x, float y, float z, float w);

	Vector4(float x, float y, float z);

	Vector4(float x, float y);

	void Set(float new_x, float new_y, float new_z, float new_w);

	static Vector4 Lerp(Vector4 from, Vector4 to, float t);

	static Vector4 MoveTowards(Vector4 current, Vector4 target, float maxDistanceDelta);

	static Vector4 Scale(Vector4 a, Vector4 b);

	void Scale(Vector4 scale);

	static Vector4 Normalize(Vector4 a);

	void Normalize();

	static float Dot(Vector4 a, Vector4 b);

	static Vector4 Project(Vector4 a, Vector4 b);

	static float Distance(Vector4 a, Vector4 b);

	static float Magnitude(Vector4 a);

	static float SqrMagnitude(Vector4 a);

	float SqrMagnitude();

	static Vector4 Min(Vector4 lhs, Vector4 rhs);

	static Vector4 Max(Vector4 lhs, Vector4 rhs);

	Vector4 operator+(const Vector4 & b) const;

	Vector4 operator-(const Vector4 & b) const;

	Vector4 operator-() const;

	Vector4 operator *(float d) const;

	Vector4 operator /(float d) const;

	bool operator == (const Vector4 & b) const;

	bool operator != (const Vector4 & b) const;

	friend Vector4 operator *(const float d, Vector4 b);
};

Vector4 operator *(const float d, Vector4 b);