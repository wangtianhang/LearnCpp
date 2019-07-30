#pragma once

#include <vector>

#include "./Vector3.h"
#include "./Quaternion.h"


class Transform
{
public:

	bool m_needParentUpdate = true;

	Vector3 m_localPostion;
	Quaternion m_localRotation = Quaternion::identity();
	Vector3 m_localScale = Vector3::one();

	Quaternion m_DerivedOrientation = Quaternion::identity(); // 包含自身和上级
	Vector3 m_DerivedScale = Vector3::one(); // 包含自身和上级
	Vector3 m_DerivedPosition; // 包含自身和上级

	Transform * m_parent = NULL;
	std::vector<Transform *> m_childList;

	Vector3 m_worldPosition;
	bool m_isWorldPositionNeedUpdate = true;

	Vector3 GetPosition()
	{
		if (m_isWorldPositionNeedUpdate)
		{
			m_worldPosition = convertLocalToWorldPosition(Vector3::zero());
			m_isWorldPositionNeedUpdate = false;
		}
		return m_worldPosition;
	}

	void SetPosition(Vector3 value)
	{
		m_isWorldPositionNeedUpdate = true;
		m_localPostion = convertWorldToLocalPosition(value);
		SetChildNeedUpdate();
	}

	Vector3 GetLocalPosition()
	{
		return m_localPostion;
	}

	Vector3 SetLocalPosition(Vector3 value)
	{
		m_isWorldPositionNeedUpdate = true;
		m_localPostion = value;
		SetChildNeedUpdate();
	}

	static Vector3 Divide(Vector3 a, Vector3 b)
	{
		return Vector3(a.x / b.x, a.y / b.y, a.z / b.z);
	}

	Vector3 convertWorldToLocalPosition(Vector3 worldPos)
	{
		if (m_needParentUpdate)
		{
			_updateFromParent();
		}

		Quaternion inverse = Quaternion::Inverse(GetParentOrientation());
		Vector3 divide = Divide(worldPos - GetParentPosition(), GetParentScale());
		return inverse * divide;
	}

	Vector3 convertLocalToWorldPosition(Vector3 localPos)
	{
		if (m_needParentUpdate)
		{
			_updateFromParent();
		}
		//Matrix4x4 matrix = Matrix4x4.TRS(_getDerivedPosition(), _getDerivedOrientation(), _getDerivedScale());
		Matrix4x4 matrix = GetSelfTransform();
		return matrix.MultiplyPoint(localPos);
	}

	void SetChildNeedUpdate()
	{
		//if(m_parent == null)
		{
			m_needParentUpdate = true;
			//m_isWorldPositionNeedUpdate = true;
		}

		for(int i = 0; i < m_childList.size(); ++i)
		{
			Transform * child = m_childList[i];
			child->SetNeedUpdateParent();
		}
	}

	void SetNeedUpdateParent()
	{
		m_needParentUpdate = true;
		//m_isWorldPositionNeedUpdate = true;

		SetChildNeedUpdate();
	}

	void _updateFromParent()
	{
		if (m_parent != NULL)
		{
			Quaternion parentOrientation = m_parent->_getDerivedOrientation();
			m_DerivedOrientation = parentOrientation * m_localRotation;
			Vector3 parentScale = m_parent->_getDerivedScale();
			m_DerivedScale = Vector3::Scale(parentScale, m_localScale);
			// Change position vector based on parent's orientation & scale
			m_DerivedPosition = parentOrientation * Vector3::Scale(parentScale, m_localPostion);
			// Add altered position vector to parents
			m_DerivedPosition = m_DerivedPosition + m_parent->_getDerivedPosition();
		}
		else
		{
			m_DerivedOrientation = m_localRotation;
			m_DerivedPosition = m_localPostion;
			m_DerivedScale = m_localScale;
		}

		m_needParentUpdate = false;
		m_isWorldPositionNeedUpdate = true;
	}

	Quaternion GetParentOrientation()
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

	Vector3 GetParentScale()
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

	Vector3 GetParentPosition()
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

	Quaternion _getDerivedOrientation()
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

	Vector3 _getDerivedScale()
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

	Vector3 _getDerivedPosition()
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

	Quaternion GetRotation()
	{
		return convertLocalToWorldOrientation(m_localRotation);
	}

	void SetRotation(Quaternion value)
	{
		m_localRotation = convertWorldToLocalOrientation(value);
		SetChildNeedUpdate();
	}

	Vector3 GetLocalEulerAngles()
	{
		return m_localRotation.eulerAngles();
	}

	void SetLocalEulerAngles(Vector3 value)
	{
		m_localRotation = Quaternion::Euler(value);
		SetChildNeedUpdate();
	}

	Vector3 GetEulerAngles()
	{
		return GetRotation().eulerAngles();
	}

	Vector3 SetEulerAngles(Vector3 value)
	{
		SetRotation(Quaternion::Euler(value));
	}

	Quaternion convertLocalToWorldOrientation(Quaternion localOrientation)
	{
		if (m_needParentUpdate)
		{
			_updateFromParent();
		}
		return GetParentOrientation() * localOrientation;
	}

	Quaternion convertWorldToLocalOrientation(Quaternion worldOrientation)
	{
		if (m_needParentUpdate)
		{
			_updateFromParent();
		}
		return Quaternion::Inverse(GetParentOrientation()) * worldOrientation;
	}

	Transform * GetParent()
	{
		return m_parent;
	}

	void SetParent(Transform * value)
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

	Quaternion GetLocalRotation()
	{
		return m_localRotation;
	}

	void SetLocalRotation(Quaternion value)
	{
		m_localRotation = value;
		SetChildNeedUpdate();
	}

	Vector3 GetLocalScale()
	{
		return m_localScale;
	}

	void SetLocalScale(Vector3 value)
	{
		m_localScale = value;
		SetChildNeedUpdate();
	}

	Vector3 GetLossyScale()
	{
		return Vector3::Scale(m_DerivedScale, m_localScale);
	}

	void SetLossyScale(Vector3 value)
	{
		m_localScale = Divide(GetLossyScale(), m_DerivedScale);
		SetChildNeedUpdate();
	}

	Matrix4x4 GetSelfTransform()
	{
		Matrix4x4 matrix = Matrix4x4::TRS(_getDerivedPosition(), _getDerivedOrientation(), _getDerivedScale());
		return matrix;
	}

	Matrix4x4 GetLocalToWorld()
	{
		return GetSelfTransform();
	}

	Matrix4x4 GetWorldToLocalMatrix()
	{
		return GetSelfTransform().inverse();
	}

	Vector3 GetForward()
	{
		return GetRotation() * Vector3::forward();
	}

	void SetForward(Vector3 value)
	{
		SetRotation(Quaternion::LookRotation(value));
	}

	Vector3 GetRight()
	{
		return GetRotation() * Vector3::right();
	}

	void SetRight(Vector3 value)
	{
		SetRotation(Quaternion::FromToRotation(Vector3::right(), value));
	}

	Vector3 GetUp()
	{
		return GetRotation() * Vector3::up();
	}

	void SetUp(Vector3 value)
	{
		SetRotation(Quaternion::FromToRotation(Vector3::up(), value));
	}
};
