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
			throw std::exception("vector3 no index");
			break;
		}
	}

	static Vector4 zero()
	{
		return Vector4(0, 0, 0, 0);
	}

	static Vector4 one()
	{
		return Vector4(1, 1, 1, 1);
	}
};