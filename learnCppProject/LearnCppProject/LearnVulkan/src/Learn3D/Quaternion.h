#pragma once


struct Matrix3x3;
struct Vector3;
struct Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

	static void Test();

	Quaternion();

	Quaternion(float x, float y, float z, float w);

	Quaternion(Vector3 v, float w);

	bool operator == (const Quaternion & b) const;

	bool operator != (const Quaternion & b) const;

	Quaternion operator*(const Quaternion & b) const;
	
	Vector3 operator*(const Vector3 & point) const;

	static Quaternion identity();

	float& operator[](int i);

	static float Angle(Quaternion a, Quaternion b);

	static Quaternion AngleAxis(float degress, Vector3 axis);

	Vector3 eulerAngles();

	void SetEulerAngles(Vector3 euler);

	static float Dot(Quaternion a, Quaternion b);

	static Quaternion Euler(Vector3 euler);

	static Quaternion Euler(float x, float y, float z);

	//static Quaternion FromToRotation(Vector3 fromDiection, Vector3 toDirection)
//根据两个向量计算出旋转量，计算出来的旋转量为从fromDiection,旋转到toDirection的旋转量。
//这句话意思很明显了。就是计算旋转量。
//那么LookRotation(Vector3 forward)计算的是，Z轴旋转到forward的旋转量。
//推出：Quaternion.LookRotation(new Vector3(1,0,0)) == Quaternion.FromToRotation(Vector3.forward, new Vector3(1,0,0));
//因为前者就是计算向前向量到当前向量（1,0,0）的旋转量的，其实现过程就是后者喽。
	static Quaternion FromToRotation(Vector3 v1, Vector3 v2);

	static Quaternion Inverse(Quaternion rotation);

	static Quaternion Lerp(Quaternion from, Quaternion to, float t);

	// 四元数转欧拉角
	static Vector3 ToEulerRad(Quaternion q);

	static void QuaternionToMatrix(Quaternion q, Matrix3x3 & m);

	static void MakePositive(Vector3 & euler);

	static void SanitizeEuler(Vector3 & euler);

	static bool MatrixToEuler(Matrix3x3 matrix, Vector3 & v);

	static Vector3 NormalizeAngles(Vector3 angles);

	static float NormalizeAngle(float angle);

	// 欧拉角转四元数
	static Quaternion FromEulerRad(Vector3 euler);

	static Quaternion LookRotation(Vector3 forward);

	static Quaternion LookRotation(Vector3 forward, Vector3 up);

	static Quaternion RotateTowards(Quaternion from, Quaternion to, float maxDegreesDelta);

	void Set(float new_x, float new_y, float new_z, float new_w);

	void SetFromToRotation(Vector3 fromDirection, Vector3 toDirection);

	void SetLookRotation(Vector3 view);

	void SetLookRotation(Vector3 view, Vector3 up);

	static Quaternion SlerpUnclamped(Quaternion a, Quaternion b, float t);

	Vector3 GetXYZ();

	void SetXYZ(Vector3 xyz);

	float LengthSquared();

	float Length();

	static Quaternion Slerp(Quaternion a, Quaternion b, float t);

	static Quaternion Normalize(Quaternion q);

	void ToAngleAxis(float& angle, Vector3& axis);

	void Normalize();

	static void ToAxisAngleRad(Quaternion q, Vector3& axis, float& angle);
};