#pragma once

#include <vector>
#include "./Quaternion.h"
#include "./Vector3.h"

struct Matrix4x4;
class Transform
{
private:
	bool m_needParentUpdate = true;

	Vector3 m_localPostion;
	Quaternion m_localRotation = Quaternion::identity();
	Vector3 m_localScale = Vector3::one();

	Quaternion m_DerivedOrientation = Quaternion::identity(); // 包含自身和上级
	Vector3 m_DerivedScale = Vector3::one(); // 包含自身和上级
	Vector3 m_DerivedPosition; // 只含上级

	Transform * m_parent = NULL;
	std::vector<Transform *> m_childList;

	Vector3 m_worldPosition;
	bool m_isWorldPositionNeedUpdate = true;

public:
	std::string m_name;

	static void Test();

	static Vector3 NormalizeAngles(Vector3 angles);

	static float NormalizeAngle(float angle);

	Vector3 GetPosition();

	void SetPosition(Vector3 value);

	Vector3 GetLocalPosition();

	void SetLocalPosition(Vector3 value);

	static Vector3 Divide(Vector3 a, Vector3 b);

	Vector3 convertWorldToLocalPosition(Vector3 worldPos);

	Vector3 convertLocalToWorldPosition(Vector3 localPos);

	void SetChildNeedUpdate();

	void SetNeedUpdateParent();

	void _updateFromParent();

	Quaternion GetParentOrientation();

	Vector3 GetParentScale();

	Vector3 GetParentPosition();

	Quaternion _getDerivedOrientation();

	Vector3 _getDerivedScale();

	Vector3 _getDerivedPosition();

	Quaternion GetRotation();

	void SetRotation(Quaternion value);

	Vector3 GetLocalEulerAngles();

	void SetLocalEulerAngles(Vector3 value);

	Vector3 GetEulerAngles();

	void SetEulerAngles(Vector3 value);

	Quaternion convertLocalToWorldOrientation(Quaternion localOrientation);

	Quaternion convertWorldToLocalOrientation(Quaternion worldOrientation);

	Transform * GetParent();

	void SetParent(Transform * value);

	Quaternion GetLocalRotation();

	void SetLocalRotation(Quaternion value);

	Vector3 GetLocalScale();

	void SetLocalScale(Vector3 value);

	Vector3 GetLossyScale();

	void SetLossyScale(Vector3 value);

	Matrix4x4 GetSelfTransform();

	Matrix4x4 GetLocalToWorldMatrix();

	Matrix4x4 GetWorldToLocalMatrix();

	Vector3 GetForward();

	void SetForward(Vector3 value);

	Vector3 GetRight();

	void SetRight(Vector3 value);

	Vector3 GetUp();

	void SetUp(Vector3 value);

};
