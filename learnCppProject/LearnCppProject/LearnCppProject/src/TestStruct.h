#pragma once
#include <iostream>

struct Inflatable
{
	char name[20];
	float volume;
	double price;
};

void TestStruct()
{
	std::cout << "TestStruct ===============begin=================\n";

	using namespace std;

	Inflatable guest =
	{
		"Glorious Gloria", // name value
		1.88, // volume value
		29.99 // price value
	};

	Inflatable guest2;
	guest2.price = 10;

	cout << guest2.price << endl;

	std::cout << "TestStruct ===============end=================\n";
}