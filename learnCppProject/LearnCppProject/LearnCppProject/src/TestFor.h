#pragma once

#include <iostream>

void TestFor()
{
	std::cout << "TestFor ===============begin=================\n";

	double prices[5] = { 4.99, 10.99, 6.87, 7.99, 8.49 };
	for (double x : prices)
		std::cout << x << std::endl;

	for (double &x : prices)
	{
		x = x * 0.8;
	}

	std::cout << "TestFor ===============end=================\n";
}