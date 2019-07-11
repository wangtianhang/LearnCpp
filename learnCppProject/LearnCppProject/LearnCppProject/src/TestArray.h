#pragma once
#include <iostream>

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

	std::cout << "TestArray ===============end=================\n";
}