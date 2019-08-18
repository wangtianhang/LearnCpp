#pragma once

#include "./Vector3.h"

struct Quaternion
{
public:
	static void Test()
	{

	}

	float x;
	float y;
	float z;
	float w;

	Quaternion()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	Quaternion(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Quaternion(Vector3 v, float w)
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
		this->w = w;
	}

	bool operator == (const Quaternion & b) const
	{
		return Quaternion::Dot(*this, b) > 0.999999f;
	}

	bool operator != (const Quaternion & b) const
	{
		return Quaternion::Dot(*this, b) <= 0.999999f;
	}



	Quaternion operator*(const Quaternion & b) const
	{
		const Quaternion &lhs = *this;
		const Quaternion &rhs = b;
		return Quaternion(lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y, lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z, lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x, lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z);
	}
	
	Vector3 operator*(const Vector3 & point) const
	{
		const Quaternion rotation = *this;
		float num = rotation.x * 2;
		float num2 = rotation.y * 2;
		float num3 = rotation.z * 2;
		float num4 = rotation.x * num;
		float num5 = rotation.y * num2;
		float num6 = rotation.z * num3;
		float num7 = rotation.x * num2;
		float num8 = rotation.x * num3;
		float num9 = rotation.y * num3;
		float num10 = rotation.w * num;
		float num11 = rotation.w * num2;
		float num12 = rotation.w * num3;
		Vector3 result;
		result.x = (1 - (num5 + num6)) * point.x + (num7 - num12) * point.y + (num8 + num11) * point.z;
		result.y = (num7 + num12) * point.x + (1 - (num4 + num6)) * point.y + (num9 - num10) * point.z;
		result.z = (num8 - num11) * point.x + (num9 + num10) * point.y + (1 - (num4 + num5)) * point.z;
		return result;
	}

