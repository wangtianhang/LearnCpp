#include <exception>

#include "./Matrix3x3.h"



float Matrix3x3::Get(int row, int column) const
{
	return (*this)._GetValue(row + column * 3);
}

void Matrix3x3::Set(int row, int column, float value)
{
	(*this)[row + column * 3] = value;
}

float Matrix3x3::_GetValue(int i) const
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

float& Matrix3x3::operator[](int i)
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
