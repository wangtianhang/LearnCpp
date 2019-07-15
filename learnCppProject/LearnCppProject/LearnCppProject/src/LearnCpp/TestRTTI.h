#pragma once

#include <iostream>
#include <typeinfo>

class TestRTTIClass
{

};

class TestRTTIClass2
{

};

void TestRTTI()
{
	std::cout << "TestRTTI ===============begin=================\n";
	if (typeid(TestRTTIClass) == typeid(TestRTTIClass2))
	{

	}
	else
	{

	}
	std::cout << "TestRTTI ===============end=================\n";
}