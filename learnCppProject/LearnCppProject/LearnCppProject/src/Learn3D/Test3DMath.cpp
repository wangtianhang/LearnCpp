#include "pch.h"

#include <iostream>
#include "./Test3DMath.h"

#include "./Mathf.h"
#include "./Vector3.h"

void Test3dMath()
{
	std::cout << "Test3dMath ===============begin=================\n";

	Mathf::Test();

	Vector3 a = Vector3(1, 0, 0);
	Vector3 b = Vector3(1, 0, 0);
	Vector3 c = a + b;
	Vector3 d = (a + b) + c;

	d = -d;

	Vector3 e = c * 2;
	Vector3 f = 2 * c;

	std::cout << "Test3dMath ===============end=================\n";
}
