#include "pch.h"

#include <iostream>
#include "./Test3DMath.h"

#include "./Mathf.h"
#include "./Vector3.h"
#include "./Quaternion.h"
#include "./Matrix4x4.h"

void Test3dMath()
{
	std::cout << "Test3dMath ===============begin=================\n";

	Mathf::Test();

	Vector3::Test();

	Quaternion::Test();

	Matrix4x4::Test();

	std::cout << "Test3dMath ===============end=================\n";
}
