#pragma once

#include <iostream>

void TestString()
{
	std::cout << "TestString ===============begin=================\n";

	const int size = 15;
	char test[size] = "gaga";
	for (int i = 0; i < size; ++i)
	{
		int tmp = test[i];
		char tmp2 = (char)tmp;
		std::cout << tmp2 << "\t" << tmp << std::endl;
	}

	std::cout << "TestString ===============end=================\n";
}