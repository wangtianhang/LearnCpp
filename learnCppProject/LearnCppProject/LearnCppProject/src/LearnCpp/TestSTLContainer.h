#pragma once

#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <array>
#include <set>
#include <map>
#include <unordered_map>

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

	{
		// 有序关联数据结构 底层为tree

		std::set<std::string> setTest = { "buffoon", "thinkers", "for", "heavy", "can", "for" };
		std::set<std::string> setTest2 = { "buffoon2", "thinkers2", "for2", "heavy2", "can2", "for2" };
		std::set<std::string> setTest3;
		set_union(setTest.begin(), setTest.end(), setTest2.begin(), setTest2.end(),
			insert_iterator<set<string> >(setTest3, setTest3.begin()));

		// 容许有重复键的map
		std::multimap<int, string> multimapTest;

		std::map<int, string> treemapTest;
	}

	{
		// 无序关联数据结构 底层为hashmap

		std::unordered_map<int, string> hashmapTest;
	}

	std::cout << "TestSTLDataStruct ===============end=================\n";
}

/*
vector
创建对象，vector<int> vec;
尾部插入数字，vec.push_back(a)；
使用下表访问元素
使用迭代器访问元素
插入元素
删除最后一个元素，vec.pop_back()

queue
定义一个queue的变量 queue<Type> M
查看是否为空范例  M.empty()
从已有元素后面增加元素 M.push()
输出现有元素的个数 M.size()
显示第一个元素 M.front()
显示最后一个元素 M.back()
弹出队列的第一个元素 M.pop()

stack
返回栈的元素数size()
返回栈顶的元素 top()
从栈中去除并删除元素 pop()
向栈中添加元素x push(x)
在栈为空时返回true empty()

map
map遍历
basic
for (iter = str2vec.begin(); iter != str2vec.end(); iter++)
{
	output.push_back(iter->second);
}
faster
for (auto& p : str2vec) {
	output.push_back(p.second);
}

list
list是双向链表，与向量相比，它允许快读的插入和删除，但是随机访问比较慢
Lst1.assign() 给list赋值 
Lst1.back() 返回最后一个元素 
Lst1.begin() 返回指向第一个元素的迭代器 
Lst1.clear() 删除所有元素 
Lst1.empty() 如果list是空的则返回true 
Lst1.end() 返回末尾的迭代器 
Lst1.erase() 删除一个元素 
Lst1.front() 返回第一个元素 
Lst1.get_allocator() 返回list的配置器 
Lst1.insert() 插入一个元素到list中 
Lst1.max_size() 返回list能容纳的最大元素数量 
Lst1.merge() 合并两个list 
Lst1.pop_back() 删除最后一个元素 
Lst1.pop_front() 删除第一个元素 
Lst1.push_back() 在list的末尾添加一个元素 
Lst1.push_front() 在list的头部添加一个元素 
Lst1.rbegin() 返回指向第一个元素的逆向迭代器 
Lst1.remove() 从list删除元素 
Lst1.remove_if() 按指定条件删除元素 
Lst1.rend() 指向list末尾的逆向迭代器 
Lst1.resize() 改变list的大小 
Lst1.reverse() 把list的元素倒转 
Lst1.size() 返回list中的元素个数 
Lst1.sort() 给list排序 
Lst1.splice() 合并两个list 
Lst1.swap() 交换两个list 
Lst1.unique() 删除list中重复的元素


priority_queue
q.push()
q.pop()
q.top()

bitset
bitset的大小在编译时就需要确定
定义bitset，bitset<16> b;
b.size() 返回位数
b.count() 返回1的个数
b.any() 返回是否有1
b.none() 返回是否没有1
b.set() 全部变成1
b.set(i) 将i + 1位变成1
b.set(i, x) 将i + 1位变成x
b.reset() 全部都变成0
b.flip() 全部去翻
b.to_string() 转为string类型


unordered_map
1.find函数判断某键值是否存在
map.find(key) == map.end() 时不存在
2.count函数
统计key值在map中出现的次数
int count(key)

set
1. begin()--返回指向第一个元素的迭代器
2. clear()--清除所有元素
3. count()--返回某个值元素的个数
4. empty()--如果集合为空，返回true
5. end()--返回指向最后一个元素的迭代器
6. equal_range()--返回集合中与给定值相等的上下限的两个迭代器
7. erase()--删除集合中的元素
8. find()--返回一个指向被查找到元素的迭代器
9. get_allocator()--返回集合的分配器
10. insert()--在集合中插入元素
11. lower_bound()--返回指向大于（或等于）某值的第一个元素的迭代器
12. key_comp()--返回一个用于元素间值比较的函数
13. max_size()--返回集合能容纳的元素的最大限值
14. rbegin()--返回指向集合中最后一个元素的反向迭代器
15. rend()--返回指向集合中第一个元素的反向迭代器
16. size()--集合中元素的数目
17. swap()--交换两个集合变量
18. upper_bound()--返回大于某个值元素的迭代器
19. value_comp()--返回一个用于比较元素间的值的函数

unordered_set
1. empty() --检查是否为空
2. insert()--插入元素
3. erase()--删除指定元素

*/