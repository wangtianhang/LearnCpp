#pragma once



struct Vector3
{
public:
	static void Test()
	{

	}

	float x;
	float y;
	float z;

	Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3(float x, float y)
	{
		this->x = x;
		this->y = y;
		this->z = 0;
	}

	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3 operator-() const
	{
		Vector3 ret = Vector3();
		ret.x = -this->x;
		ret.y = -this->y;
		ret.z = -this->z;
		return ret;
	}

	Vector3 operator+(const Vector3 & b) const
	{
		Vector3 ret = Vector3();
		ret.x = this->x + b.x;
		ret.y = this->y + b.y;
		ret.z = this->z + b.z;
		return ret;
	}

	Vector3 operator-(const Vector3 & b) const
	{
		Vector3 ret = Vector3();
		ret.x = this->x - b.x;
		ret.y = this->y - b.y;
		ret.z = this->z - b.z;
		return ret;
	}

	Vector3 operator *(float d) const
	{
		Vector3 ret = Vector3();
		ret.x = this->x * d;
		ret.y = this->y * d;
		ret.z = this->z * d;
		return ret;
	}

	friend Vector3 operator *(const float d, Vector3 & b);
};

Vector3 operator *(const float d, Vector3 & b);