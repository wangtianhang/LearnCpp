#pragma once

template <typename AnyType>
void Swap(AnyType &a, AnyType &b)
{
	AnyType temp;
	temp = a;
	a = b;
	b = temp;
}

void TestTemplate()
{
	std::cout << "TestTemplate ===============begin=================\n";

	int a = 5;
	int b = 6;
	Swap(a, b);
	Swap<int>(a, b);

	std::cout << "TestTemplate ===============end=================\n";
}

