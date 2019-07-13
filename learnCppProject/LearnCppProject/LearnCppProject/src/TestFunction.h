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

struct FuncStruct
{

public: 
	int test;

	int GetGaga(int a)
	{
		return 0;
	}

	static int GetStaticGaga(int a)
	{
		return 0;
	}
};

struct SubFuncStruct : FuncStruct
{

};

FuncStruct TestPassStruct(FuncStruct a, FuncStruct b)
{
	FuncStruct ret;

	ret.test = a.test + b.test;

	return ret;
}

// 错误示范
FuncStruct& TestPassStruct2(FuncStruct a, FuncStruct b)
{
	FuncStruct ret;

	ret.test = a.test + b.test;

	/*不能这样写 返回局部变量的引用 外部得到的会是一个烂值*/
	return ret;
}

// 错误示范
FuncStruct * TestPassStruct2_2(FuncStruct a, FuncStruct b)
{
	FuncStruct ret;

	ret.test = a.test + b.test;

	/*不能这样写 返回局部变量的引用 外部得到的会是一个烂值*/
	return &ret;
}

void TestPassStruct3(const FuncStruct * a, const FuncStruct * b, FuncStruct * ret)
{
	//FuncStruct ret;

	ret->test = a->test + b->test;

}

void TestPassStruct4(const FuncStruct& a, const FuncStruct& b, FuncStruct& c)
{
	c.test = a.test + b.test;
}

void TestStr(const std::string& a, const std::string& b, std::string& c)
{
	c = a + b;
}

double Pam(int a = 1)
{
	return 0;
}

void estimate(int lines, double(*pf)(int))
{

}

typedef double (*p_fun)(int); // p_fun now a type name

inline double square(double x) { return x * x; }

void OverloadTest(int a)
{

}

void OverloadTest(double b)
{

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

	{
		// 指针和引用相关
		FuncStruct a;
		a.test = 1;
		FuncStruct b;
		b.test = 2;
		FuncStruct c = TestPassStruct(a, b);
		std::cout << c.test << std::endl;

		TestPassStruct3(&a, &b, &c);

		// 子类可以直接传到父类引用
		SubFuncStruct d;
		TestPassStruct4(a, b, d);

		std::string str;
		TestStr("aaa", "bbb", str);
		std::cout << str << std::endl;
	}


	{
		// 函数指针相关
		// 1.全局函数 类c函数
		double(*pf)(int);// pf points to a function that returns double
		// 需要注意 下面这个不是函数指针 是一个函数
		double *pf2(int); // pf() a function that returns a pointer-to-double
		pf = Pam;
		// 如下两种方式是等价的
		double ret4 = (*pf)(1);
		double ret5 = pf(1); // 这种感觉可以理解成一种语法糖
		estimate(50, Pam);

		// 如下形式是c++11的语法糖。。
		auto pf3 = &Pam;
		pf3(1);

		// 2.测试成员函数的函数指针
		FuncStruct test;
		auto pf4 = &FuncStruct::GetGaga;
		(test.*pf4)(1);

		// 3.测试类成员的函数指针
		FuncStruct::GetStaticGaga(1);
		auto pf5 = &FuncStruct::GetStaticGaga;
		pf5(1);

		p_fun pf6 = &Pam;
		pf6(1);
	}


	std::cout << "TestFunction ===============end=================\n";
}


