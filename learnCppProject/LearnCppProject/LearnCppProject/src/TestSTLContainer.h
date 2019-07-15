#pragma once

#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <array>

void DataCallback(int)
{

}

void TestSTLContainer()
{
	std::cout << "TestSTLDataStruct ===============begin=================\n";
	std::vector<int> intVec;
	intVec.push_back(1);

	std::vector<int>::iterator pr;
	for (pr = intVec.begin(); pr != intVec.end(); ++pr)
	{
		DataCallback(*pr);
	}

	for_each(intVec.begin(), intVec.end(), DataCallback);
	
	for (auto x : intVec)
	{
		DataCallback(x);
	}

	//The deque template class (declared in the deque header file) represents a double-ended queue, a type often called a deque(pronounced “deck”), for short
	std::deque<int> intDeque;
	//The list template class (declared in the list header file) represents a doubly linked list.
	std::list<int> intList;

	std::queue<int> intQueue;

	std::priority_queue<int> intPriorityQueue;

	std::stack<int> intStack;

	//c++11新增 固定长度的vector
	std::array<int, 4> intArray;

	std::cout << "TestSTLDataStruct ===============end=================\n";
}