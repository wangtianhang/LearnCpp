#pragma once

#include <string>
struct Vector4;
struct Vector3;
struct Quaternion;
struct Matrix4x4
{
public:
	float m00;

	float m10;

	float m20;

	float m30;

	float m01;

	float m11;

	float m21;

	float m31;

	float m02;

	float m12;

	float m22;

	float m32;

	float m03;

	float m13;

	float m23;

	float m33;

	static void Test();

	std::string ToString();

	Matrix4x4();

	bool operator == (const Matrix4x4 & rhs) const;

	bool operator != (const Matrix4x4 & rhs) const;

	Matrix4x4 operator*(const Matrix4x4 & rhs) const;

	Vector4 operator*(const Vector4 & v) const;

	static Matrix4x4 identity();

	static Matrix4x4 zero();

	Matrix4x4 inverse();

	Matrix4x4 transpose();

	float Get(int row, int column) const;

	void Set(int row, int column, float value);

	float _GetValue(int i) const;

	float& operator[](int i);

	Vector4 GetColumn(int i) const;

	Vector4 GetRow(int i);

	void SetColumn(int i, Vector4 v);

	void SetRow(int i, Vector4 v);

	static Matrix4x4 Inverse(Matrix4x4 m);

	Vector3 MultiplyPoint(Vector3 v);

	Vector3 MultiplyVector(Vector3 v);

	static Matrix4x4 Perspective(float fov, float aspect, float zNear, float zFar);

	static Matrix4x4 Scale(Vector3 v);

	static Matrix4x4 Transpose(Matrix4x4 m);

	/// <summary>
	/// 可以用来计算ojbtoworld矩阵
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="q"></param>
	/// <param name="s"></param>
	/// <returns></returns>
	static Matrix4x4 TRS(Vector3 pos, Quaternion q, Vector3 s);

	// 移除Translation分量
	static Matrix4x4 RemoveTranslationComponent(Matrix4x4 input);

	void GetMatrixArray(float matrixArray[16]);

#pragma region inverse
	//求逆 https ://github.com/Phylliida/UnityMatrix/blob/master/Matrix.cs
// 	static float[][] _MatrixCreate(int rows, int cols)
// 	{
// 		float[][] result = new float[rows][];
// 		for (int i = 0; i < rows; ++i)
// 			result[i] = new float[cols];
// 		return result;
// 	}

	static void _MatrixInverse(float matrix[4][4], float result[4][4]);

	static int _MatrixDecompose(float m[4][4], float lum[4][4], int perm[4]);

	static void ChangeRow(float mat[4][4], int row1, int row2);

	static void _Helper(float luMatrix[4][4], float b[4], float result[4]); // helper
	// ==================结束求逆====================================
#pragma endregion

	static Matrix4x4 Ortho(float left, float right, float bottom, float top, float zNear, float zFar);
};