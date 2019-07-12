#pragma once

int Sum(/*const保护不被修改*/const int arr[], int n)
{
	int total = 0;
	for (int i = 0; i < n; i++)
		total = total + arr[i];

	//arr[0] = 1;

	return total;
}

int Sum2(const int * begin, const int * end)
{
	const int * pt;
	int total = 0;
	for (pt = begin; pt != end; pt++)
		total = total + *pt;
	return total;
}

void TestFunction()
{
	std::cout << "TestFunction ===============begin=================\n";

	const int ArSize = 8;
	int cookies[ArSize] = { 1,2,4,8,16,32,64,128 };
	int ret = Sum(cookies, ArSize);
	int ret2 = Sum2(cookies, cookies + 3);

	std::cout << "TestFunction ===============end=================\n";
}

