#pragma once

#include <iostream>

void TestPointer()
{
	std::cout << "TestPointer ===============begin=================\n";

	using namespace std;
	int donuts = 6;
	int * p_donuts = &donuts;
	cout << " and donuts address = " << p_donuts << endl;
	*p_donuts += 1;
	cout << " and donuts content = " << *p_donuts << endl;

	if (false)
	{
		// 未初始化的指针很危险 可能写入到任何内存
		long * fellow; // create a pointer-to-long
		*fellow = 223323; // place a value in never-never land
	}

	{
		// 可以自由的指向任何地方。。
		int address = 0xB8000000;
		int * pt;
		pt = (int *)address;

		double * pt2;
		cout << " double pointer size " << sizeof(pt2) << endl;
		cout << " double size " << sizeof(double) << endl;
	}

	std::cout << "TestPointer ===============end=================\n";
}