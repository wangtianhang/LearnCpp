#pragma once
#include <iostream>
#include <array>

void TestArray()
{
	//int num = 4;
	std::cout << "TestArray ===============begin=================\n";

	int test[4];
	test[0] = 1;
	for (int i = 0; i < 4; ++i)
	{
		std::cout << test[i] << std::endl;
	}

	int test2[4] = {3, 6, 8, 10};
	for (int i = 0; i < 4; ++i)
	{
		std::cout << test2[i] << std::endl;
	}

	double wages[3] = { 10000.0, 20000.0, 30000.0 };
	double *p = &wages[0];
	if (wages == &wages[0])
	{
		std::cout << "wages == &wages[0]" << std::endl;
	}
	std::cout << *p << std::endl;

	// 相当于定长vector
	std::array<double, 4> a3 = { 3.14, 2.72, 1.62, 1.41 };
	for (size_t i = 0; i < a3.size(); ++i)
	{
		std::cout << a3[i] << std::endl;
	}

	std::cout << "TestArray ===============end=================\n";
}