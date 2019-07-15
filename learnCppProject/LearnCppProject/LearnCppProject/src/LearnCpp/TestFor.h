#pragma once

#include <iostream>
#include <vector>

static void DataCallback2(int)
{

}

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

	std::vector<int> intVec;
	intVec.push_back(1);

	std::vector<int>::iterator pr;
	for (pr = intVec.begin(); pr != intVec.end(); ++pr)
	{
		DataCallback2(*pr);
	}

	for_each(intVec.begin(), intVec.end(), DataCallback2);

	for (auto x : intVec)
	{
		DataCallback2(x);
	}

	std::cout << "TestFor ===============end=================\n";
}