#include "Transform.h"

#include "./Vector3.h"
#include "./Quaternion.h"
#include "./Matrix4x4.h"
#include "../GUtil.h"

void Transform::Test()
{
	Transform test;
	//Vector3 euler = Vector3(-87.729256, 0.000000, 0.000000);
	Vector3 euler = Vector3(-88, 0.000000, 0.000000);
	GUtil::Log(euler.toString());
	test.SetEulerAngles(euler);
	Vector3 euler2 = NormalizeAngles(test.GetEulerAngles());
	GUtil::Log(euler2.toString());

	Quaternion qua = Quaternion::Euler(euler);
	Vector3 euler3 = qua.eulerAngles();
	GUtil::Log(NormalizeAngles(euler3).toString());
}

Vector3 Transform::NormalizeAngles(Vector3 angles)
{
	angles.x = NormalizeAngle(angles.x);
	angles.y = NormalizeAngle(angles.y);
	angles.z = NormalizeAngle(angles.z);
	return angles;
}

float Transform::NormalizeAngle(float angle)
{
	while (angle > 180)
		angle -= 360;
	while (angle < -180)
		angle += 360;
	return angle;
}

Vector3 Transform::GetPosition()
{
	if (m_isWorldPositionNeedUpdate)
	{
		m_worldPosition = convertLocalToWorldPosition(Vector3::zero());
		m_isWorldPositionNeedUpdate = false;
	}
	return m_worldPosition;
}

void Transform::SetPosition(Vector3 value)
{
	m_isWorldPositionNeedUpdate = true;
	m_localPostion = convertWorldToLocalPosition(value);
	if (m_name == "Bip001 Pelvis")
	{
		int test = 0;
	}
	SetChildNeedUpdate();
}

Vector3 Transform::GetLocalPosition()
{
	return m_localPostion;
}

void Transform::SetLocalPosition(Vector3 value)
{
	m_isWorldPositionNeedUpdate = true;
	if (m_name == "Bip001 Pelvis")
	{
		int test = 0;
	}
	m_localPostion = value;
	SetChildNeedUpdate();
}

Vector3 Transform::Divide(Vector3 a, Vector3 b)
{
	return Vector3(a.x / b.x, a.y / b.y, a.z / b.z);
}

Vector3 Transform::convertWorldToLocalPosition(Vector3 worldPos)
{
	if (m_needParentUpdate)
	{
		_updateFromParent();
	}

	Quaternion inverse = Quaternion::Inverse(GetParentOrientation());
	Vector3 divide = Divide(worldPos - GetParentPosition(), GetParentScale());
	return inverse * divide;
}

Vector3 Transform::convertLocalToWorldPosition(Vector3 localPos)
{
	if (m_needParentUpdate)
	{
		_updateFromParent();
	}
	//Matrix4x4 matrix = Matrix4x4.TRS(_getDerivedPosition(), _getDerivedOrientation(), _getDerivedScale());
	Matrix4x4 matrix = GetSelfTransform();
	return matrix.MultiplyPoint(localPos);
}

void Transform::SetChildNeedUpdate()
{
	//if(m_parent == null)
	{
		m_needParentUpdate = true;
		//m_isWorldPositionNeedUpdate = true;
	}

	for (int i = 0; i < m_childList.size(); ++i)
	{
		Transform * child = m_childList[i];
		child->SetNeedUpdateParent();
	}
}

void Transform::SetNeedUpdateParent()
{
	m_needParentUpdate = true;
	//m_isWorldPositionNeedUpdate = true;

	SetChildNeedUpdate();
}

void Transform::_updateFromParent()
{
	if (m_parent != NULL)
	{
		Quaternion parentOrientation = m_parent->_getDerivedOrientation();
		m_DerivedOrientation = parentOrientation * m_localRotation;
		//Vector3 parentScale = m_parent->GetLossyScale();
		m_DerivedScale = m_parent->GetLossyScale();
		// Change position vector based on parent's orientation & scale
		m_DerivedPosition = parentOrientation * Vector3::Scale(m_DerivedScale, m_localPostion);
		// Add altered position vector to parents
		m_DerivedPosition = m_DerivedPosition + m_parent->_getDerivedPosition();
	}
	else
	{
		m_DerivedOrientation = m_localRotation;
		m_DerivedPosition = m_localPostion;
		m_DerivedScale = Vector3::one();
	}

	m_needParentUpdate = false;
	m_isWorldPositionNeedUpdate = true;
}

Quaternion Transform::GetParentOrientation()
{
	if (m_parent != NULL)
	{
		return m_parent->_getDerivedOrientation();
	}
	else
	{
		return Quaternion::identity();
	}
}

Vector3 Transform::GetParentScale()
{
	if (m_parent != NULL)
	{
		return m_parent->_getDerivedScale();
	}
	else
	{
		return Vector3::one();
	}
}

Vector3 Transform::GetParentPosition()
{
	if (m_parent != NULL)
	{
		return m_parent->_getDerivedPosition();
	}
	else
	{
		return Vector3::zero();
	}
}

