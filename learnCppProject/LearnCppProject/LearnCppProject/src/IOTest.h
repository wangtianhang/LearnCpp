#pragma once

#include <iostream>
#include <cmath>

void TestStdOutput()
{
	std::cout << "TestStdOutput ===============begin=================\n";

	std::cout << "test" << std::endl;
	int test = 2;
	std::cout << "test" << test;
	std::cout << std::endl;
	std::cout << sqrt(3) << std::endl;

	std::string testStr = "25";
	printf("print a string: %s\n", testStr.c_str());
	printf("print a integer: %d\n", test);

	std::cout << "TestStdOutput ===============end=================\n";
}

void TestStdInput()
{
	int test = 0;
	std::cin >> test;
}
