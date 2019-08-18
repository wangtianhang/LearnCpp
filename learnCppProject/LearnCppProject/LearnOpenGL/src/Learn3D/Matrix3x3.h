#pragma once

#include <exception>

struct Matrix3x3
{
	float m00;

	float m10;

	float m20;

	float m01;

	float m11;

	float m21;

	float m02;

	float m12;

	float m22;

	float Get(int row, int column) const
	{
		return (*this)._GetValue(row + column * 3);
	}

	void Set(int row, int column, float value)
	{
		(*this)[row + column * 3] = value;
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
			return m01;
		case 4:
			return m11;
		case 5:
			return m21;
		case 6:
			return m02;
		case 7:
			return m12;
		case 8:
			return m22;
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
			return m01;
		case 4:
			return m11;
		case 5:
			return m21;
		case 6:
			return m02;
		case 7:
			return m12;
		case 8:
			return m22;
		default:
			throw std::exception("Matrix4x4 no index");
			break;
		}
	}
};