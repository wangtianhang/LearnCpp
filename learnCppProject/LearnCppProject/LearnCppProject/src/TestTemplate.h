#pragma once

template <typename AnyType>
void Swap(AnyType &a, AnyType &b)
{
	AnyType temp;
	temp = a;
	a = b;
	b = temp;
}

template <class Type, class Type2>
class TestTemplateClass
{
	Type m_t1;
	Type2 m_t2;
};

void TestTemplate()
{
	std::cout << "TestTemplate ===============begin=================\n";

	int a = 5;
	int b = 6;
	Swap(a, b);
	Swap<int>(a, b);

	TestTemplateClass<int, const char *> t = TestTemplateClass<int, const char *>();

	std::cout << "TestTemplate ===============end=================\n";
}

