#pragma once
#include <iostream>

struct Inflatable
{
	char name[20];
	float volume;
	double price;
};

class TestClass
{
public:
	TestClass();
	TestClass(int a);
	virtual ~TestClass();
	// ���ƺ��� 
	TestClass(const TestClass& testClass);
	TestClass& operator=(const TestClass &);

	int m_test2;
	static int m_test;

	int TestClassFunc() const;

	static int GetStaticGaga(int a);

	TestClass operator+(const TestClass & t) const;
	friend std::ostream & operator<<(std::ostream & os, const TestClass & t);

	// ��ʽת��
	explicit operator int() const;
	// ��ʽת��
	operator std::string() const;

	virtual void TestVirtualFunc();
protected:
	
private:
	int m_test3;
};

class SubTestClass : public TestClass
{
public:
	virtual void TestVirtualFunc();
};

void TestStructAndClass();




