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
		1.88f, // volume value
		29.99 // price value
	};

	Inflatable guest2;
	guest2.price = 10;

	cout << guest2.price << endl;

	std::cout << "TestStruct ===============end=================\n";
}

struct perks
{
	int key_number;
	char car[12];
} mr_smith, ms_jones; // two perks variables

struct perks2
{
	int key_number;
	char car[12];
} mr_glitz =
{
7, // value for mr_glitz.key_number member
"Packard" // value for mr_glitz.car member
};

struct // no tag
{
	int x; // 2 members
	int y;
} position; // a structure variable

