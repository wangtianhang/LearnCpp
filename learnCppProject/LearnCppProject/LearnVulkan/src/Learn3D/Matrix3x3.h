#pragma once

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

	float Get(int row, int column) const;

	void Set(int row, int column, float value);



	float _GetValue(int i) const;

	float& operator[](int i);

};