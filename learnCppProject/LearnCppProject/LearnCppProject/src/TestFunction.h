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

int Sum3(int ar2[][4], int size)
{
	int total = 0;
	for (int r = 0; r < size; r++)
		for (int c = 0; c < 4; c++)
			total += ar2[r][c];
	return total;
}

// this function counts the number of ch characters
// in the string str
// 统计string中字母ch的数量
unsigned int c_in_str(const char * str, char ch)
{
	unsigned int count = 0;
	while (*str) // quit when *str is '\0'
	{
		if (*str == ch)
			count++;
		str++; // move pointer to next char
	}
	return count;
}

// builds string made of n c characters
/* const保护返回值 */const char * buildstr(char c, int n)
{
	char * pstr = new char[n + 1];
	pstr[n] = '\0'; // terminate string
	while (n-- > 0)
		pstr[n] = c; // fill rest of string
	return pstr;
}

void TestFunction()
{
	std::cout << "TestFunction ===============begin=================\n";

	const int ArSize = 8;
	int cookies[ArSize] = { 1,2,4,8,16,32,64,128 };
	int ret = Sum(cookies, ArSize);
	int ret2 = Sum2(cookies, cookies + 3);
	int data[3][4] = { {1,2,3,4}, {9,8,7,6}, {2,4,6,8} };
	int ret3 = Sum3(data, 3);
	unsigned int ms = c_in_str("minimum", 'm');

	const char * cstr = buildstr('a', 10);
	//cstr[0] = 'b';
	// 返回的const可以被delete 但是不能被修改
	delete[] cstr;
	cstr = NULL;

	std::cout << "minimum 中 m 数量 " << ms << std::endl;

	std::cout << "TestFunction ===============end=================\n";
}

