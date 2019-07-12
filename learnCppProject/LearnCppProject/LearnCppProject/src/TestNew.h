#pragma once
#include <iostream>

void TestNewAndDelete()
{
	using namespace std;
	std::cout << "TestNewAndDelete ===============begin=================\n";
	{
		int * pn = new int;
		*pn = 1001;

		delete pn;
		pn = NULL;
	}

	{
		// 感觉好像只能自己记录数组长度。。

		int tmp = 10;
		int * psome = new int[tmp];

		for (int i = 0; i < tmp; ++i)
		{
			*(psome + i) = i;
		}

		delete[] psome;
		psome = nullptr;
	}
	std::cout << "TestNewAndDelete ===============end=================\n";
}