#pragma once

#include <ctime>
#include <iostream>

void TestTime()
{
	std::cout << "TestTime ===============begin=================\n";

	// ��λΪms
	std::clock_t start = clock();
	std::clock_t end = clock();

	std::clock_t delta = end - start;

	std::cout << "TestTime ===============end=================\n";
}
