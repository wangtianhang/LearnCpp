#pragma once

#include "./Vector4.h"

struct Matrix4x4
{
public:

	Matrix4x4()
	{
		m00 = 0;
		m01 = 0;
		m02 = 0;
		m03 = 0;
		m10 = 0;
		m11 = 0;
		m12 = 0;
		m13 = 0;
		m20 = 0;
		m21 = 0;
		m22 = 0;
		m23 = 0;
		m30 = 0;
		m31 = 0;
		m32 = 0;
		m33 = 0;
	}

	static void Test()
	{

	}

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

	bool operator == (const Matrix4x4 & rhs) const
	{
		const Matrix4x4 & lhs = *this;
		return lhs.GetColumn(0) == rhs.GetColumn(0) && lhs.GetColumn(1) == rhs.GetColumn(1) && lhs.GetColumn(2) == rhs.GetColumn(2) && lhs.GetColumn(3) == rhs.GetColumn(3);
	}

	bool operator != (const Matrix4x4 & rhs) const
	{
		return !(*this == rhs);
	}

	Matrix4x4 operator*(const Matrix4x4 & rhs) const
	{
		const Matrix4x4 & lhs = *this;
		Matrix4x4 ret = Matrix4x4();
		
		ret.m00 = lhs.m00 * rhs.m00 + lhs.m01 * rhs.m10 + lhs.m02 * rhs.m20 + lhs.m03 * rhs.m30;
		ret.m01 = lhs.m00 * rhs.m01 + lhs.m01 * rhs.m11 + lhs.m02 * rhs.m21 + lhs.m03 * rhs.m31;
		ret.m02 = lhs.m00 * rhs.m02 + lhs.m01 * rhs.m12 + lhs.m02 * rhs.m22 + lhs.m03 * rhs.m32;
		ret.m03 = lhs.m00 * rhs.m03 + lhs.m01 * rhs.m13 + lhs.m02 * rhs.m23 + lhs.m03 * rhs.m33;
		ret.m10 = lhs.m10 * rhs.m00 + lhs.m11 * rhs.m10 + lhs.m12 * rhs.m20 + lhs.m13 * rhs.m30;
		ret.m11 = lhs.m10 * rhs.m01 + lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21 + lhs.m13 * rhs.m31;
		ret.m12 = lhs.m10 * rhs.m02 + lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22 + lhs.m13 * rhs.m32;
		ret.m13 = lhs.m10 * rhs.m03 + lhs.m11 * rhs.m13 + lhs.m12 * rhs.m23 + lhs.m13 * rhs.m33;
		ret.m20 = lhs.m20 * rhs.m00 + lhs.m21 * rhs.m10 + lhs.m22 * rhs.m20 + lhs.m23 * rhs.m30;
		ret.m21 = lhs.m20 * rhs.m01 + lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21 + lhs.m23 * rhs.m31;
		ret.m22 = lhs.m20 * rhs.m02 + lhs.m21 * rhs.m12 + lhs.m22 * rhs.m22 + lhs.m23 * rhs.m32;
		ret.m23 = lhs.m20 * rhs.m03 + lhs.m21 * rhs.m13 + lhs.m22 * rhs.m23 + lhs.m23 * rhs.m33;
		ret.m30 = lhs.m30 * rhs.m00 + lhs.m31 * rhs.m10 + lhs.m32 * rhs.m20 + lhs.m33 * rhs.m30;
		ret.m31 = lhs.m30 * rhs.m01 + lhs.m31 * rhs.m11 + lhs.m32 * rhs.m21 + lhs.m33 * rhs.m31;
		ret.m32 = lhs.m30 * rhs.m02 + lhs.m31 * rhs.m12 + lhs.m32 * rhs.m22 + lhs.m33 * rhs.m32;
		ret.m33 = lhs.m30 * rhs.m03 + lhs.m31 * rhs.m13 + lhs.m32 * rhs.m23 + lhs.m33 * rhs.m33;

		return ret;
	}

	Vector4 operator*(const Vector4 & v) const
	{
		const Matrix4x4 & lhs = *this;
		Vector4 result = Vector4();
		result.x = lhs.m00 * v.x + lhs.m01 * v.y + lhs.m02 * v.z + lhs.m03 * v.w;
		result.y = lhs.m10 * v.x + lhs.m11 * v.y + lhs.m12 * v.z + lhs.m13 * v.w;
		result.z = lhs.m20 * v.x + lhs.m21 * v.y + lhs.m22 * v.z + lhs.m23 * v.w;
		result.w = lhs.m30 * v.x + lhs.m31 * v.y + lhs.m32 * v.z + lhs.m33 * v.w;
		return result;
	}

	static Matrix4x4 identity()
	{
		Matrix4x4 ret = Matrix4x4();

		ret.m00 = 1;
		ret.m01 = 0;
		ret.m02 = 0;
		ret.m03 = 0;
		ret.m10 = 0;
		ret.m11 = 1;
		ret.m12 = 0;
		ret.m13 = 0;
		ret.m20 = 0;
		ret.m21 = 0;
		ret.m22 = 1;
		ret.m23 = 0;
		ret.m30 = 0;
		ret.m31 = 0;
		ret.m32 = 0;
		ret.m33 = 1;

		return ret;
	}

	static Matrix4x4 zero()
	{
		return Matrix4x4();
	}

	Vector4 GetColumn(int i) const
	{
		return Vector4(Get(0, i), Get(1, i), Get(2, i), Get(3, i));
	}

	float Get(int row, int column) const
	{
		return (*this)._GetValue(row + column * 4);
	}

	void Set(int row, int column, float value)
	{
		(*this)[row + column * 4] = value;
	}

	float _GetValue(int i) const
	{
		switch (i)
		{
		case 0:
			return m00;
		case 1:
			return m10;
		case 2:
			return m20;
		case 3:
			return m30;
		case 4:
			return m01;
		case 5:
			return m11;
		case 6:
			return m21;
		case 7:
			return m31;
		case 8:
			return m02;
		case 9:
			return m12;
		case 10:
			return m22;
		case 11:
			return m32;
		case 12:
			return m03;
		case 13:
			return m13;
		case 14:
			return m23;
		case 15:
			return m33;
		default:
			throw std::exception("Matrix4x4 no index");
			break;
		}
	}

	float& operator[](int i)
	{
		switch (i)
		{
		case 0:
			return m00;
		case 1:
			return m10;
		case 2:
			return m20;
		case 3:
			return m30;
		case 4:
			return m01;
		case 5:
			return m11;
		case 6:
			return m21;
		case 7:
			return m31;
		case 8:
			return m02;
		case 9:
			return m12;
		case 10:
			return m22;
		case 11:
			return m32;
		case 12:
			return m03;
		case 13:
			return m13;
		case 14:
			return m23;
		case 15:
			return m33;
		default:
			throw std::exception("Matrix4x4 no index");
			break;
		}
	}
};