
/*#include "pch.h"*/

#include "Vector3.h"
#include "Matrix4x4.h"

// Vector3 operator*(const float d, Vector3 & b)
// {
// 	Vector3 ret = Vector3();
// 	ret.x = b.x * d;
// 	ret.y = b.y * d;
// 	ret.z = b.z * d;
// 	return ret;
// }

Vector3 operator*(const float d, Vector3 b)
{
	Vector3 ret = Vector3();
	ret.x = b.x * d;
	ret.y = b.y * d;
	ret.z = b.z * d;
	return ret;
}

Vector3 Vector3::RotateTo(Vector3 from, Vector3 to, float angle)
{
	//����������Ƕ�Ϊ0
	if (Vector3::Angle(from, to) == 0)
	{
		return from;
	}

	//��ת��
	Vector3 n = Vector3::Cross(from, to);

	//��ת��淶��
	n.Normalize();

	//��ת����
	Matrix4x4 rotateMatrix = Matrix4x4();

	//��ת�Ļ���
	double radian = angle * Mathf::PI / 180;
	float cosAngle = Mathf::Cos(radian);
	float sinAngle = Mathf::Sin(radian);

	//���������
	//���￴���������п��վ���֪ʶ
	rotateMatrix.SetRow(0, Vector4(n.x * n.x * (1 - cosAngle) + cosAngle, n.x * n.y * (1 - cosAngle) + n.z * sinAngle, n.x * n.z * (1 - cosAngle) - n.y * sinAngle, 0));
	rotateMatrix.SetRow(1, Vector4(n.x * n.y * (1 - cosAngle) - n.z * sinAngle, n.y * n.y * (1 - cosAngle) + cosAngle, n.y * n.z * (1 - cosAngle) + n.x * sinAngle, 0));
	rotateMatrix.SetRow(2, Vector4(n.x * n.z * (1 - cosAngle) + n.y * sinAngle, n.y * n.z * (1 - cosAngle) - n.x * sinAngle, n.z * n.z * (1 - cosAngle) + cosAngle, 0));
	rotateMatrix.SetRow(3, Vector4(0, 0, 0, 1));

	//Vector4 v = Vector3.ToVector4(from);
	Vector4 v = Vector4(from.x, from.y, from.z, 0);
	Vector3 vector = Vector3();
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; j++)
		{
			vector[i] += v[j] * rotateMatrix[j, i];
		}
	}
	return vector;
}

