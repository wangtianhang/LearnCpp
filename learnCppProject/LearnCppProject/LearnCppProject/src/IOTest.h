#pragma once

#include <iostream>
#include <cmath>
#include <fstream>

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

void TestFileOutput()
{
	std::cout << "TestFileOutput ===============begin=================\n";

	std::ofstream outFile;
	outFile.open("testWriteFile.txt");
	outFile << "test";
	outFile.close();

	std::cout << "TestFileOutput ===============end=================\n";
}