Quaternion Transform::_getDerivedOrientation()
{
	//         if(m_parent == null)
	//         {
	//             return m_localRotation;
	//         }
	//         else
	//         {
	if (m_needParentUpdate)
	{
		_updateFromParent();
	}
	return m_DerivedOrientation;
	//        }
}

Vector3 Transform::_getDerivedScale()
{
	//         if(m_parent == null)
	//         {
	//             return m_localScale;
	//         }
	//         else
	//         {
	if (m_needParentUpdate)
	{
		_updateFromParent();
	}
	return m_DerivedScale;
	//        }
}

Vector3 Transform::_getDerivedPosition()
{
	//         if(m_parent == null)
	//         {
	//             return m_localPostion;
	//         }
	//         else
	//         {
	if (m_needParentUpdate)
	{
		_updateFromParent();
	}
	return m_DerivedPosition;
	//        }
}

Quaternion Transform::GetRotation()
{
	return convertLocalToWorldOrientation(m_localRotation);
}

void Transform::SetRotation(Quaternion value)
{
	m_localRotation = convertWorldToLocalOrientation(value);
	SetChildNeedUpdate();
}

Vector3 Transform::GetLocalEulerAngles()
{
	return m_localRotation.eulerAngles();
}

void Transform::SetLocalEulerAngles(Vector3 value)
{
	m_localRotation = Quaternion::Euler(value);
	SetChildNeedUpdate();
}

Vector3 Transform::GetEulerAngles()
{
	return GetRotation().eulerAngles();
}

void Transform::SetEulerAngles(Vector3 value)
{
	SetRotation(Quaternion::Euler(value));
}

Quaternion Transform::convertLocalToWorldOrientation(Quaternion localOrientation)
{
	if (m_needParentUpdate)
	{
		_updateFromParent();
	}
	return GetParentOrientation() * localOrientation;
}

Quaternion Transform::convertWorldToLocalOrientation(Quaternion worldOrientation)
{
	if (m_needParentUpdate)
	{
		_updateFromParent();
	}
	return Quaternion::Inverse(GetParentOrientation()) * worldOrientation;
}

Transform * Transform::GetParent()
{
	return m_parent;
}

void Transform::SetParent(Transform * value)
{
	Vector3 cacheWorldPos = GetPosition();
	Quaternion cacheWorldQua = GetRotation();
	Vector3 cacheWorldScale = GetLossyScale();

	if (m_parent != NULL)
	{
		//m_parent->m_childList.erase(this);
		for (int i = 0; i < m_parent->m_childList.size(); ++i)
		{
			Transform * iter = m_parent->m_childList[i];
			if (iter == this)
			{
				m_parent->m_childList.erase(m_parent->m_childList.begin() + i);
				break;
			}
		}
	}

	m_parent = value;

	if (m_parent != NULL)
	{
		m_parent->m_childList.push_back(this);
	}

	SetChildNeedUpdate();

	SetPosition(cacheWorldPos);
	SetRotation(cacheWorldQua);
	SetLossyScale(cacheWorldScale);
}

Quaternion Transform::GetLocalRotation()
{
	return m_localRotation;
}

void Transform::SetLocalRotation(Quaternion value)
{
	m_localRotation = value;
	SetChildNeedUpdate();
}

Vector3 Transform::GetLocalScale()
{
	return m_localScale;
}

void Transform::SetLocalScale(Vector3 value)
{
	m_localScale = value;
	if (m_localScale.x > 360 && m_localScale.x < 362)
	{
		int test = 0;
	}
	SetChildNeedUpdate();
}

Vector3 Transform::GetLossyScale()
{
	return Vector3::Scale(m_DerivedScale, m_localScale);
}

void Transform::SetLossyScale(Vector3 value)
{
	m_localScale = Divide(value, m_DerivedScale);
	if (m_localScale.x > 360 && m_localScale.x < 362)
	{
		int test = 0;
	}
	SetChildNeedUpdate();
}

Matrix4x4 Transform::GetSelfTransform()
{
	Matrix4x4 matrix = Matrix4x4::TRS(_getDerivedPosition(), _getDerivedOrientation(), GetLossyScale());
	return matrix;
}

Matrix4x4 Transform::GetLocalToWorldMatrix()
{
	return GetSelfTransform();
}

Matrix4x4 Transform::GetWorldToLocalMatrix()
{
	return GetSelfTransform().inverse();
}

Vector3 Transform::GetForward()
{
	return GetRotation() * Vector3::forward();
}

void Transform::SetForward(Vector3 value)
{
	SetRotation(Quaternion::LookRotation(value));
}

Vector3 Transform::GetRight()
{
	return GetRotation() * Vector3::right();
}

void Transform::SetRight(Vector3 value)
{
	SetRotation(Quaternion::FromToRotation(Vector3::right(), value));
}

Vector3 Transform::GetUp()
{
	return GetRotation() * Vector3::up();
}

void Transform::SetUp(Vector3 value)
{
	SetRotation(Quaternion::FromToRotation(Vector3::up(), value));
}
