#pragma once

#include <iostream>
#include <string>
#include <cctype>

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

	std::string str1 = "gaga1";
	std::string str2 = "gaga2";
	std::string str3 = str1 + str2;
	str2 += str1;
	std::cout << str3 << std::endl;

	int len = str1.size();
	int len2 = strlen(str1.c_str());

	if (false)
	{
		char test2[3] = "12";
		char test3[10] = "12345";
		strcpy_s(test2, test3); // 拷贝源str到des str 目标buffer需要比src buffer大
		strcat_s(test2, test3); // 连接源str到des buffer 目标buffer需要比src buffer大

		std::cout << test2 << std::endl;
	}
	
	const char * str4 = str3.c_str();
	int tmpLen = strlen(str4);
	char * ps = new char[tmpLen + 1];
	// 太蛋疼了 同一个函数名居然能对应各种参数列表 无语。。
	strcpy_s(ps, tmpLen + 1, str4);
	//*(ps + tmpLen) = '\0';

	char food[20];
	strncpy_s(food, "a picnic basket filled with many goodies", 19);
	food[19] = '\0';

	if (strcmp(str4, ps) == 0)
	{
		std::cout << "字符串相等" << std::endl;
 	}
	else
	{
		std::cout << "字符串不相等" << std::endl;
	}

	char tmp = 'a';
	if (isalpha(tmp))
	{
		std::cout << "是字母" << std::endl;
	}
	else
	{
		std::cout << "不是字母" << std::endl;
	}

	std::cout << "TestString ===============end=================\n";
}