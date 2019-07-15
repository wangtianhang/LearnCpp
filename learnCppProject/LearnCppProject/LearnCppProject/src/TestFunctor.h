#pragma once

#include <iostream>
#include <algorithm>
//#include <cmath>

class Linear
{
private:
	double slope;
	double y0;
public:
	Linear(double sl_ = 1, double y_ = 0)
		: slope(sl_), y0(y_) {}
	double operator()(double x) { return y0 + slope * x; }
};

class SqrtFunctor 
{
public:
	double operator()(double x) { return sqrt(x); }
};

void TestFunctor()
{
	std::cout << "TestFunctor ===============begin=================\n";
	Linear f1;
	double y1 = f1(12.5); // right-hand side is f1.operator()(12.5)

	vector<double> arr1{ 28, 29, 30, 35, 38, 59 };
	vector<double> arr2;
	SqrtFunctor sqrtFunctor;
	transform(arr1.begin(), arr1.end(), std::insert_iterator<vector<double> >(arr2, arr2.begin()), sqrtFunctor);

	for (auto x : arr2)
	{
		std::cout << x << std::endl;
	}
	std::cout << "TestFunctor ===============end=================\n";
}