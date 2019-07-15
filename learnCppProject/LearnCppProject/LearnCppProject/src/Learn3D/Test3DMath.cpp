#include "pch.h"

#include <iostream>
#include "./Test3DMath.h"

#include "./Mathf.h"
#include "./Vector3.h"

void Test3dMath()
{
	std::cout << "Test3dMath ===============begin=================\n";

	Mathf::Test();

	Vector3::Test();

	std::cout << "Test3dMath ===============end=================\n";
}
