#pragma once

#include <iostream>

void TestPointer()
{
	using namespace std;
	int donuts = 6;
	int * p_donuts = &donuts;
	cout << " and donuts address = " << p_donuts << endl;
	*p_donuts += 1;
	cout << " and donuts content = " << *p_donuts << endl;
}