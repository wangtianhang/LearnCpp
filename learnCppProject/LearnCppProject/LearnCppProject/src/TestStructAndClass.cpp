#include "pch.h"

#include "./TestStructAndClass.h"

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

int TestClass::m_test = 1;

TestClass::TestClass()
{
	m_test2 = 1;
}

TestClass::TestClass(int a)
{

}

TestClass::~TestClass()
{

}

inline int TestClass::TestClassFunc() const
{
	return this->m_test2;
}

int TestClass::GetStaticGaga(int a)
{
	return 0;
}

TestClass TestClass::operator+(const TestClass & t) const
{
	TestClass sum;

	return sum;
}

TestClass::operator int() const
{
	return 0;
}

TestClass::operator std::string() const
{
	return "";
}

void TestStructAndClass()
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

	Inflatable gifts[100]; // array of 100 inflatable structures

	Inflatable guests[2] = // initializing an array of structs
	{
	{"Bambi", 0.5, 21.99}, // first structure in array
	{"Godzilla", 2000, 565.99} // next structure in array
	};

	Inflatable * ps = new Inflatable;
	ps->price = 10;

	TestClass testClass;
	testClass.TestClassFunc();

	TestClass a;
	TestClass b;
	TestClass c = a + b;

	int d = (int)c;
	TestClass e = 2;
	string f = c;

	std::cout << "TestStruct ===============end=================\n";
}

std::ostream & operator<<(std::ostream & os, const TestClass & t)
{
	os << t.m_test3;
	return os;
}