	static Quaternion identity()
	{
		return Quaternion(0, 0, 0, 1);
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
			throw std::exception("quaternion no index");
			break;
		}
	}

	static float Angle(Quaternion a, Quaternion b)
	{
		float f = Quaternion::Dot(a, b);
		return Mathf::Acos(Mathf::Min(Mathf::Abs(f), (float)1)) * 2 * 57.29578f;
	}

	static Quaternion AngleAxis(float degress, Vector3 axis)
	{
		if (axis.sqrMagnitude() == 0.0f)
			return identity();

		Quaternion result = identity();
		float radians = degress * Mathf::Deg2Rad;
		radians *= 0.5f;
		axis.Normalize();
		axis = axis * Mathf::Sin(radians);
		result.x = axis.x;
		result.y = axis.y;
		result.z = axis.z;
		result.w = Mathf::Cos(radians);

		return Normalize(result);
	}

	Vector3 eulerAngles()
	{
		return Quaternion::ToEulerRad(*this) * 57.29578f;
	}


	void SetEulerAngles(Vector3 euler)
	{
		*this = Quaternion::FromEulerRad(euler * 0.0174532924f);
	}

	static float Dot(Quaternion a, Quaternion b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	static Quaternion Euler(Vector3 euler)
	{
		Vector3 eulerRad = euler * Mathf::Deg2Rad;
		return FromEulerRad(eulerRad);
	}

	static Quaternion Euler(float x, float y, float z)
	{
		return Quaternion::Euler(Vector3(x, y, z));
	}


	//static Quaternion FromToRotation(Vector3 fromDiection, Vector3 toDirection)
//根据两个向量计算出旋转量，计算出来的旋转量为从fromDiection,旋转到toDirection的旋转量。
//这句话意思很明显了。就是计算旋转量。
//那么LookRotation(Vector3 forward)计算的是，Z轴旋转到forward的旋转量。
//推出：Quaternion.LookRotation(new Vector3(1,0,0)) == Quaternion.FromToRotation(Vector3.forward, new Vector3(1,0,0));
//因为前者就是计算向前向量到当前向量（1,0,0）的旋转量的，其实现过程就是后者喽。
	static Quaternion FromToRotation(Vector3 v1, Vector3 v2)
	{
		return Quaternion::AngleAxis(Vector3::Angle(v1, v2), Vector3::Cross(v1, v2));
	}

	static Quaternion Inverse(Quaternion rotation)
	{
		float lengthSq = rotation.LengthSquared();
		if (lengthSq != 0.0)
		{
			float i = 1.0f / lengthSq;
			float x = rotation.x * -i;
			float y = rotation.y * -i;
			float z = rotation.z * -i;
			return Quaternion(x, y, z, rotation.w * i);
		}
		return rotation;
	}

	static Quaternion Lerp(Quaternion from, Quaternion to, float t)
	{
		if (t > 1) t = 1;
		if (t < 0) t = 0;
		return Slerp(from, to, t);
	}


	// 四元数转欧拉角
	static Vector3 ToEulerRad(Quaternion q)
	{
// 		float sqw = rotation.w * rotation.w;
// 		float sqx = rotation.x * rotation.x;
// 		float sqy = rotation.y * rotation.y;
// 		float sqz = rotation.z * rotation.z;
// 		float unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
// 		float test = rotation.x * rotation.w - rotation.y * rotation.z;
// 		Vector3 v;
// 
// 		if (test > 0.4995f * unit)
// 		{ // singularity at north pole
// 			v.y = 2 * Mathf::Atan2(rotation.y, rotation.x);
// 			v.x = Mathf::PI / 2;
// 			v.z = 0;
// 			return NormalizeAngles(v * Mathf::Rad2Deg);
// 		}
// 		if (test < -0.4995f * unit)
// 		{ // singularity at south pole
// 			v.y = -2 * Mathf::Atan2(rotation.y, rotation.x);
// 			v.x = -Mathf::PI / 2;
// 			v.z = 0;
// 			return NormalizeAngles(v * Mathf::Rad2Deg);
// 		}
// 		Quaternion q = Quaternion(rotation.w, rotation.z, rotation.x, rotation.y);
// 		v.y = Mathf::Atan2(2 * q.x * q.w + 2 * q.y * q.z, 1 - 2 * (q.z * q.z + q.w * q.w));     // Yaw
// 		v.x = Mathf::Asin(2 * (q.x * q.z - q.w * q.y));                             // Pitch
// 		v.z = Mathf::Atan2(2 * q.x * q.y + 2 * q.z * q.w, 1 - 2 * (q.y * q.y + q.z * q.z));      // Roll
// 		return NormalizeAngles(v * Mathf::Rad2Deg) * Mathf::Deg2Rad;

		float sqw = q.w * q.w;
		float sqx = q.x * q.x;
		float sqy = q.y * q.y;
		float sqz = q.z * q.z;

		float unit = sqx + sqy + sqz + sqw;
		float test = q.x * q.y + q.z * q.w;

		float yaw = 0.0f;
		float pitch = 0.0f;
		float roll = 0.0f;

		// North pole singularity
		if (test > 0.499f * unit)
		{
			yaw = 2.0f * Mathf::Atan2(q.x, q.w);
			pitch = Mathf::PI * 0.5f;
			roll = 0.0f;
		}

		// South pole singularity
		else if (test < -0.499f * unit)
		{
			yaw = -2.0f * Mathf::Atan2(q.x, q.w);
			pitch = -Mathf::PI * 0.5f;
			roll = 0.0f;
		}

		else
		{
			yaw = Mathf::Atan2(2.0f * q.y * q.w - 2.0f * q.x * q.z, sqx - sqy - sqz + sqw);
			pitch = Mathf::Asin(2.0f * test / unit);
			roll = Mathf::Atan2(2.0f * q.x * q.w - 2.0f * q.y * q.z, -sqx + sqy - sqz + sqw);
		}

		// Keep angles [0..360].
		if (Mathf::Sign(yaw) < 0)
			yaw = Mathf::Deg2Rad * (360) + yaw;
		if (Mathf::Sign(pitch) < 0)
			pitch = Mathf::Deg2Rad * (360) + pitch;
		if (Mathf::Sign(roll) < 0)
			roll = Mathf::Deg2Rad * (360) + roll;

		return Vector3(roll, yaw, pitch);
	}

	static Vector3 NormalizeAngles(Vector3 angles)
	{
		angles.x = NormalizeAngle(angles.x);
		angles.y = NormalizeAngle(angles.y);
		angles.z = NormalizeAngle(angles.z);
		return angles;
	}

	static float NormalizeAngle(float angle)
	{
		while (angle > 360)
			angle -= 360;
		while (angle < 0)
			angle += 360;
		return angle;
	}


	// 欧拉角转四元数
	static Quaternion FromEulerRad(Vector3 euler)
	{
		float yaw = euler.z;
		float pitch = euler.x;
		float roll = euler.y;

		float yawOver2 = yaw * 0.5f;
		float sinYawOver2 = Mathf::Sin(yawOver2);
		float cosYawOver2 = Mathf::Cos(yawOver2);

		float pitchOver2 = pitch * 0.5f;
		float sinPitchOver2 = Mathf::Sin(pitchOver2);
		float cosPitchOver2 = Mathf::Cos(pitchOver2);

		float rollOver2 = roll * 0.5f;
		float sinRollOver2 = Mathf::Sin(rollOver2);
		float cosRollOver2 = Mathf::Cos(rollOver2);

		Quaternion result;
		result.w = cosYawOver2 * cosPitchOver2 * cosRollOver2 + sinYawOver2 * sinPitchOver2 * sinRollOver2;
		result.x = cosYawOver2 * sinPitchOver2 * cosRollOver2 + sinYawOver2 * cosPitchOver2 * sinRollOver2;
		result.y = cosYawOver2 * cosPitchOver2 * sinRollOver2 - sinYawOver2 * sinPitchOver2 * cosRollOver2;
		result.z = sinYawOver2 * cosPitchOver2 * cosRollOver2 - cosYawOver2 * sinPitchOver2 * sinRollOver2;
		return result;
	}

	static Quaternion LookRotation(Vector3 forward)
	{
		return LookRotation(forward, Vector3::up());
	}

	static Quaternion LookRotation(Vector3 forward, Vector3 up)
	{
		forward = Vector3::Normalize(forward);
		Vector3 right = Vector3::Normalize(Vector3::Cross(up, forward));
		up = Vector3::Cross(forward, right);
		float m00 = right.x;
		float m01 = right.y;
		float m02 = right.z;
		float m10 = up.x;
		float m11 = up.y;
		float m12 = up.z;
		float m20 = forward.x;
		float m21 = forward.y;
		float m22 = forward.z;


		float num8 = (m00 + m11) + m22;
		Quaternion quaternion = Quaternion();
		if (num8 > 0)
		{
			float num = Mathf::Sqrt(num8 + 1);
			quaternion.w = num * 0.5f;
			num = 0.5f / num;
			quaternion.x = (m12 - m21) * num;
			quaternion.y = (m20 - m02) * num;
			quaternion.z = (m01 - m10) * num;
			return quaternion;
		}
		if ((m00 >= m11) && (m00 >= m22))
		{
			float num7 = Mathf::Sqrt(((1 + m00) - m11) - m22);
			float num4 = 0.5f / num7;
			quaternion.x = 0.5f * num7;
			quaternion.y = (m01 + m10) * num4;
			quaternion.z = (m02 + m20) * num4;
			quaternion.w = (m12 - m21) * num4;
			return quaternion;
		}
		if (m11 > m22)
		{
			float num6 = Mathf::Sqrt(((1 + m11) - m00) - m22);
			float num3 = 0.5f / num6;
			quaternion.x = (m10 + m01) * num3;
			quaternion.y = 0.5f * num6;
			quaternion.z = (m21 + m12) * num3;
			quaternion.w = (m20 - m02) * num3;
			return quaternion;
		}
		float num5 = Mathf::Sqrt(((1 + m22) - m00) - m11);
		float num2 = 0.5f / num5;
		quaternion.x = (m20 + m02) * num2;
		quaternion.y = (m21 + m12) * num2;
		quaternion.z = 0.5f * num5;
		quaternion.w = (m01 - m10) * num2;
		return quaternion;
	}

	static Quaternion RotateTowards(Quaternion from, Quaternion to, float maxDegreesDelta)
	{
		float num = Quaternion::Angle(from, to);
		if (num == 0)
		{
			return to;
		}
		float t = Mathf::Min((double)1, maxDegreesDelta / num);
		return Quaternion::SlerpUnclamped(from, to, t);
	}

	void Set(float new_x, float new_y, float new_z, float new_w)
	{
		x = new_x;
		y = new_y;
		z = new_z;
		w = new_w;
	}

	void SetFromToRotation(Vector3 fromDirection, Vector3 toDirection)
	{
		*this = FromToRotation(fromDirection, toDirection);
	}

	void SetLookRotation(Vector3 view)
	{
		*this = LookRotation(view);
	}

	void SetLookRotation(Vector3 view, Vector3 up)
	{
		*this = LookRotation(view, up);
	}

	static Quaternion SlerpUnclamped(Quaternion a, Quaternion b, float t)
	{
		// if either input is zero, return the other.
		if (a.LengthSquared() == 0.0f)
		{
			if (b.LengthSquared() == 0.0f)
			{
				return identity();
			}
			return b;
		}
		else if (b.LengthSquared() == 0.0f)
		{
			return a;
		}


		float cosHalfAngle = a.w * b.w + Vector3::Dot(a.GetXYZ(), b.GetXYZ());

		if (cosHalfAngle >= 1.0f || cosHalfAngle <= -1.0f)
		{
			// angle = 0.0f, so just return one input.
			return a;
		}
		else if (cosHalfAngle < 0.0f)
		{
			b.SetXYZ(-b.GetXYZ());
			b.w = -b.w;
			cosHalfAngle = -cosHalfAngle;
		}

		float blendA;
		float blendB;
		if (cosHalfAngle < 0.99f)
		{
			// do proper slerp for big angles
			float halfAngle = Mathf::Acos(cosHalfAngle);
			float sinHalfAngle = Mathf::Sin(halfAngle);
			float oneOverSinHalfAngle = 1.0f / sinHalfAngle;
			blendA = Mathf::Sin(halfAngle * (1.0f - t)) * oneOverSinHalfAngle;
			blendB = Mathf::Sin(halfAngle * t) * oneOverSinHalfAngle;
		}
		else
		{
			// do lerp if angle is really small.
			blendA = 1.0f - t;
			blendB = t;
		}

		Vector3 tmp1 = blendA * a.GetXYZ();
		Vector3 tmp2 = blendB * b.GetXYZ();
		Quaternion result = Quaternion(tmp1 + tmp2, blendA * a.w + blendB * b.w);
		if (result.LengthSquared() > 0.0f)
			return Normalize(result);
		else
			return identity();
	}



	Vector3 GetXYZ()
	{
		return Vector3(x, y, z);
	}

	Vector3 SetXYZ(Vector3 xyz)
	{
		x = xyz.x;
		y = xyz.y;
		z = xyz.z;
	}

	float LengthSquared()
	{
		return x * x + y * y + z * z + w * w;
	}

	float Length()
	{
		return Mathf::Sqrt(x * x + y * y + z * z + w * w);
	}

	static Quaternion Slerp(Quaternion a, Quaternion b, float t)
	{
		if (t > 1) t = 1;
		if (t < 0) t = 0;
		return SlerpUnclamped(a, b, t);
	}

	static Quaternion Normalize(Quaternion q)
	{
		float scale = 1.0f / q.Length();
		float x = q.x * scale;
		float y = q.y * scale;
		float z = q.z * scale;
		Quaternion result = Quaternion(x, y, z, q.w * scale);
		return result;
	}

	void ToAngleAxis(float& angle, Vector3& axis)
	{
		Quaternion::ToAxisAngleRad(*this, axis, angle);
		angle *= Mathf::Rad2Deg;
	}

	void Normalize()
	{
		float scale = 1.0f / Length();
		//xyz *= scale;
		SetXYZ(GetXYZ() * scale);
		w *= scale;
	}

	static void ToAxisAngleRad(Quaternion q, Vector3& axis, float& angle)
	{
		if (Mathf::Abs(q.w) > 1.0f)
			q.Normalize();
		angle = 2.0f * Mathf::Acos(q.w); // angle
		float den = Mathf::Sqrt(1.0f - q.w * q.w);
		if (den > 0.0001f)
		{
			axis = q.GetXYZ() / den;
		}
		else
		{
			// This occurs when the angle is zero. 
			// Not a problem: just set an arbitrary normalized axis.
			axis = Vector3(1, 0, 0);
		}
	}
};