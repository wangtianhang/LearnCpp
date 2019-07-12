#pragma once

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>

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
	outFile << "line1";
	outFile << "\n";
	outFile << "line2";
	outFile.close();

	std::cout << "TestFileOutput ===============end=================\n";
}

void TestFileInput()
{
	std::cout << "TestFileInput ===============begin=================\n";

	std::ifstream inFile;
	inFile.open("testWriteFile.txt");
	if (!inFile.is_open())
	{
		std::cout << "没有打开文件" << std::endl;
		return;
	}

// 	char buffer[256];
// 	while (inFile.good())
// 	{
// 		//std::string line;
// 		//inFile >> line;
// 		std::streamsize size = 256;
// 		inFile.read(buffer, size);
// 		std::cout << line;
// 	}
//	std::string str((std::istreambuf_iterator<char>(inFile)),
//		std::istreambuf_iterator<char>());

	std::stringstream buffer;
	buffer << inFile.rdbuf();

	inFile.close();

	std::string content(buffer.str());
	// 感觉不清理也可以 直接等待析构？
	buffer.clear();

	std::cout << content.c_str() << std::endl;
	std::cout << "TestFileInput ===============end=================\n";
}
