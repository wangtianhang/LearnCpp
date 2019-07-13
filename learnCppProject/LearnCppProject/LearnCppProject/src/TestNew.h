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

	// placement new 可以指定new的内存位置
	char buffer2[500];
	int * placement = new (buffer2) int[20];
	//delete[] placement; // 貌似这种不用delete。。
	placement = NULL;

	std::cout << "TestNewAndDelete ===============end=================\n";
}