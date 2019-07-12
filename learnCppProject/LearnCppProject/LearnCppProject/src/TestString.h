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
		strcpy_s(test2, test3); // ����Դstr��des str Ŀ��buffer��Ҫ��src buffer��
		strcat_s(test2, test3); // ����Դstr��des buffer Ŀ��buffer��Ҫ��src buffer��

		std::cout << test2 << std::endl;
	}
	
	const char * str4 = str3.c_str();
	int tmpLen = strlen(str4);
	char * ps = new char[tmpLen + 1];
	// ̫������ ͬһ����������Ȼ�ܶ�Ӧ���ֲ����б� �����
	strcpy_s(ps, tmpLen + 1, str4);
	//*(ps + tmpLen) = '\0';

	char food[20];
	strncpy_s(food, "a picnic basket filled with many goodies", 19);
	food[19] = '\0';

	if (strcmp(str4, ps) == 0)
	{
		std::cout << "�ַ������" << std::endl;
 	}
	else
	{
		std::cout << "�ַ��������" << std::endl;
	}

	char tmp = 'a';
	if (isalpha(tmp))
	{
		std::cout << "����ĸ" << std::endl;
	}
	else
	{
		std::cout << "������ĸ" << std::endl;
	}

	std::cout << "TestString ===============end=================\n";
}